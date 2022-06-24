#ifndef PRO_SETTINGS_SITE_RULES_H
#define PRO_SETTINGS_SITE_RULES_H

#include "../pro_sample.h"

namespace pro::settings
{

class site_rules : public pro::dialog_sample<pro::global>
{
public:
    site_rules(pro::global& global);


protected:
    /*
     * table
    */
    ext::ui::table* table_ = nullptr;


protected:
    /*
     * init events
    */
    void init_events();
    /*
     * init messages
    */
    void init_messages();


public:
    /*
     * exec
    */
    void exec();

};

}

#endif
