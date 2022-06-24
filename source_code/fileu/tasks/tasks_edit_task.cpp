#include "tasks_edit_task.h"

namespace pro::tasks
{

edit_task::edit_task(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/tasks/edit_task.sml")
{
    dialog_->on_close([this](auto){
        delete this;
    });
    ui.on_click("#save",[this](auto){
        on_save();
    });
}

edit_task::~edit_task()
{

}


///--------------------------
void edit_task::on_save()
{
    auto values = form_.values();
    values["@"]    = protocol::Message_Task_Edit;
    values["id"]   = id_;
    values["type"] = type_;

    zzz->send(values);
    dialog_->close();
}


///--------------------------
void edit_task::init_default_values(const ext::text& type)
{
    auto catalog_combobox = ui.cast_id<ext::ui::combobox*>(type + "_catalog");
    auto proxy_combobox   = ui.cast_id<ext::ui::combobox*>(type + "_proxy");

    if(zzz->catalogs.is_map())
    {
        for(auto& iter : *zzz->catalogs.cast_map()){
            catalog_combobox->append(iter.first.text(),iter.first.text());
        }
    }
    if(zzz->proxies.is_map() && proxy_combobox)
    {
        for(auto& iter : *zzz->proxies.cast_map()){
            proxy_combobox->append(iter.first.text(),iter.first.text());
        }
    }
}


///--------------------------
void edit_task::exec(ext::value& json)
{
    std::string file_path;
    std::string type(protocol::Task_Types_Text[type_ = json.uint16("type")]);

    if(type.empty()){
        return delete this;
    }
    auto tab = ui.cast<ext::ui::tab*>("#central_widget");
    {
        ui.import(ui("#sml_files")->value(type).string());
        tab->layout(0,ui("#" + type)->object);
    }
    auto no_task_record = ui("#" + type + "_no_task_record");
    auto combobox_node  = ui("#" + type + "_uri");
    auto combobox       = combobox_node->object.cast<ext::ui::combobox*>();

    init_default_values(type);

    if(no_task_record){
        no_task_record->object.hide();
    }
    combobox->hide();

    id_   = json.int64("id");
    form_ = ext::ui::form(ui.root());
    form_.values(json);
    form_["uri"]->object.cast<ext::ui::text_edit*>()->setReadOnly(type_ == protocol::Task_Torrent || type_ == protocol::Task_Ed2k);
    form_["file_name"]->object.cast<ext::ui::line_edit*>()->setReadOnly(true);
    form_["save_path"]->object.cast<ext::ui::combobox*>()->lineEdit()->setReadOnly(true);

    dialog_->show();
}


}