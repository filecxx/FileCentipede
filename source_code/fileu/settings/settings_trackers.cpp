#include "settings_trackers.h"

namespace pro::settings
{

trackers::trackers(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/settings/tracker.sml")
{
    form_       = ext::ui::form(ui("#tab_settings"));
    subscribes_ = ui.cast_id<ext::ui::table*>("subscribes");

    init_events();
    init_actions();
    init_messages();
}


///-------------------------
void trackers::init_events()
{
    ui.on_click("#save",[this]{
        zzz.send({{"@",protocol::Message_Config_Update},{"name","trackers"},{"config",ext::value::merge(zzz.configs["trackers"],form_.values())}});
        dialog_->close();
    });
    subscribes_->on_context_menu([this]
    {
        auto id = subscribes_->current_row_data();

        for(auto& name : std::initializer_list<ext::text>{"edit_subscribe","remove_subscribe","update_trackers"}){
            ui.cast_id<ext::ui::action*>(ext::text("act_") + name)->enable(id.is_number());
        }
        subscribes_->show_context_menu();
    });
}

void trackers::init_actions()
{
    auto dialog = ui.cast_id<ext::ui::edit_dialog*>("dialog_subscribe");

    dialog->on_add([this](auto&& values)
    {
        ext::parser::split_lines(values.text_view("url"),[&](auto url,auto){
            zzz.send({{"@",protocol::Message_Subscribe_Add},{"type",protocol::Subscribe_Trackers},{"url",url}});
            return false;
        });
    });
    dialog->on_edit([this](auto&& values,auto id){
        zzz.send(ext::value::merge(values,{{"@",protocol::Message_Subscribe_Update},{"type",protocol::Subscribe_Trackers},{"id",id}}));
    });
    ui.on_action_id("act_edit_subscribe",[this,dialog](auto)
    {
        auto id = subscribes_->current_row_data();

        if(id.is_number() && zzz.subscribes.contains(id.int64())){
            dialog->edit(zzz.subscribes[id.int64()],id);
        }
    });
    ui.on_action_id("act_remove_subscribe",[this](auto)
    {
        for(auto data : subscribes_->selected_rows_data()){
            zzz.send({{"@",protocol::Message_Subscribe_Remove},{"type",protocol::Subscribe_Trackers},{"id",data}});
        }
    });
}

void trackers::init_messages()
{
    zzz.ipc_bind(protocol::Message_Subscribe_Update_Trackers,[this](ext::value& json){
        zzz.send({{"@",protocol::Message_Trackers}});
    });
}


///-------------------------
void trackers::subscribe_add(ext::value& json)
{
    auto cells = subscribes_->create_row(json,json.uint16("id"));
    subscribes_->append_row(cells);
}

void trackers::subscribe_update(ext::value& json,std::int64_t id)
{
    subscribes_->each([&](auto index)
    {
        if(subscribes_->data(index,0) == id){
            subscribes_->siblings(index,json);
            return true;
        }
        return false;
    });
}

void trackers::subscribe_remove(ext::value& json,std::int64_t id)
{
    subscribes_->each([&](auto index)
    {
        if(subscribes_->data(index,0) == id){
            subscribes_->remove_row(index);
            return true;
        }
        return false;
    });
}


///-------------------------
void trackers::update(ext::value& json)
{
    auto now = ext::time::system_now_count();

    subscribes_->each([&](auto index){
        //subscribes_->sibling(index,"uptime",ext::format_number("datetime",now));
        return false;
    });
    ui.set_value("#trackers_list",json.string_view("content"));
}

void trackers::exec()
{
    subscribes_->clear_rows();

    for(auto& iter : zzz.subscribes)
    {
        if(iter.second.uint16("type") == protocol::Subscribe_Trackers){
            auto cells = subscribes_->create_row(iter.second,iter.first);
            subscribes_->append_row(cells);
        }
    }
    form_.values(zzz.configs["trackers"]);
    dialog_->show_active();
    zzz.send({{"@",protocol::Message_Trackers}});
}


}
