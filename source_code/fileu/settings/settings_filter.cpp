#include "settings_filter.h"

namespace pro::settings
{

filter::filter(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/settings/filter.sml")
{
    form_                 = ext::ui::form(ui("#main"));
    torrent_files_filter_ = ui.cast_id<ext::ui::table*>("torrent_files_filter");

    init_events();
    init_actions();
}


///-------------------------
void filter::init_events()
{
    ui.on_click("#save",[this]
    {
        auto& filters = zzz.configs["filters"];
        zzz.send({{"@",protocol::Message_Config_Update},{"name","filters"},{"config",ext::value::merge(filters,form_.values())}});
        dialog_->close();
    });
    torrent_files_filter_->on_context_menu([this]
    {
        auto id = torrent_files_filter_->current_index();

        for(auto& name : std::initializer_list<ext::text>{"edit","remove"}){
            ui.cast_id<ext::ui::action*>(ext::text("act_") + name)->setEnabled(id.isValid());
        }
        torrent_files_filter_->show_context_menu();
    });
}

void filter::init_actions()
{
    auto dialog = ui.cast<ext::ui::edit_dialog*>("#dialog_torrent_files_filter");

    dialog->on_add([this](auto&& values){
        if(!values["rule"].empty()){
            torrent_files_filter_->append_row(values);
        }
    });
    dialog->on_edit([this](auto&& values,ext::value_view index){
        torrent_files_filter_->siblings(*index.cast<QModelIndex*>(),values);
    });
    ui.on_action_id("act_add",[this,dialog](auto){
        dialog->add();
    });
    ui.on_action_id("act_edit",[this,dialog](auto){
        auto index = torrent_files_filter_->current_index();
        dialog->edit(torrent_files_filter_->cells_text(index),&index);
    });
}


///-------------------------
void filter::exec()
{
    form_.values(zzz.configs["filters"]);
    dialog_->show_active();
}



}