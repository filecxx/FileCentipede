#include "tasks_add_task.h"

namespace pro::tasks
{

add_task::add_task(pro::global& global,ext::boolean_t is_stream,std::string_view ui_path) : pro::dialog_sample<>(global,ui_path),is_stream_(is_stream)
{
    dialog_->on_close([this](auto){
        ext::invoke(on_delete_);
        delete this;
    });
    ui.cast(addresses_,"#addresses");
    ui.cast(tab_,"#tab");
}

add_task::~add_task()
{
    ext::ui::clear_timeout(timer_);
}


///--------------------------
void add_task::analyze_addresses()
{
    auto& general_config = zzz.configs["general"];
    auto& network_config = zzz.configs["network"];

    ext::text protocol;
    ext::parser::split_lines(addresses_->text(),[&](auto& line,auto n)
    {
        if(auto address = boost::trim_copy(line);!address.empty())
        {
            pro::uri uri;

            if(address.starts_with('{') && address.ends_with('}'))
            {
                if(uri.analyze_json(address,ext::Map)){
                    auto key = uri.config.text("uri");
                    uris_.emplace(std::move(key),config_t{uri.type,std::move(uri.config)});
                }
            }else if(uri.analyze(address,ext::Map)){
                uris_.emplace(line,config_t{uri.type,std::move(uri.config)});
            }
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
        if(configs_.contains(iter.first)){
            continue;
        }
        if(is_stream_ && iter.second.type != protocol::Task_HTTP){
            continue;
        }
        ext::value values = ext::value::merge(zzz.task_config(iter.second.type),std::move(iter.second.values));
        values["@"]         = is_stream_ ? protocol::Message_Task_Add_Stream : protocol::Message_Task_Add;
        values["uri"]       = iter.first;
        values["save_path"] = general_config.get("default_save_path");
        values["proxy"]     = network_config.get("proxy");

        if(!combobox_configs_[iter.second.type]){
            ui.import(tab_->item_data(iter.second.type + 1).string());
            init_form(ext::text(protocol::Task_Types_Text[iter.second.type]),iter.second.type);
        }
        configs_.emplace(iter.first,config_t{iter.second.type,std::move(values)});
        combobox_configs_[iter.second.type]->append(iter.first);
    }
    for(int i=0;i<combobox_configs_.size();++i){
        if(combobox_configs_[i]){
            tab_->setTabVisible(i + 1,combobox_configs_[i]->count() != 0);
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
            iter.second.values["download_later"] = true;
        }
        if(iter.second.type != protocol::Task_Torrent){
            iter.second.values["without_confirm"] = true;
        }
        zzz.send(iter.second.values.stringify());
    }
    dialog_->close();
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
    if(zzz.catalogs.is_map())
    {
        for(auto& iter : *zzz.catalogs.cast_map()){
            catalog_combobox->append(iter.first.text(),iter.first.text());
        }
        catalog_combobox->on_index_change([this,type,catalog_combobox](auto index)
        {
            ext::text path;

            if(index == 0){
                path = zzz.configs["general"].text_view("default_save_path");
            }else if(auto name = catalog_combobox->item_text(index);zzz.catalogs.contains(name)){
                path = zzz.catalogs[name].text_view("path");
            }
            forms_[type].values({{"save_path",path}});
        });
    }
}

void add_task::init_events()
{
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
