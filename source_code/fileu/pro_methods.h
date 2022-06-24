#ifndef PRO_METHODS_H
#define PRO_METHODS_H

#include "pro_global.h"

namespace pro
{

class methods
{
    friend class main_window;

public:
    methods(pro::global& global,ext::ui::model& instance);


protected:
    /*
     * global
    */
    pro::global& zzz;
    /*
     * ui
    */
    ext::ui::model& ui;


protected:
    /*
     * actions initialized
    */
    ext::boolean_t actions_initialized_ = false;
    /*
     * tray initialized
    */
    ext::boolean_t tray_initialized_ = false;
    /*
     * clipboard initialized
    */
    ext::boolean_t clipboard_initialized_ = false;
    /*
     * window size changed
    */
    ext::boolean_t window_size_changed_ = false;
    /*
     * interval handlers
    */
    std::unordered_map<ext::text,ext::value_view> interval_handlers_;


protected:
    /*
     * message type
    */
    static uint16_t message_type(ext::text_view type);


protected:
    /*
     * filec-version
    */
    static void filec_version(ext::ui::arguments& arguments);
    /*
     * filec-lang
    */
    static void filec_lang(ext::ui::arguments& arguments);
    /*
     * filec-interval
    */
    static void filec_interval(ext::ui::arguments& arguments);
    /*
     * filec-submit
    */
    static void filec_submit(ext::ui::arguments& arguments);
    /*
     * filec-form
    */
    static void filec_form(ext::ui::arguments& arguments);
    /*
     * filec-send
    */
    static void filec_send(ext::ui::arguments& arguments);
    /*
     * filec on
    */
    static void filec_on(ext::ui::arguments& arguments);
    /*
     * filec launch
    */
    static void filec_launch(ext::ui::arguments& arguments);
    /*
     * filec user agents
    */
    static void filec_user_agents(ext::ui::arguments& arguments);
    /*
     * filec paths
    */
    static void filec_paths(ext::ui::arguments& arguments);
    /*
     * filec filter rules
    */
    static void filter_rules(ext::ui::arguments& arguments);
    /*
     * exit
    */
    static void exit(ext::ui::arguments& arguments);


public:
    /*
     * launch filec
    */
    void launch_filec();


public:
    /*
     * init
    */
    void init();

};

}



#endif
