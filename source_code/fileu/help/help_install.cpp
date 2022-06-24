#include "help_install.h"

namespace pro::help
{

install::install(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/help/install.sml")
{
    ui.cast(licence_,"#licence");
    ui.cast(path_,"#path");
    ui.cast(language_,"#language");

    form_ = ext::ui::form(ui.root());
    path_->value(ext::text(zzz.workspace.u8string()));
    dialog_->on_close([this](auto){
        delete this;
    });
    init_languages();
    init_actions();
}

install::~install()
{
    //ext::debug <<= "~install";
}


///--------------------------
ext::value install::load_settings(const ext::fs::path& path,ext::text_view lang)
{
    ext::error_code error;
    ext::value      setting({
        {"installed",1},
        {"watch_clipboard",true},
        {"lang",lang},
        {"sound_effects",true}
    });
    if(ext::fs::exists(path,error))
    {
        ext::text  conf;
        ext::value json;

        if(ext::cfile::read(path,conf).value() == 0 && (json = ext::json::parse(conf)).is_map()){
            setting.merge(std::move(json));
        }
    }
    setting["tray_icon"] = values_["tray_icon"];
    setting["autostart"] = values_["autostart"];

    return setting;
}


///--------------------------
void install::init_languages()
{
    ext::error_code error;

    for(auto& iter: ext::fs::directory_iterator("lang/",error))
    {
        auto& path = iter.path();

        if(iter.is_regular_file() && path.extension() == ".lang"){
            ext::text locale_name = path.stem().u8string();
            language_->append(ext::ui::language::name(locale_name),locale_name);
        }
    }
}

void install::init_actions()
{
    ui.on_click("#btn_install",[this](auto){
        start_install();
    });
    ui.on_click("#btn_cancel",[this](auto){
        dialog_->close();
    });
}


///--------------------------
void install::save_lang_file(ext::ui::language& lang,const ext::fs::path& path)
{
    ext::text buffer;

    lang.each([&](auto name,auto value)
    {
        buffer += ext::text(name) + "=";

        if(!value.empty() && ext::ui::language::is_raw(value)){
            buffer += ext::text(value);
        }else{
            buffer += ext::value_view(value).stringify();
        }
        buffer += "\r\n";
        return false;
    });
    if(!buffer.empty()){
        ext::cfile::write(path,"wb",buffer);
    }
}

void install::create_desktop_shortcuts(const ext::text& name)
{
    doom::custom::desktop desktop;

    desktop.categories("Application;Network;GNOME;Qt;");
    desktop.full_name(name);
#ifndef EXT_OS_WINDOWS
    desktop.icon(install_path_ / "icons" / "icon.png");
#endif
    desktop.create_shortcut(name,(install_path_ / "lib").executable(pro::Client_Bin));
}

void install::start_install()
{
    ext::random random;
    install_path_ = ext::fs::path(path_->value());
    values_       = form_.values();

    if(!ext::fs::exists(install_path_,error_) && !ext::fs::create_directories(install_path_,error_)){
        goto readonly;
    }
    if(!ext::fs::test_write_perm(install_path_,random)){
        readonly:
        ext::ui::alert("error","error",ext::text("write_file_error"_lang) + " - " + "readonly"_lang).exec();
        return;
    }
    if(!ext::fs::filename_valid(values_["software_name"].text_view())){
        ext::ui::alert("error","error",ext::text("software_name"_lang) + " " + "error"_lang).exec();
        return;
    }
    ui("#btn_install")->object.enable(false);

    thread_ = std::jthread([this]
    {
        auto args = std::vector<ext::text>{"install","path",install_path_.u8string()};

        if(values_["system_service"] == true){
            args.emplace_back("system_service");
        }
        zzz.shutdown();

        bool elevatable = false;
        int  ret        = doom::privilege::launch(zzz.workspace.executable(pro::Service_Bin),args,elevatable,true);

        ext::ui::post([this,ret,elevatable]() mutable
        {
            if(WEXITSTATUS(ret) != 200){
                install_failed(WEXITSTATUS(ret),elevatable);
            }else{
                install_success();
            }
            std::exit(0);
        });
    });
}

void install::install_failed(int ret,bool elevatable)
{
    if(ret == 99){
        install_write_conf_failed();
    }else{
        ext::text error_str = ext::ui::lang((!elevatable || ret == 0) ? "install_failed_error1_" : "install_failed");
        ext::ui::alert("error","error",error_str + " code: " + std::to_string(ret)).exec();
    }
    ui("#btn_install")->object.enable(true);
}

void install::install_write_conf_failed()
{
    ext::ui::alert("error","error"_lang,"write_conf_failed"_lang).exec();
}

void install::install_success()
{
    auto lang = language_->value();

    if(!lang.is_string()){
        lang = ext::ui::language::locale_name();
    }
    ext::ui::language language;
    ext::text         software_name = "software_name_"_lang;
    ext::fs::path     lang_path     = install_path_ / "lang" / (lang.text() + ".lang");
    ext::fs::path     config_path   = install_path_ / "lib" / FileU_Config_File_Name;

    auto setting = load_settings(config_path,lang.text_view());

    if(language.load_file(lang_path))
    {
        auto name     = language("software_name_");
        auto name_new = values_["software_name"];

        if(name_new != name){
            software_name = name_new.string();
            language("software_name_",software_name);
            save_lang_file(language,lang_path);
        }
    }
    if(values_["desktop_shortcuts"] == true){
        create_desktop_shortcuts(software_name);
    }
    if(ext::cfile::write(config_path,"wb",setting.stringify()).value() != 0){
        install_write_conf_failed();
    }else{
        ext::ui::alert("info","success","install_success"_lang).exec();
    }
    ext::process::launch(0,(install_path_ / "lib").executable(pro::Client_Bin));
    std::exit(1);
};


///--------------------------
void install::exec(bool show)
{
    if(show){
        dialog_->show();
    }else{
        dialog_->exec();
    }
}


}