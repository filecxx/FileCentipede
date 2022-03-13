#include "tool_create_torrent.h"

namespace pro::tools
{

create_torrent::create_torrent(pro::global& global) : pro::dialog_sample(global,"ui/tools/create_torrent.sml")
{
    form_ = ext::ui::form(ui("#main"));
    dialog_->on_close([this](auto e){
        zzz.ipc_unbind(xid_);
        delete this;
    });
    init_values();
    init_actions();
    init_catalogs();
}


///--------------------------
void create_torrent::init_values()
{
    form_.values({
        {"creator",pro::Client_Full_Name},
        {"trackers",zzz.configs["trackers"]["new_task_trackers"]}
    });
}

void create_torrent::init_actions()
{
    ui.on_click("#btn_create",[this](auto){
        create();
    });
}

void create_torrent::init_catalogs()
{
    Ext_Return_If(!zzz.catalogs.is_map());

    auto combobox = ui.cast_id<ext::ui::combobox*>("catalog");

    for(auto& iter : *zzz.catalogs.cast_map()){
        combobox->append(iter.first.text(),iter.first.text());
    }
}


///--------------------------
void create_torrent::create()
{
    auto values = form_.values();
    auto path   = values.text("path");

    if(path.empty()){
        return;
    }
    if(auto text = ext::ui::file_dialog::save_file({},ext::text(ext::fs::path(path).filename().u8string() + u8".torrent"),"*.torrent");!text.empty())
    {
        ui("#btn_create")->object.enable(false);
        ui("#btn_cancel")->object.enable(false);

        if(!ext::fs::path(text).has_extension()){
            text += ".torrent";
        }
        zzz.ipc_xbind(xid_,[this](auto& value)
        {
            auto error   = value.int32("error");
            auto message = value.text("message");

            if(error == 0){
                dialog_->close();
            }else{
                ext::ui::alert("error",ext::ui::lang("error"),global::error_text(error) + " " + message).exec();
                ui("#btn_create")->object.enable(true);
                ui("#btn_cancel")->object.enable(true);
            }
        });
        values["@"]         = protocol::Message_Torrent_Create;
        values["xid"]       = xid_;
        values["save_path"] = text;
        zzz.send(values);
    }
}


///--------------------------
void create_torrent::exec()
{
    dialog_->show();
}


}