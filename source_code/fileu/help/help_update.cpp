#include "help_update.h"

namespace pro::help
{

update::update(pro::global& global) : pro::dialog_sample<>(global,"ui/help/update.sml")
{
    dialog_->on_close([this](auto){
        ext::ui::clear_timeout(timer_);
        save_settings();
    });
    form_info_    = ext::ui::form(ui("#page_update"));
    form_source_  = ext::ui::form(ui("#page_source"));
    form_setting_ = ext::ui::form(ui("#settings"));
    init_messages();
}


///--------------------------
void update::init_messages()
{
    zzz.ipc_bind(protocol::Message_Update_Checked,[this](auto& value){
        set_info(value);
    });
    zzz.ipc_bind(protocol::Message_Update_Status,[this](auto& value){
        set_info(value);
    });
}


///--------------------------
void update::start_timer()
{
    timer_ = ext::ui::set_timeout([this]{
        Ext_Return_If(timer_ == 0);
        timer_ = 0;
        zzz.send({{"@",protocol::Message_Update_Status}});
        start_timer();
    },1s);
}


///--------------------------
void update::save_settings()
{
    auto& upgrade = zzz.configs["upgrade"];
    auto& source  = zzz.configs["upgrade_source"];

    upgrade.merge(form_setting_.values());
    source.merge(form_source_.values());

    zzz.send({{"@",protocol::Message_Config_Update},{"name","upgrade"},{"config",upgrade}});
    zzz.send({{"@",protocol::Message_Config_Update},{"name","upgrade_source"},{"config",source}});
}

void update::set_info(ext::value& values)
{
    auto& state            = values["state"];
    auto  btn_check_update = ui("#check_update");
    auto  btn_upgrade      = ui("#upgrade");
    bool  enabled[2]       = {false,false};

    if(state == "none"){
        enabled[0] = true;
    }else if(state == "checked"){
        enabled[0] = true;
        enabled[1] = true;
    }
    state = ext::ui::lang(state.text_view());
    btn_check_update->object.enable(enabled[0]);
    btn_upgrade->object.enable(enabled[1]);
    form_info_.values(values);
}


///--------------------------
void update::exec()
{
    auto upgrade        = zzz.configs["upgrade"];
    auto upgrade_source = zzz.configs["upgrade_source"];

    form_source_.values(upgrade_source);
    zzz.send({{"@",protocol::Message_Update_Status}});
    start_timer();

    dialog_->show_active();
}



}
