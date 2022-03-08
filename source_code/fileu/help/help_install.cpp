#include "help_install.h"

namespace pro::help
{

install::install(pro::global& global) : pro::dialog_sample(global,"ui/help/install.sml")
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
void install::init_languages()
{
    auto error = std::error_code();

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
void install::create_desktop_shortcuts()
{
    ext::text display = ext::ui::lang("software_name_");

    doom::custom::desktop desktop;

    desktop.categories("Application;Network;GNOME;Qt;");
    desktop.full_name(display);
#ifndef EXT_OS_WINDOWS
    desktop.icon(install_path_ / "icons" / "icon.png");
#endif
    desktop.create_shortcut(display,(install_path_ / "lib").executable(protocol::Client_Bin));
}

void install::start_install()
{
    ui("#btn_install")->object.enable(false);

    thread_ = std::jthread([this]
    {
        auto settings = form_.values();
        auto args     = ext::text("install path \"") + (install_path_ = ext::fs::path(path_->value())).u8string() + "\"";

        for(auto i=0;i<args.size();++i){
            if(args[i] == '\\'){
                args[i] = '/';
            }
        }
        if(settings["system_service"] == true){
            args += " system_service";
        }
        bool elevatable = false;
        int  ret        = doom::privilege::launch(zzz.workspace.executable(protocol::Service_Bin),args,elevatable,true);

        ext::ui::post([this,ret,elevatable]() mutable
        {
            if(WEXITSTATUS(ret) != 200){
                install_failed(elevatable);
            }else{
                install_success();
            }
        });
    });
}

void install::install_failed(bool elevatable)
{
    ext::ui::alert("error","error",ext::ui::lang(elevatable ? "install_failed" : "install_failed_error1_")).exec();

    ui("#btn_install")->object.enable(true);
}

void install::install_success()
{
    auto values  = form_.values();
    auto setting = ext::value{
        {"installed",1},
        {"watch_clipboard",true},
        {"lang",language_->value()},
        {"tray_icon",values["tray_icon"]},
        {"autostart",values["autostart"]}
    };
    if(values["desktop_shortcuts"] == true){
        create_desktop_shortcuts();
    }
    zzz.shutdown();

    if(ext::cfile::write((install_path_ / "lib" / Config_File_Name).u8string().c_str(),"wb",setting.stringify()).value() != 0){
        ext::ui::alert("error","error",ext::ui::lang("write_conf_failed")).exec();
    }else{
        ext::ui::alert("info","success",ext::ui::lang("install_success")).exec();
    }
    ext::process::launch(0,(install_path_ / "lib").executable(protocol::Client_Bin));
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