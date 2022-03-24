#include "settings_proxies.h"

namespace pro::settings
{

proxies::proxies(pro::global& global) : pro::dialog_sample<>(global,"ui/settings/proxy.sml")
{
    table_ = ui.cast_id<ext::ui::table*>("proxies");
    table_->on_context_menu([this]{
        if(table_->has_selection()){
            table_->show_context_menu();
        }
    });
    init_events();
    init_messages();
}


///-------------------------
void proxies::init_events()
{
    auto dialog = ui.cast<ext::ui::edit_dialog*>("#dialog_edit");

    dialog->on_add([this](auto&& values)
    {
        auto name = values.text("name");

        if(!name.empty() && !values["host"].empty() && !zzz.proxies.contains(name)){
            values["@"] = protocol::Message_Proxy_Add;
            zzz.send(values);
        }
    });
    dialog->on_edit([this](auto&& values,auto name){
        values["@"]    = protocol::Message_Proxy_Update;
        values["name"] = name;
        zzz.send(values);
    });

    ui.on_action("#act_proxy_add",[this,dialog](auto)
    {
        dialog->form()["name"]->object.enable(true);
        dialog->form().values({{"name","Proxy" + std::to_string(zzz.proxies.size() + 1)}});

        dialog->add();
    });
    ui.on_action("#act_proxy_edit",[this,dialog](auto){
        auto name   = table_->current_text("name");
        auto values = ext::value({{"name",name}});

        dialog->form()["name"]->object.enable(false);
        dialog->edit(ext::value::merge(values,ext::value(zzz.proxies[name.string_view()])),name);
    });
    ui.on_action("#act_proxy_remove",[this](auto)
    {
        for(auto& index : table_->selected_rows()){
            zzz.send({{"@",protocol::Message_Proxy_Remove},{"name",table_->sibling_text(index,"name")}});
        }
    });
    ui.on_action("#act_proxy_import",[this](auto){
        imports();
    });
    ui.on_action("#act_proxy_export",[this](auto){
        exports();
    });
    ui.on_action("#act_proxy_test",[this](auto){
        test();
    });
}

void proxies::init_messages()
{
    zzz.ipc_bind(protocol::Message_Proxy_Add,[this](auto& value)
    {
        zzz.proxies[value.text("name")] = value;
        table_->append_row(value);
    });
    zzz.ipc_bind(protocol::Message_Proxy_Update,[this](auto& value)
    {
        auto name = value.text("name");

        table_->each([&](auto index)
        {
            if(table_->sibling_text(index,"name") == name){
                table_->siblings(index,value);
                zzz.proxies[name] = value;
                return true;
            }
            return false;
        });
    });
    zzz.ipc_bind(protocol::Message_Proxy_Remove,[this](auto& value)
    {
        auto name = value.text("name");

        if(name == zzz.configs["network"].text("proxy")){
            zzz.configs["network"]["proxy"] = "";
        }
        table_->each([&](auto index)
        {
            if(table_->sibling_text(index,"name") == name){
                table_->remove_row(index);
                return true;
            }
            return false;
        });
        zzz.proxies.erase(name);
    });
    zzz.ipc_bind(protocol::Message_Proxy_Test,[this](ext::value& value)
    {
        table_->each([&](auto index)
        {
            if(table_->sibling_text(index,"name") == value.text_view("name")){
                bool success = value.get("success") == true;

                table_->row_color(index,success? "green" : "red");
                table_->sibling(index,"state",success ? value.get("elapse").stringify() + " ms" : "");
                return true;
            }
            return false;
        });
    });
}


///-------------------------
void proxies::imports()
{

}

void proxies::exports()
{

}

void proxies::test()
{
    ext::ui::input_dialog dialog;
    dialog.value("https://www.w3.org/");
    dialog.label(ext::ui::lang("target"));

    if(dialog.exec() != 0){
        zzz.send({{"@",protocol::Message_Proxy_Test},{"target",dialog.value()}});
    }
}


///-------------------------
void proxies::exec()
{
    table_->clear_rows();

    if(zzz.proxies.is_map())
    {
        for(auto& iter : *zzz.proxies.cast_map()){
            ext::value row = iter.second;
            row["name"] = iter.first.string_view();
            table_->append_row(table_->create_row(row));
        }
    }
    dialog_->show_active();
}


}