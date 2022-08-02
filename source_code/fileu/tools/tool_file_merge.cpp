#include "tool_file_merge.h"

namespace pro::tools
{

file_merge::file_merge(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/tools/file_merge.sml")
{
    ui.cast(tab_,"#tab");
    ui.cast(normal_files_,"#normal_files");
    ui.cast(statusbar_,"#status");

    video_audio_form_ = ui("#video_audio_merge");
    dialog_->on_drop([this](auto files){
        normal_add(files);
    });
    dialog_->on_close([this](auto e)
    {
        state_ = ext::state::Stopping;

        if(process_.running()){
            process_.terminate();
            process_.join();
        }
        if(--refcount_ == 0){
            delete this;
        }
    });
    tab_->on_change([this](auto index){
        if(index == 1){
            detect_ffmpeg();
        }
    });
    init_actions();
}

file_merge::~file_merge()
{

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


    ui.on_click("#btn_video_audio_merge",[this](auto){
        video_audio_merge();
    });
}

///--------------------------
void file_merge::detect_ffmpeg()
{
#ifdef EXT_OS_WINDOWS
    constexpr std::string_view search_path[] = {"c:\\windows\\","c:\\windows\\system32","c:\\Program Files"};

    ext::text executable_name = ext::text("ffmpeg") + ".exe";
#else
    constexpr std::string_view search_path[] = {"/usr/bin","/usr/local/bin","/bin/"};

    ext::text executable_name = ext::text("ffmpeg");
#endif

    ext::error_code error;
    ext::text       executable;

    for(auto& path : search_path)
    {
        auto target            = ext::fs::path(path) / "ffmpeg";
        auto target_executable = ext::fs::path(path) / executable_name;

        if(ext::fs::exists(target_executable,error) && ext::fs::is_regular_file(target_executable,error)){
            executable = target_executable.u8string();
            break;
        }else if(ext::fs::is_directory(target,error) && ext::fs::is_regular_file(target / executable_name,error)){
            executable = (target / executable_name).u8string();
            break;
        }
    }
    if(!executable.empty()){
        video_audio_form_.values({
            {"ffmpeg_path",executable}
        });
    }
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
    ext::fs::path              save_path = ext::ui::file_dialog::save_file("save_file"_lang);
    std::vector<ext::fs::path> paths;

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
void file_merge::video_audio_merge()
{
    constexpr std::string_view path_names[] = {"ffmpeg_path","video_path","audio_path"};

    auto button     = ui.cast<ext::ui::button*>("#btn_video_audio_merge");
    auto error      = ext::error_code();
    auto values     = video_audio_form_.values();

    for(auto name : path_names)
    {
        ext::fs::path path(values[name].text());

        if(path.empty() || !ext::fs::is_regular_file(path,error)){
            ext::ui::alert("error","error"_lang,"file_path_error"_lang + " : "_text + path.u8string()).exec();
            return;
        }
    }
    ext::fs::path save_path = ext::ui::file_dialog::save_file("save_file"_lang);

    if(save_path.empty()){
        return;
    }
    button->setEnabled(false);

    process_.option(ext::process::New_Console);
    process_.start(values["ffmpeg_path"].text(),{
        "-i",
        values["video_path"].text(),
        "-i",
        values["audio_path"].text(),
        "-vcodec",
        "copy",
        "-acodec",
        "copy",
        ext::text(save_path.u8string())
    });
    process_.on_exit([this,button](auto code){
        button->setEnabled(true);
    });
}


///--------------------------
void file_merge::exec()
{
    refcount_++;
    dialog_->show();
}


}
