#include "view_desktop_shortcuts.h"

namespace pro::view
{

desktop_shortcuts::desktop_shortcuts(pro::global& global) : pro::dialog_sample(global,"ui/view/desktop_shortcuts.sml")
{
    dialog_->on_close([this](auto){
        delete this;
    });
    init_events();
}


///--------------------------
void desktop_shortcuts::init_events()
{
    ui.on_click("#filec",[this](auto){
        create_shortcut(ext::ui::lang("software_name_") + ext::text(" (filec)"),"filec",{},true);
    });
    ui.on_click("#fileu",[this](auto){
        create_shortcut(ext::ui::lang("software_name_") + ext::text(" (fileu)"),"fileu",{},true);
    });
    ext::ui::form(ui("#main")).each([this](auto name,auto node)
    {
        auto button = node->object.template cast<ext::ui::button*>();
        button->on_click([this,name,text = button->text()](auto){
            create_shortcut(text,"fileu","--" + name);
        });
        return false;
    });

}


///--------------------------
void desktop_shortcuts::create_shortcut(ext::text_view display,ext::text_view name,ext::text_view args,bool use_categories)
{
    ext::text path = ((zzz.workspace / "lib").executable(name)).u8string();
    ext::text text = '"' + path + '"';

    if(!args.empty()){
        text += " ";
        text += args;
    }
    ui.cast<ext::ui::line_view*>("#command_line")->text(text);

    doom::custom::desktop desktop;
    if(use_categories){
        desktop.categories("Application;Network;GNOME;Qt;");
    }
    desktop.full_name(display);
#ifndef EXT_OS_WINDOWS
    desktop.icon(zzz.workspace / "icons" / "icon.png");
#endif
    ext::fs::path p(path);
    desktop.create_shortcut(display,path,args);
}


///--------------------------
void desktop_shortcuts::exec()
{
    dialog_->show_active();
}


}