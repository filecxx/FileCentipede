#ifndef PRO_SETTINGS_MAIN_H
#define PRO_SETTINGS_MAIN_H

#include "../pro_sample.h"

namespace pro::settings
{

class main : public pro::dialog_sample
{
    constexpr static std::string_view UI_Config_Fields[] = {"lang","fonts","font_size","tray_icon","autostart","watch_clipboard"};


public:
    main(pro::global& global);


protected:
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


protected:
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