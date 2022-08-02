#include "tasks_add_task.h"

namespace pro::tasks
{

add_task::add_task(pro::global& global,ext::boolean_t is_stream,ext::boolean_t is_directory) :
    pro::dialog_sample<pro::global>(global,"ui/tasks/add_task.sml"),
    is_stream_(is_stream),
    is_directory_(is_directory)
{
    dialog_->on_close([this](auto){
        ext::invoke(on_delete_);
        delete this;
    });
    placeholders_ = ui("#placeholders");
    ui.cast(addresses_,"#addresses");
    ui.cast(tab_,"#tab");

    auto placeholder = "file";

    if(is_stream){
        placeholder = "m3u8";
    }else if(is_directory){
        placeholder = "directory";
    }
    addresses_->setPlaceholderText(ext::ui::string(placeholders_->value(placeholder).text_view()));
}

add_task::~add_task()
{
    ext::ui::clear_timeout(timer_);
}


///--------------------------
void add_task::analyze_addresses()
{
    ext::text protocol;
    ext::parser::split_lines(addresses_->text(),[&](auto& line,auto n)
    {
        if(auto address = boost::trim_copy(line);!address.empty())
        {
            pro::uri uri;

            if(!uri.analyze(address,ext::Map)){
                return false;
            }
            if(is_stream_)
            {
                if(uri.type != protocol::Task_HTTP){
                    return false;
                }
                uri.type = protocol::Task_Stream;
            }else if(is_directory_){
                if(uri.type != protocol::Task_HTTP && uri.type != protocol::Task_FTP && uri.type != protocol::Task_SSH){
                    return false;
                }
            }
            auto key = uri.config.text("uri");
            uris_.emplace(std::move(key),config_t{uri.type,std::move(uri.config)});
        }
        return false;
    });
    for(auto iter=configs_.begin();iter != configs_.end();)
    {
        if(uris_.contains(iter->first)){
            ++iter;
            continue;
        }
        combobox_configs_[iter->second.type]->remove(iter->first);
        configs_.erase(iter++);
    }
    for(auto& iter : uris_)
    {
        auto type = iter.second.type;

        if(configs_.contains(iter.first)){
            continue;
        }
        if(!combobox_configs_[type]){
            ui.import(tab_->item_data(type + 1).string());
            init_form(ext::text(protocol::Task_Types_Text[type]),type);
        }
        ext::value values = default_values_[type];

        if(type == protocol::Task_HTTP || type == protocol::Task_FTP || type == protocol::Task_SSH){
            zzz.task_config(type,iter.first,values);
        }
        values.merge(std::move(iter.second.values));
        values["uri"] = iter.first;

        configs_.emplace(iter.first,config_t{type,std::move(values)});
        combobox_configs_[type]->append(iter.first);
    }
    for(int i=0;i<combobox_configs_.size();++i){
        if(combobox_configs_[i]){
            tab_->visible(i + 1,combobox_configs_[i]->count() != 0);
        }
    }
    uris_.clear();
    cached_uris_.clear();
}

void add_task::download(bool immediately)
{
    analyze_addresses();

    for(auto& iter : configs_)
    {
        if(!immediately){
            iter.second.values["later"] = true;
        }
        if(iter.second.type != protocol::Task_Torrent){
            iter.second.values["without_confirm"] = true;
        }
        if(is_directory_)
        {
            uint32_t mode = 0;

            if(auto val = iter.second.values.get("mode");val.is_number()){
                mode = val.uint32();
            }
            iter.second.values["mode"] = mode | protocol::Task_Mode_Directory;
        }
        zzz->send(iter.second.values.stringify());
    }
    dialog_->close();
}

void add_task::change_save_path(const ext::text& path)
{
    default_save_path_ = path;

    for(auto& value : default_values_){
        if(value.is_map()){
            value["save_path"] = path;
        }
    }
    for(auto& config : configs_){
        if(config.second.values.is_map()){
            config.second.values["save_path"] = path;
        }
    }
    for(auto& form : forms_){
        if(form){
            form.values({{"save_path",path}});
        }
    }
}


///--------------------------
void add_task::init_widget(const ext::text& name,std::uint16_t config_type,ext::ui::object& object)
{
    auto on_value_change = [this](std::uint8_t type,const ext::text& name,const ext::value& value)
    {
        if(auto config = current_configs_[type];config){
            config->values[name] = value;
        }
    };
    switch(object.type())
    {
    case ext::ui::CheckBox:
        object.cast<ext::ui::checkbox*>()->on_toggle([on_value_change,config_type,name,object](bool val){
            on_value_change(config_type,name,val);
        });
        break;
    case ext::ui::ComboBox:
        object.cast<ext::ui::combobox*>()->on_change([on_value_change,config_type,name,object](auto& str){
            on_value_change(config_type,name,object.cast<ext::ui::combobox*>()->value());
        });
        break;
    case ext::ui::LineEdit:
        object.cast<ext::ui::line_edit*>()->on_change([on_value_change,config_type,name](auto& str){
            on_value_change(config_type,name,ext::ui::text(str));
        });
        break;
    case ext::ui::TextEdit:
        object.cast<ext::ui::text_edit*>()->on_change([on_value_change,config_type,name](auto& str){
            on_value_change(config_type,name,str);
        });
        break;
    case ext::ui::SpinBox:
        object.cast<ext::ui::spinbox*>()->on_change([on_value_change,config_type,name](int val){
            on_value_change(config_type,name,val);
        });
        break;
    case ext::ui::DoubleSpinBox:
        object.cast<ext::ui::double_spinbox*>()->on_change([on_value_change,config_type,name](double val){
            on_value_change(config_type,name,val);
        });
        break;
    }
}

void add_task::init_form(const ext::text& name,uint16_t type)
{
    auto layout           = ui.query('#' + name);
    auto catalog_combobox = ui.cast_id<ext::ui::combobox*>(name + "_catalog");
    auto proxy_combobox   = ui.cast_id<ext::ui::combobox*>(name + "_proxy");

    tab_->layout(type + 1,layout->object);
    forms_[type] = ext::ui::form(layout);
    forms_[type].each([this,type](auto& name,ext::ui::node_t* node){
        init_widget(name,type,node->object);
        return false;
    });
    combobox_configs_[type] = ui.cast_id<ext::ui::combobox*>(name + "_uri");
    combobox_configs_[type]->on_text_change([this,type](auto text)
    {
        auto uri    = ext::ui::text(text);
        auto config = uri.empty() ? nullptr : &configs_[uri];

        current_configs_[type] = config;

        if(config){
            forms_[type].values(config->values);
        }
    });
    if(zzz->proxies.is_map() && proxy_combobox)
    {
        auto current = zzz->configs["network"].text("proxy");

        for(auto& iter : *zzz->proxies.cast_map())
        {
            proxy_combobox->append(iter.first.text(),iter.first.text());

            if(iter.first.text() == current){
                proxy_combobox->setCurrentIndex(proxy_combobox->count() - 1);
            }
        }
    }
    if(zzz->catalogs.is_map())
    {
        for(auto& iter : *zzz->catalogs.cast_map()){
            catalog_combobox->append(iter.first.text(),iter.first.text());
        }
        catalog_combobox->on_index_change([this,type,catalog_combobox](auto index)
        {
            ext::text path;

            if(index == 0){
                path = default_save_path();
            }else if(auto name = catalog_combobox->item_text(index);zzz->catalogs.contains(name)){
                path = zzz->catalogs[name].text_view("path");
            }
            forms_[type].values({{"save_path",path}});
        });
    }
    auto values = forms_[type].values();
    values["@"]         = is_stream_ ? protocol::Message_Task_Add_Stream : protocol::Message_Task_Add;
    values["save_path"] = default_save_path();
    values["proxy"]     = zzz->configs["network"].get("proxy");

    default_values_[type] = ext::value::merge(values,zzz->task_config(type));
}

void add_task::init_events()
{
    ui.on_action("#act_save_path",[this](auto)
    {
        auto path = ext::ui::file_dialog::open_directory("save_path"_lang);

        if(!path.empty()){
            change_save_path(path);
        }
    });
    ui.on_click("#download_later",[this](auto){
        download(false);
    });
    ui.on_click("#download_now",[this](auto){
        download(true);
    });
    addresses_->on_change([&](auto& str)
    {
        Ext_Return_If(timer_ != 0);

        timer_ = ext::ui::set_timeout([this]{
            timer_ = 0;
            analyze_addresses();
        },500ms);
    });

}


///--------------------------
void add_task::exec()
{
    dialog_->show_active();
    init_events();
}

void add_task::active()
{
    dialog_->show_active();
}

bool add_task::append(const std::vector<ext::text>& addresses)
{
    uint32_t appended = 0;

    for(auto& uri : addresses)
    {
        if(configs_.contains(uri) || cached_uris_.contains(uri)){
            continue;
        }
        cached_uris_.emplace(uri);
        addresses_->append(uri);
        appended++;
    }
    return appended != 0;
}


}
