#include "tasks_edit_task.h"

namespace pro::tasks
{

edit_task::edit_task(pro::global& global) : pro::dialog_sample<>(global,"ui/tasks/edit_task.sml")
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

    zzz.send(values);

    dialog_->close();
}


///--------------------------
void edit_task::init_default_values(const ext::text& type)
{
    auto catalog_combobox = ui.cast_id<ext::ui::combobox*>(type + "_catalog");
    auto proxy_combobox   = ui.cast_id<ext::ui::combobox*>(type + "_proxy");

    if(zzz.catalogs.is_map())
    {
        for(auto& iter : *zzz.catalogs.cast_map()){
            catalog_combobox->append(iter.first.text(),iter.first.text());
        }
    }
    if(zzz.proxies.is_map() && proxy_combobox)
    {
        auto current = zzz.configs["network"].text("proxy");

        for(auto& iter : *zzz.proxies.cast_map())
        {
            proxy_combobox->append(iter.first.text(),iter.first.text());

            if(iter.first.text() == current){
                proxy_combobox->setCurrentIndex(proxy_combobox->count() - 1);
            }
        }
    }
}


///--------------------------
std::string_view edit_task::type(std::uint16_t n)
{
    switch(n)
    {
    case protocol::Task_HTTP:
    case protocol::Task_FTP:
    case protocol::Task_Torrent:
    case protocol::Task_Ed2k:
        return protocol::Task_Types_Text[n];
    case protocol::Task_Stream:
        return protocol::Task_Types_Text[protocol::Task_HTTP];
    }
    return {};
}


///--------------------------
void edit_task::exec(ext::value& json)
{
    std::string file_path;
    std::string type(this->type(type_ = json.uint16("type")));

    if(type.empty()){
        return delete this;
    }
    ui.import(ui("#sml_files")->value(type).string());
    ui.cast<ext::ui::widget*>("#central_widget")->layout(ui("#" + type)->object);
    init_default_values(type);

    auto combobox_node = ui("#" + type + "_uri");
    auto combobox      = combobox_node->object.cast<ext::ui::combobox*>();

    combobox->setEditable(true);
    combobox->lineEdit()->setReadOnly(true);
    combobox->hide();
    combobox_node->pairs.emplace("name","uri");

    id_   = json.int64("id");
    form_ = ext::ui::form(ui.root());
    form_.values(json);
    form_["file_name"]->object.cast<ext::ui::line_edit*>()->setReadOnly(true);
    form_["save_path"]->object.cast<ext::ui::combobox*>()->lineEdit()->setReadOnly(true);

    dialog_->show();
}


}