#include "tasks_confirm_http.h"

namespace pro::tasks
{

confirm_http::confirm_http(pro::global& global,ext::value& json,ext::func<void(int64_t,bool)>&& callback) :
    pro::dialog_sample<pro::global>(global,"ui/tasks/confirm_http.sml"),
    callback_(std::move(callback))
{
    form_ = ext::ui::form(ui.root());
    ui.cast(files_,"#files");
    ui.cast(proxy_combobox_,"#proxy");
    files_->icons(&zzz->icons_mime);

    init_ui();
}


///-------------------------------
void confirm_http::init_ui()
{
    ui.on_click("#without_confirm",[this](auto val){
        auto& config = zzz->configs["http_task"];
        config["without_confirm"] = val;
        zzz->send({{"@",protocol::Message_Config_Update},{"name","http_task"},{"config",config}});
    });
    ui.on_click("#download_later",[this](auto){
        on_download(true);
    });
    ui.on_click("#download_now",[this](auto){
        on_download(false);
    });
    dialog_->on_close([this](auto)
    {
        if(!destroying_)
        {
            if(!confirmed_){
                zzz->send({{"@",protocol::Message_Task_Remove},{"type",protocol::Task_HTTP},{"id",id_},{"delete_file",true}});
            }
            callback_(id_,confirmed_);
        }
        delete this;
    });
    files_->on_double_click([this](auto)
    {
        auto index = files_->current_index();
        auto input = zzz->messages()->input("#rename_task");

        if(input->exec(files_->text(index)) != 0)
        {
            if(auto new_name = input->value().text();!ext::fs::filename_valid(new_name)){
                ext::ui::alert("error","error"_lang,"invalid_name"_lang)();
            }else{
                values_["file_name"]        = new_name;
                values_["auto_rename_file"] = false;
                files_->text(index,"file_name",new_name);
                form_.values(ext::value{{"auto_rename_file",false}});
            }
        }
    });
    load_catalogs();
    load_proxies();
}


///-------------------------------
void confirm_http::on_download(bool later)
{
    auto values = ext::value({{"@",protocol::Message_Task_Confirm},{"type",protocol::Task_HTTP},{"id",id_}});
    values.merge(form_.values());

    if(values_.is_map()){
        values.merge(std::move(values_));
    }
    if(later){
        values["later"] = true;
    }
    zzz->send(values);
    confirmed_ = true;
    dialog_->close();
}


///-------------------------------
void confirm_http::load_catalogs()
{
    Ext_Return_If(!zzz->catalogs.is_map());

    auto combobox = ui.cast_id<ext::ui::combobox*>("catalog");

    for(auto& iter : *zzz->catalogs.cast_map()){
        combobox->append(iter.first.text(),iter.first.text());
    }
    combobox->on_index_change([this,combobox](auto index)
    {
        ext::text path;

        if(index == 0){
            path = zzz->configs["general"].text_view("default_save_path");
        }else if(auto name = combobox->item_text(index);zzz->catalogs.contains(name)){
            path = zzz->catalogs[name].text_view("path");
        }
        ui.set_value("#save_path",path);
    });
}

void confirm_http::load_proxies()
{
    if(zzz->proxies.is_map() && proxy_combobox_)
    {
        auto current = zzz->configs["network"].text("proxy");

        for(auto& iter : *zzz->proxies.cast_map())
        {
            proxy_combobox_->append(iter.first.text(),iter.first.text());

            if(iter.first.text() == current){
                proxy_combobox_->setCurrentIndex(proxy_combobox_->count() - 1);
            }
        }
    }
}


///-------------------------------
void confirm_http::update(ext::value& json)
{
    auto file_size = json.int64("file_size");

    if(file_size <= 0){
        json["file_size"] = ext::ui::lang("unknown");
    }
    auto node = files_->update_file(json,json.text_view("file_name"),json.text_view("file_path"),true);
    files_->type(ext::fs::file_type::regular,node);

    form_.values(json);
}

void confirm_http::exec(ext::value& json,uint16_t state)
{
    id_ = json.int64("id");
    dialog_->show_active();

    update(json);
}

void confirm_http::destroy()
{
    destroying_ = true;
    dialog_->close();
}


}