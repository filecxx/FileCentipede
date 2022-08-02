#include "tool_checksum.h"

namespace pro::tools
{

checksum::checksum(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/tools/checksum.sml")
{
    form_text_  = ext::ui::form(ui("#checksum_text"));
    form_file_  = ext::ui::form(ui("#checksum_file"));

    ui.cast(file_path_,"#file_path");
    ui.cast(button_start_,"#start");
    ui.cast(button_stop_,"#stop");
    ui.cast(button_save_,"#save");

    dialog_->on_drop([this](auto files){
        stop();
        join();
        file_path_->text(files[0]);
    });
    dialog_->on_close([this](auto e){
        delete this;
    });
    init_actions();
}

checksum::~checksum()
{
    stop();
    join();
}


///--------------------------
void checksum::init_actions()
{
    ui.cast<ext::ui::text_edit*>("#text")->on_change([this](auto){
        calc_text(ui.query_value("#text").text_view());
    });
    file_path_->on_change([this](auto){
        start();
    });
    button_start_->on_click([this](auto){
        start();
    });
    button_stop_->on_click([this](auto){
        stop();
    });
    button_save_->on_click([this](auto){
        save();
    });
}


///--------------------------
void checksum::post_file_result(const ext::text& name,const std::string& result)
{
    ext::ui::post([this,name,result]
    {
        if(!stopping()){
            form_file_.values({{name,result}});
        }
        if(--refcount_ == 0){
            button_start_->setEnabled(true);
            button_stop_->setEnabled(false);
            state_ = ext::state::Stopped;
            form_file_.values({{"state","stopped"_lang},{"file_size",total_size_}});
        }
    });
}

void checksum::post_file_progress(const ext::text& name,size_t file_size,size_t offset,size_t size)
{
    ext::ui::post([this,name,file_size,offset,size]
    {
        if(temp_key_.empty()){
            temp_key_ = name;
        }
        if(name == temp_key_){
            total_size_ += size;
        }
        form_file_.values({{"progress_" + name,ext::percentage(offset + size,file_size)}});
    });
}

void checksum::calc_text(ext::text_view text)
{
    std::string str_crc = std::to_string(ext::checksum::crc32(text));
    std::string out_md5,out_sha1,out_sha256;

    auto md5    = ext::checksum::md5(text);
    auto sha1   = ext::checksum::sha1(text);
    auto sha256 = ext::checksum::sha256(text);

    ext::crypto::bin2hex((uint8_t*)md5.data(),md5.size(),out_md5,"");
    ext::crypto::bin2hex((uint8_t*)sha1.data(),sha1.size(),out_sha1,"");
    ext::crypto::bin2hex((uint8_t*)sha256.data(),sha256.size(),out_sha256,"");

    form_text_.values({{"text_crc32",str_crc},{"text_md5",out_md5},{"text_sha1",out_sha1},{"text_sha256",out_sha256}});
}

void checksum::calc_file(const ext::fs::path& path)
{
    if(path.empty()){
        return void();
    }
    state_      = ext::state::Running;
    total_size_ = 0;
    temp_key_.clear();
    form_file_.values({{"state","working"_lang}});
    button_start_->setEnabled(false);
    button_stop_->setEnabled(true);
    form_file_.values({{"file_crc32",""},{"file_md5",""},{"file_sha1",""},{"file_sha256",""}});
    ui.cast<ext::ui::tab*>("#tab")->current(1);

    auto values = form_file_.values();

    if(values["file_crc32_check"] == true)
    {
        ++refcount_;
        threads_[0] = std::jthread([this,path]
        {
            auto out_crc = std::to_string(ext::checksum::file_crc32(path,[this](auto file_index,const auto& file_path,auto data,auto size,auto offset,auto file_size){
                post_file_progress("crc32",file_size,offset,size);
                return stopping();
            }));
            post_file_result("file_crc32",out_crc);
        });
    }
    if(values["file_md5_check"] == true)
    {
        ++refcount_;
        threads_[1] = std::jthread([this,path]
        {
            std::string str = ext::checksum::file_md5(path,[this](auto file_index,const auto& file_path,auto data,auto size,auto offset,auto file_size){
                post_file_progress("md5",file_size,offset,size);
                return stopping();
            });
            std::string out_md5;
            ext::crypto::bin2hex((uint8_t*)str.data(),str.size(),out_md5,"");

            post_file_result("file_md5",out_md5);
        });
    }
    if(values["file_sha1_check"] == true)
    {
        ++refcount_;
        threads_[2] = std::jthread([this,path]
        {
            std::string str = ext::checksum::file_sha1(path,[this](auto file_index,const auto& file_path,auto data,auto size,auto offset,auto file_size){
                post_file_progress("sha1",file_size,offset,size);
                return stopping();
            });
            std::string out_sha1;
            ext::crypto::bin2hex((uint8_t*)str.data(),str.size(),out_sha1,"");

            post_file_result("file_sha1",out_sha1);
        });
    }
    if(values["file_sha256_check"] == true)
    {
        ++refcount_;
        threads_[3] = std::jthread([this,path]
        {
            std::string str = ext::checksum::file_sha256(path,[this](auto file_index,const auto& file_path,auto data,auto size,auto offset,auto file_size){
                post_file_progress("sha256",file_size,offset,size);
                return stopping();
            });
            std::string out_sha256;
            ext::crypto::bin2hex((uint8_t*)str.data(),str.size(),out_sha256,"");

            post_file_result("file_sha256",out_sha256);
        });
    }
}


///--------------------------
void checksum::start()
{
    stop();
    join();

    calc_file(file_path_->text());
}

void checksum::stop()
{
    Ext_Return_If(state_ != ext::state::Running);

    state_ = ext::state::Stopping;
}

void checksum::join()
{
    for(auto& thread : threads_){
        try{
            if(thread.joinable()){
                thread.join();
            }
        }catch(...){

        }
    }
}

void checksum::save()
{
    auto error  = ext::error_code();
    auto path   = ext::fs::path(file_path_->text());
    auto values = form_file_.values();
    auto names  = {"crc32","md5","sha1","sha256"};

    if(path.empty() || !ext::fs::exists(path,error)){
        return;
    }
    for(auto name : names)
    {
        auto key = "file_"_text + name;

        if(values[key + "_check"] == true && !values[key].empty())
        {
            auto save_path = file_path_->text() + "." + name;

            if((error = ext::cfile::write(save_path,"wb",values[key].text() + "  " + path.filename()))){
                ext::ui::alert("error","error"_lang,"write_file_error"_lang + " : "_text + save_path).exec();
            }
        }
    }
}

void checksum::exec(const ext::text& path)
{
    dialog_->show();

    if(!path.empty()){
        file_path_->text(path);
    }
}

void checksum::exec(int argc,char** argv)
{
    exec(argc == 0 ? "" : argv[0]);
}


}