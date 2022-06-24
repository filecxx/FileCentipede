#ifndef PRO_SETTINGS_MAIN_H
#define PRO_SETTINGS_MAIN_H

#include "../pro_sample.h"

namespace pro::settings
{

class main : public pro::dialog_sample<pro::global>
{
    constexpr static std::string_view UI_Config_Fields[] = {
        "lang","fonts","font_size","tray_icon",
        "autostart","watch_clipboard","no_refresh_address_dialog","no_completed_dialog",
        "sound_effects","save_window_size","silent_mode"
    };


public:
    main(pro::global& global,settings::main*& self_ptr);


protected:
    /*
     * self ptr
    */
    settings::main*& self;
    /*
     * loaded
    */
    std::unordered_set<ext::text> loaded_;
    /*
     * list
    */
    ext::ui::list* list_ = nullptr;
    /*
     * current
    */
    ext::ui::widget* current_ = nullptr;
    /*
     * widgets
    */
    ext::ui::widgets* widgets_ = nullptr;


protected:
    /*
     * init list
    */
    void init_list();
    /*
     * init languages
    */
    void init_languages();
    /*
     * init fonts
    */
    void init_fonts();
    /*
     * init proxies
    */
    void init_proxies();
    /*
     * init events
    */
    void init_events();
    /*
     * init user agents
    */
    void init_user_agents();
    /*
     * ini form
    */
    void init_form(const ext::text& name);


protected:
    /*
     * edit user agents
    */
    void edit_user_agents();
    /*
     * set autostart
    */
    void set_autostart(bool state);


public:
    /*
     * exec
    */
    void exec();

};

}

#endif