#include "settings_main.h"

namespace pro::settings
{

main::main(pro::global& global,settings::main*& self_ptr) : pro::dialog_sample<pro::global>(global,"ui/settings/main.sml"),self(self_ptr)
{
    ui.cast(list_,"#settings_list");
    ui.cast(widgets_,"#settings_widgets");

    init_form("general");
    init_list();
    init_events();

    if(zzz.settings.is_map())
    {
        for(auto& key : UI_Config_Fields){
            ui.set_value("#gen_" + ext::text(key),zzz.settings[key]);
        }
    }
    dialog_->on_close([this](auto){
        self = nullptr;
        delete this;
    });
}


///--------------------------
void main::init_list()
{
    list_->on_current_row_change([this](auto row)
    {
        auto item = list_->item(row);
        auto data = list_->item_data((ext::ui::list_item*)item);

        if(!data.is_string() || data.empty()){
            return;
        }
        if(current_){
            current_->hide();
        }
        if(auto name = data.text();!loaded_.contains(name)){
            init_form(name);
        }else{
            current_ = ui.query('#' + name)->object.cast<ext::ui::widget*>();
            current_->show();
        }
    });
}

void main::init_languages()
{
    auto lang  = ui.cast_id<ext::ui::combobox*>("gen_lang");
    auto error = ext::error_code();

    for(auto& iter: ext::fs::directory_iterator("lang/",error))
    {
        auto& path = iter.path();

        if(iter.is_regular_file() && path.extension() == ".lang"){
            ext::text locale_name = path.stem().u8string();
            lang->append(ext::ui::language::name(locale_name),locale_name);
        }
    }
}

void main::init_fonts()
{
    auto list  = ext::ui::system_fonts();
    auto fonts = ui.cast_id<ext::ui::combobox*>("gen_fonts");

    for(auto& name : list){
        fonts->append(name,name);
    }
}

void main::init_proxies()
{
    auto proxies  = ui.cast_id<ext::ui::combobox*>("network_proxy");
    auto selected = zzz.configs["network"].text("proxy");

    proxies->clear();
    proxies->append("no_proxy"_lang);

    if(zzz.proxies.is_map())
    {
        for(auto& iter : *zzz.proxies.cast_map())
        {
            proxies->append(iter.first.text(),iter.first.text());

            if(iter.first.text() == selected){
                proxies->setCurrentIndex(proxies->count() - 1);
            }
        }
    }
}

void main::init_events()
{
    ui.on_click("#settings_save",[this](auto)
    {
        if(zzz.configs.empty()){
            goto bottom;
        }
        for(auto& iter : *zzz.configs.cast_map())
        {
            auto name = iter.first.text();
            auto page = ui.query("#page_" + name);

            if(page){
                iter.second.merge(ext::ui::form(page).values());
                zzz.send({{"@",protocol::Message_Config_Update},{"name",name},{"config",iter.second}});
            }
        }
        bottom: for(auto& key : UI_Config_Fields)
        {
            auto value = ui.query_value("#gen_" + std::string(key));

            if(key == "autostart"){
                set_autostart(value.cast<bool>());
            }
            zzz.setting(key,value);
        }
        dialog_->close();
    });
}

void main::init_user_agents()
{
    ui.on_click("#edit_http_user_agents",[this](auto){
        edit_user_agents();
    });
}

void main::init_form(const ext::text& name)
{
    ext::text path = "ui/settings/" + name + ".sml";

    if(!ui.import(path)){
        return ext::ui::alert("error","error"_lang,ext::text("Load UI file " + path + " failed."))(),void();
    }
    auto node = ui.query('#' + name);
    widgets_->add(node->object);
    current_ = node->object.cast<ext::ui::widget*>();
    current_->show();

    if(name == "general"){
        init_languages();
        init_fonts();
    }else if(name == "network"){
        init_proxies();
    }else if(name == "http"){
        init_user_agents();
    }
    for(auto& iter : *zzz.configs.cast_map())
    {
        auto key = iter.first.string();

        if(key == name || key.starts_with(name + "_")){
            if(auto page = ui.query("#page_" + key)){
                ext::ui::form(page).values(iter.second);
            }
        }
    }
    loaded_.emplace(name);
}


///--------------------------
void main::edit_user_agents()
{
    auto& config   = zzz.configs["http_user_agents"];
    auto  combobox = ui.cast_id<ext::ui::combobox*>("http_user_agents");
    auto  sample   = new pro::dialog_sample<pro::global>(zzz,"ui/settings/user_agents.sml");
    auto  dialog   = sample->dialog();
    auto  edit     = sample->ui.cast<ext::ui::text_edit*>("TextEdit");

    if(auto& text = config["text"];text.is_string()){
        edit->value(text.text_view());
    }
    sample->ui.on_click("#save",[&](auto)
    {
        auto text = edit->text();
        config["text"] = text;
        zzz.send({{"@",protocol::Message_Config_Update},{"name","http_user_agents"},{"config",config}});

        combobox->clear_items();
        combobox->items(text);
        dialog->close();
    });
    dialog->on_close([sample](auto){
        delete sample;
    });
    dialog->exec();
}

void main::set_autostart(bool state)
{
#ifdef EXT_OS_WINDOWS
    doom::startup::config config;
    doom::startup::normal startup(config);

    config.name  = "fileu";
    config.title = "software_name_"_lang;
    config.path  = zzz.workspace.executable("fileu").u8string();
    config.args  = "boot";

    if(state)
    {
        if(!startup.has()){
            startup.create();
        }
    }else if(startup.has()){
        startup.remove();
    }
#endif
}


///--------------------------
void main::exec()
{
    dialog_->show();
}


}