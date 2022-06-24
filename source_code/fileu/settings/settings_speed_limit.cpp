#include "settings_speed_limit.h"

namespace pro::settings
{

speed_limit::speed_limit(pro::global& global,const ext::text& type) : pro::dialog_sample<pro::global>(global,"ui/settings/speed_limit_" + type + ".sml"),type_(type)
{
    dialog_->on_close([this](auto){
        ext::ui::clear_timeout(timer_);
        delete this;
    });
    form_ = ext::ui::form(ui.root());

    ui.on_click("#save",[this](auto)
    {
        auto& config = zzz.configs["network"];

        config.merge(form_.values());

        zzz.send({{"@",protocol::Message_Config_Update},{"name","network"},{"config",config}});
        dialog_->close();
    });
}


///-------------------------
void speed_limit::start_timer()
{
    static ext::text default_titles[protocol::Task_Types_Size];

    if(auto& tasks_speed = zzz.status["tasks_speed_" + type_];tasks_speed.is_array())
    {
        for(auto i=0;auto& speed : *tasks_speed.cast_array())
        {
            auto value = ext::format_number("bytes/s",speed.number());
            auto group = ui.cast<ext::ui::group_box*>("#speed_" + ext::text(protocol::Task_Types_Text[i]));

            if(group)
            {
                if(default_titles[i].empty()){
                    default_titles[i] = group->title();
                }
                group->title(default_titles[i] + " - " + value);
            }
            ++i;
        }
    }
    timer_ = ext::ui::set_timeout([this]{
        start_timer();
    },500ms);
}


///-------------------------
void speed_limit::exec()
{
    start_timer();
    form_.values(zzz.configs["network"]);
    dialog_->exec();
}

}