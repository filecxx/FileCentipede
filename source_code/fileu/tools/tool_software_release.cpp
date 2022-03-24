#include "tool_software_release.h"

namespace pro::tools
{

software_release::software_release(pro::global& global) : pro::dialog_sample<>(global,"ui/tools/software_release.sml")
{
    dialog_->on_close([this](auto e)
    {
        closing_ = true;
        if(archive_thread_.joinable()){
            try{
                archive_thread_.join();
            }catch(...){}
        }
        delete this;
    });
    form_archive_ = ext::ui::form(ui("#page_archive"));
    ui.cast(archive_progress_,"#page_archive_progress");
    ui.set_value("#output_dir",(ext::fs::home_path() / "Publish").u8string());
    init_actions();
}


///--------------------------
void software_release::init_actions()
{
    ui.on_click("#btn_create_archive",[this](auto){
        create_archive();
    });
}


///--------------------------
ext::text software_release::mime(const ext::fs::path& path)
{
    auto text = ext::ui::text(QMimeDatabase().mimeTypeForFile(ext::ui::string(path.u8string())).name());

    return text;
}


///--------------------------
bool software_release::is_windows_file(const ext::fs::path& path)
{
    auto extension = path.extension().string();

    if(boost::iequals(extension,".exe") || boost::iequals(extension,".dll") || boost::iequals(extension,".lib")){
        return true;
    }
    return false;
}

bool software_release::is_linux_file(const ext::fs::path& path)
{
    auto filename  = path.filename().string();
    auto extension = path.extension().string();

    for(auto ext : {".sh",".so",".a"})
    {
        if(boost::iequals(ext,extension)){
            return true;
        }
    }
    if(boost::icontains(filename,".so.") || boost::icontains(filename,".a.")){
        return true;
    }else if(extension.empty() && mime(path) == "application/x-executable"){
        return true;
    }
    return false;
}

bool software_release::is_ignore(const ext::fs::path& path,const std::vector<std::regex>& rules)
{
    auto filename = ext::text(path.filename().u8string());

    for(auto& regex : rules)
    {
        if(std::regex_match(filename.begin(),filename.end(),regex)){
            return true;
        }
    }
    return false;
}


///--------------------------
void software_release::on_archive_done(bool success)
{
    ui("#btn_create_archive")->object.enable(true);

    if(!success){
        ext::ui::alert("error","error",error_.message()).exec();
        return;
    }
    ext::ui::alert("info","OK","archive created").exec();
}

void software_release::on_zip_progress(const ext::archive::file_info_t& info,int64_t position)
{
    if(info.uncompressed_size == position){
        finished_size_archive_ += position;
    }
    auto percent = ext::percentage(finished_size_archive_ + position,total_size_archive_);

    ext::ui::post([this,percent]{
        archive_progress_->value(percent);
    });
}


///--------------------------
void software_release::create_archive()
{
    auto values     = form_archive_.values();
    auto name       = values["name"].text();
    auto dir        = values["dir"].text();
    auto version    = values["version"].number();
    auto output_dir = values["output_dir"].text();
    auto ignores    = std::vector<std::regex>();

    if(!ext::fs::exists(output_dir)){
        ext::fs::create_directories(output_dir);
    }
    if(name.empty() || output_dir.empty() || dir.empty() || !ext::fs::is_directory(output_dir,error_)){
        return;
    }
    name += "_" + ext::f2str(version,1);
    ui("#btn_create_archive")->object.enable(false);
    error_.clear();
    ext::parser::split_lines(values["ignore"].text_view(),[&](auto text,auto index)
    {
        try{
            std::regex regex(std::string(text),std::regex_constants::ECMAScript | std::regex_constants::optimize);
            ignores.emplace_back(std::move(regex));
        }catch(...){};

        return false;
    });
    archive_thread_ = std::thread([this,name,dir,output_dir,ignores = std::move(ignores)]
    {
        total_size_archive_    = 0;
        finished_size_archive_ = 0;

        auto result = create_archive(name,dir,output_dir,ignores);

        if(!closing_) ext::ui::post([this,result]{
            on_archive_done(result);
        });
    });
}

bool software_release::create_archive(const ext::text& name,const ext::fs::path& dir,const ext::fs::path& output_dir,const std::vector<std::regex>& ignores)
{
    paths_type directories;
    paths_type files_common;
    paths_type files_windows;
    paths_type files_linux;
    paths_type files_ignored;

    for(auto& entry : std::filesystem::recursive_directory_iterator(dir,error_))
    {
        Ext_Continue_If(is_ignore(entry.path(),ignores));

        if(entry.is_directory(error_)){
            directories.emplace_back(entry.path());
        }else if(entry.is_regular_file(error_)){
            if(is_windows_file(entry.path())){
                files_windows.emplace_back(entry.path());
            }else if(is_linux_file(entry.path())){
                files_linux.emplace_back(entry.path());
            }else{
                std::cout << entry.path() << std::endl;
                files_common.emplace_back(entry.path());
            }
            total_size_archive_ += entry.file_size(error_);
        }
        Ext_Break_If(error_);
    }
    std::pair<paths_type*,ext::text> pairs[2] = {{&files_windows,"_win_x64.zip"},{&files_linux,"_linux_x64.zip"}};

    for(auto& pair : pairs)
    {
        ext::archive::zip zip;

        if(!zip.open((const char*)(output_dir / (name + pair.second)).u8string().c_str(),ext::archive::Write | ext::archive::Create)){
            error_ = ext::make_error_code(ext::errors::Create_File_Error);
            return false;
        }
        zip.on_progress([this](const ext::archive::file_info_t& info,int64_t position){
            on_zip_progress(info,position);
            return 0;
        });
        if(!write_archive(zip,dir,directories,files_common,*pair.first)){
            error_ = ext::make_error_code(ext::errors::Write_File_Error);
            return false;
        }
    }
    return !error_;
}

bool software_release::write_archive(ext::archive::zip& zip,const ext::fs::path& dir,paths_type& directories,paths_type& paths,paths_type& paths_common)
{
    auto insert_file = [&](const auto& path)
    {
        if(!zip.add_file((const char*)path.u8string().c_str(),(const char*)path.lexically_relative(dir).u8string().c_str())){
            return false;
        }
        return true;
    };
    for(auto& path : paths)
    {
        if(closing_){
            return true;
        }
        if(!insert_file(path)){
           return false;
        }
    }
    for(auto& path : paths_common)
    {
        if(closing_){
            return true;
        }
        if(!insert_file(path)){
            return false;
        }
    }
    return true;
}


///--------------------------
void software_release::exec()
{
    dialog_->show();
}


}