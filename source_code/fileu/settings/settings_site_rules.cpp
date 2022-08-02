#include "settings_site_rules.h"

namespace pro::settings
{

site_rules_edit::site_rules_edit(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/settings/site_rules_edit.sml")
{
    ui.cast_id(protocol_,"protocol");
    ui.cast_id(config_,"config");
    ui.on_click("#save",[this](auto){
        on_save();
    });
    protocol_->on_change([this]{
        on_change();
    });
}


///-------------------
void site_rules_edit::on_change()
{
    auto protocol_name = protocol_->value().text();
    auto protocol      = protocol::task_type(protocol_name);
    auto prefix        = "#rule_"_text;

    if(!forms_[protocol])
    {
        auto proxy_combobox = ui.cast_id<ext::ui::combobox*>(protocol_name + "_proxy");

        forms_[protocol] = ext::ui::form(ui("#rule_" + protocol_name));
        forms_[protocol].values(zzz->task_config(protocol));

        if(zzz->proxies.is_map() && proxy_combobox)
        {
            for(auto& iter : *zzz->proxies.cast_map()){
                proxy_combobox->append(iter.first.text(),iter.first.text());
            }
        }
        if(values_.is_map() && values_["subtype"] == protocol_name && values_.get("config").is_map())
        {
            forms_[protocol].values(values_["config"]);

            for(auto& iter : *values_["config"].cast_map()){
                ui.set_value("#enable_" + protocol_name + "_" + iter.first.string(),true);
                forms_[protocol][iter.first.string()]->object.enable(true);
            }
        }
    }
    ui(prefix + protocol::Task_Types_Text[current_])->object.hide();
    ui(prefix + protocol::Task_Types_Text[current_ = protocol])->object.show();
}

void site_rules_edit::on_save()
{
    auto configs = ext::ui::form(ui("#rule_"_text + protocol::Task_Types_Text[current_]),true).values();
    auto values  = ext::ui::form(ui("#host")).values();

    if(values["host"].empty()){
        return;
    }
    if(configs.is_map()){
        values["config"] = configs;
    }
    if(id_ == 0){
        values["@"] = protocol::Message_Site_Rule_Add;
    }else{
        values["@"]  = protocol::Message_Site_Rule_Update;
        values["id"] = id_;
    }
    values["type"] = protocol::Site_Rule_File_Transfer;

    zzz.send(values);
    dialog_->close();
}


///-------------------
void site_rules_edit::add()
{
    on_change();
    dialog_->exec();
}

void site_rules_edit::edit(int64_t id,ext::value& values)
{
    id_     = id;
    values_ = values;
    ext::ui::form(ui("#host")).values(values_);
    on_change();
    dialog_->exec();
}


///-------------------------
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
    ui.on_action("#act_transfer_add",[this](auto){
        on_transfer_add();
    });
    ui.on_action("#act_transfer_edit",[this](auto){
        on_transfer_edit();
    });
    ui.on_action("#act_transfer_remove",[this](auto){
        on_transfer_remove();
    });
    ui.on_action("#act_transfer_copy",[this](auto){
        on_transfer_copy();
    });
    ui.on_action("#act_transfer_import",[this](auto){
        on_transfer_import();
    });
    ui.on_action("#act_transfer_export",[this](auto){
        on_transfer_export();
    });

    ui.on_click("#paste_rules",[this](auto){
        on_transfer_paste();
    });
}

void site_rules::init_messages()
{
    zzz.ipc_bind(protocol::Message_Site_Rule_Add,[this](auto& value)
    {
        auto id    = value.int64("id");
        auto cells = table_->create_row(value,id);

        table_->append_row(cells);
        zzz.site_rules[id] = value;
    });
    zzz.ipc_bind(protocol::Message_Site_Rule_Update,[this](auto& value)
    {
        auto id = value.int64("id");

        table_->each([&](auto index)
        {
            if(table_->row_data(index) == id){
                table_->siblings(index,value);
                zzz.site_rules[id] = value;
                return true;
            }
            return false;
        });
    });
    zzz.ipc_bind(protocol::Message_Site_Rule_Remove,[this](auto& value)
    {
        auto id = value.int64("id");

        table_->each([&](auto index)
        {
            if(table_->row_data(index) == id){
                table_->remove_row(index);
                return true;
            }
            return false;
        });
        zzz.site_rules.erase(id);
    });
}


///-------------------------
void site_rules::on_transfer_add()
{
    site_rules_edit(zzz).add();
}

void site_rules::on_transfer_edit()
{
    auto data = table_->current_row_data();

    if(!data.is_number()){
        return;
    }
    auto id = data.int64();

    if(auto iter = zzz.site_rules.find(id);iter != zzz.site_rules.end()){
        site_rules_edit(zzz).edit(id,iter->second);
    }
}

void site_rules::on_transfer_remove()
{
    for(auto& index : table_->selected_rows())
    {
        auto data = table_->row_data(index);
        auto id   = data.int64();

        if(auto iter = zzz.site_rules.find(id);iter != zzz.site_rules.end()){
            zzz.send({
                {"@",protocol::Message_Site_Rule_Remove},
                {"id",id},
                {"type",protocol::Site_Rule_File_Transfer},
                {"subtype",iter->second.get("subtype")}
            });
        }
    }
}

void site_rules::on_transfer_copy()
{
    ext::text text;

    for(auto& index : table_->selected_rows())
    {
        auto data = table_->row_data(index);

        if(auto iter = zzz.site_rules.find(data.int64());iter != zzz.site_rules.end()){
            ext::value value = iter->second;
            value.erase("id");
            text.append_line("1" + pro::uri::encode(value.stringify(),0));
        }
    }
    if(!text.empty()){
        ext::ui::clipboard::text(text);
    }
}

void site_rules::on_transfer_paste()
{
    auto node   = ui("#dialog_paste");
    auto values = ext::ui::form(node).values();

    ext::parser::split_lines(values.text_view("text"),[&](auto line,auto)
    {
        if(!line.empty() && line[0] == '1')
        {
            line.remove_prefix(1);
            uint8_t options;
            auto decoded = pro::uri::decode(line,options);

            if(decoded.size() > 2 && decoded.front() == '{' && decoded.back() == '}'){
                if(auto value = ext::json::parse(decoded);value.is_map()){
                    value["@"] = protocol::Message_Site_Rule_Add;
                    zzz.send(value);
                }
            }
        }
        return false;
    });
    ext::ui::methods::invoke(node->object,"close");
}

void site_rules::on_transfer_import()
{

}

void site_rules::on_transfer_export()
{

}


///-------------------------
void site_rules::exec()
{
    table_->clear_rows();

    for(auto& iter : zzz.site_rules)
    {
        if(iter.second.uint16("type") == protocol::Site_Rule_File_Transfer){
            auto cells = table_->create_row(iter.second,iter.first);
            table_->append_row(cells);
        }
    }
    dialog_->show_active();
}

}