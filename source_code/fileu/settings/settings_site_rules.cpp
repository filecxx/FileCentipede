#include "settings_site_rules.h"

namespace pro::settings
{

site_rules::site_rules(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/settings/site_rules.sml")
{
    table_ = ui.cast_id<ext::ui::table*>("sites");
    table_->on_context_menu([this]
    {
        if(table_->has_selection()){
            table_->show_context_menu();
        }
    });
    init_events();
    init_messages();
}


///-------------------------
void site_rules::init_events()
{

}

void site_rules::init_messages()
{

}


///-------------------------
void site_rules::exec()
{
    table_->clear_rows();


    dialog_->show_active();
}

}