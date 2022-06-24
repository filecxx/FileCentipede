#ifndef PRO_HELP_UPDATE_H
#define PRO_HELP_UPDATE_H

#include "../pro_sample.h"

namespace pro::help
{

class update : public pro::dialog_sample<pro::global>
{
public:
    update(pro::global& global);


protected:
    /*
     * form info
    */
    ext::ui::form form_info_;
    /*
     * form source
    */
    ext::ui::form form_source_;
    /*
    * form setting
   */
    ext::ui::form form_setting_;
    /*
     * timer
    */
    std::int64_t timer_ = 0;


protected:
    /*
     * init messages
    */
    void init_messages();


protected:
    /*
     * start timer
    */
    void start_timer();
    /*
     * save settings
    */
    void save_settings();
    /*
     * set info
    */
    void set_info(ext::value& values);


public:
    /*
     * exec
    */
    void exec();

};

}

#endif
