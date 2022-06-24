#include "tool_file_merge.h"

namespace pro::tools
{

file_merge::file_merge(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/tools/file_merge.sml")
{
    ui.cast(normal_files_,"#normal_files");
    ui.cast(statusbar_,"#status");

    dialog_->on_drop([this](auto files){
        normal_add(files);
    });
    dialog_->on_close([this](auto e)
    {
        state_ = ext::state::Stopping;

        if(--refcount_ == 0){
            delete this;
        }
    });
    init_actions();

}


///--------------------------
void file_merge::init_actions()
{
    ui.on_action("#act_normal_add",[this](auto){
        normal_add();
    });
    ui.on_action("#act_normal_remove",[this](auto){
        normal_remove();
    });
    ui.on_action("#act_normal_clear",[this](auto){
        normal_clear();
    });
    ui.on_action("#act_normal_merge",[this](auto){
        normal_merge();
    });

}


///--------------------------
void file_merge::merge_normal_files(ext::cfile&& file,const std::vector<ext::fs::path>& paths)
{
    auto show_error = [&](auto text,auto path)
    {
        ext::ui::post([this,text,path]{
            ext::ui::alert("error","error"_lang,ext::text(ext::ui::lang(text)) + " : " + ext::text(path.u8string())).exec();
            merge_done();
        });
    };
    auto finished_bytes = std::int64_t(0);
    auto handler        = [&](auto bytes){
        finished_bytes += bytes;
        return false;
    };
    for(auto& path : paths)
    {
        ext::file_mapping in;

        if(!in.open(path,true)){
            return show_error("open_file_error",path);
        }
        if(!file.write(in.data(),in.size(),handler)){
            return show_error("write_file_error",path);
        }
        if(state_ != ext::state::Running){
            break;
        }
    }
    ext::ui::post([this]{
        statusbar_->message("merge_success"_lang);
        merge_done();
    });
}


///--------------------------
void file_merge::merge_done()
{
    if(--refcount_ == 0){
        delete this;
    }else{
        enable_normal_actions(true);
    }
}

void file_merge::enable_normal_merge_action()
{
    auto action = ui.cast<ext::ui::action*>("#act_normal_merge");

    action->enable(normal_files_->row_count() != 0);
}

void file_merge::enable_normal_actions(bool enable)
{
    for(auto name : std::initializer_list<ext::text_view>{"add","remove","clear","merge"}){
        auto action = ui.cast<ext::ui::action*>(ext::text("#act_normal_") + name);
        action->enable(enable);
    }
}


///--------------------------
void file_merge::normal_add(const std::vector<ext::text>& files)
{
    auto error = std::error_code();

    for(auto& file : files)
    {
        auto path = ext::fs::path(file);
        auto size = ext::fs::file_size(path,error);

        if(size > 0){
            normal_files_->append_row({{"size",ext::format_number("bytes",size)},{"path",path.u8string()}});
        }
    }
    enable_normal_merge_action();
}

void file_merge::normal_add()
{
    normal_add(ext::ui::file_dialog::open_files("open_file"_lang));
}

void file_merge::normal_remove()
{
    normal_files_->remove_selected_rows();
    enable_normal_merge_action();
}

void file_merge::normal_clear()
{
    normal_files_->clear_rows();
    enable_normal_merge_action();
}

void file_merge::normal_merge()
{
    ext::cfile                 file;
    std::vector<ext::fs::path> paths;
    ext::fs::path              save_path = ext::ui::file_dialog::save_file("save_file"_lang);

    if(save_path.empty()){
        return;
    }
    if(!file.open(save_path,"wb")){
        ext::ui::alert("error","error"_lang,"create_file_error"_lang).exec();
        return;
    }
    normal_files_->each([&](auto index)
    {
        if(auto text = normal_files_->sibling_text(index,"path");!text.empty()){
            paths.emplace_back(text);
        }
        return false;
    });
    if(!paths.empty())
    {
        refcount_++;
        enable_normal_actions(false);
        zzz.io_worker()->post([this,file = std::move(file),paths = std::move(paths)]() mutable{
            merge_normal_files(std::move(file),paths);
        });
    }
}


///--------------------------
void file_merge::exec()
{
    refcount_++;
    dialog_->show();
}


}
