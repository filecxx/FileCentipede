#include "tasks_download_completed.h"

namespace pro::tasks
{

download_completed::download_completed(pro::global& global,std::int64_t id,ext::func_void<int64_t>&& callback) :
    pro::dialog_sample<ext::ui::frameless_dialog>(global,"ui/tasks/download_completed.sml"),
    id_(id),
    callback_(std::move(callback))
{
    form_ = ext::ui::form(ui.root());

    dialog_->on_close([this](auto){
        callback_(id_);
        delete this;
    });
    ui.on_click("#open",[this](auto){
        if(!save_path_.empty()){
            ext::ui::file_dialog::open_local_url((save_path_ / file_name_).u8string());
        }
        dialog_->close();
    });
    ui.on_click("#open_dir",[this](auto){
        if(!save_path_.empty()){
            ext::ui::file_dialog::reveal_file((save_path_ / file_name_).u8string());
        }
        dialog_->close();
    });
    ui.on_click("#no_completed_dialog",[this](auto val){
        zzz.setting("no_completed_dialog",val);
        dialog_->close();
    });
    timer_ = ext::ui::set_timeout([this]{
        timer_ = 0;
        dialog_->close();
    },10s);
}

download_completed::~download_completed()
{
    ext::ui::clear_timeout(timer_);
}


///---------------------------
void download_completed::exec(ext::value& values,const ext::text& error)
{
    if(error.empty()){
        ui.set_value("#status",ext::ui::lang("downloaded"));
    }else{
        ui.set_value("#status",error);
        ui("#open")->object.hide();
        ui("#open_dir")->object.hide();
        dialog_->add_class("error");
        dialog_->box_shadow("#ff3033");
    }
    file_name_ = values["file_name"].text();
    save_path_ = values["save_path"].text();

    ui.cast<ext::ui::img*>("#icon")->icon(zzz.icons_mime.mime(file_name_,24));
    form_.values(values);

    dialog_->setWindowFlags(dialog_->windowFlags() | Qt::Tool | Qt::X11BypassWindowManagerHint);
    dialog_->show_active();
    dialog_->move_to_south_east();
}


}