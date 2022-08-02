#include "catalogs_main.h"

namespace pro::catalogs
{

main::main(pro::global& global,ext::ui::list* list) : pro::sample<>(global,"ui/catalogs/main.sml")
{
    list_         = list;
    context_menu_ = ui.cast_id<ext::ui::menu*>("context_menu");

    init_actions();
}


///-------------------
void main::init_actions()
{
    ui.on_action_id("act_add",[this](auto checked){
        (new catalogs::edit(zzz))->exec();
    });
    ui.on_action_id("act_edit",[this](auto checked)
    {
        for(auto item : list_->selected_items())
        {
            if(item != list_->item(0)){
                (new catalogs::edit(zzz))->exec(item->text());
            }
        }
    });
    ui.on_action_id("act_delete",[this](auto checked){
        remove_catalog();
    });
    ui.on_action_id("act_merge",[this](auto checked){
        merge_catalogs();
    });
}


///-------------------
void main::remove_catalog()
{
    auto alert_type = zzz.settings.get("alert_delete_catalog");
    auto result     = ext::value(0);

    if(alert_type.is_number() && alert_type != 0){
        result = alert_type.number();
    }else{
        result = zzz.messages()->alert("#delete_catalog")->call();
    }
    if(result.is_number() && result != 0) for(auto item : list_->selected_items())
    {
        if(item != list_->item(0)){
            zzz.send({{"@",protocol::Message_Catalog_Remove},{"name",item->text()},{"operation",result}});
        }
    }
}

void main::merge_catalogs()
{
    auto dialog = ui.cast<ext::ui::input_dialog*>("#merge_dialog");
    auto target = ext::text();
    auto names  = ext::value::array_type();
    auto items  = ext::value::array_type();

    list_->each([&](auto i,auto item)
    {
        if(item != list_->item(0)){
            items.push_back(item->text());
        }
        return false;
    });
    for(auto item : list_->selected_items())
    {
        if(item != list_->item(0)){
            names.emplace_back(item->text());
        }
    }
    if(dialog->items(items);names.size() >= 2 && dialog->exec() != 0)
    {
        if(auto target = dialog->value();!target.empty()){
            zzz.send({{"@",protocol::Message_Catalog_Merge},{"target",target},{"names",ext::value(std::move(names))}});
        }
    }
}


///-------------------
void main::show_context_menu(int32_t row)
{
    if(row != 0){
        context_menu_->show_context_menu();
    }
}

}