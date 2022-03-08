#include "settings_main.h"

namespace pro::settings
{

main::main(pro::global& global) : pro::dialog_sample(global,"ui/settings/main.sml")
{
    dialog_->on_close([this](auto){

    });
    init_languages();
    init_fonts();
    init_events();

    if(zzz.settings.is_map())
    {
        for(auto& key : UI_Config_Fields){
            ui.set_value("#gen_" + ext::text(key),zzz.settings[key]);
        }
    }
}


///--------------------------
void main::init_languages()
{
    auto lang  = ui.cast_id<ext::ui::combobox*>("gen_lang");
    auto error = std::error_code();

    for(auto& iter: std::filesystem::directory_iterator("lang/",error))
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
    proxies->append(ext::ui::lang("no_proxy"));

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
    ui.on_click("#settings_cancel",[this](auto){
        dialog_->close();
    });
}


///--------------------------
void main::set_autostart(bool state)
{
#ifdef EXT_OS_WINDOWS
    doom::startup::config config;
    doom::startup::normal startup(config);

    config.name  = "fileu";
    config.title = ext::ui::lang("software_name_");
    config.path  = zzz.workspace.executable("fileu").u8string();

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
    if(zzz.configs.empty()){
        goto bottom;
    }
    for(auto& iter : *zzz.configs.cast_map())
    {
        auto name = iter.first.string();
        auto page = ui.query("#page_" + name);

        if(page){
            ext::ui::form(page).values(iter.second);
        }
    }
    bottom:
    init_proxies();
    dialog_->show();
}


}