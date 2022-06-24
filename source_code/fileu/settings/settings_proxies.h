#ifndef PRO_SETTINGS_PROXIES_H
#define PRO_SETTINGS_PROXIES_H

#include "../pro_sample.h"

namespace pro::settings
{

class proxies : public pro::dialog_sample<pro::global>
{
public:
    proxies(pro::global& global);


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


protected:
    /*
     * import
    */
    void imports();
    /*
     * export
    */
    void exports();
    /*
     * test
    */
    void test();


public:
    /*
     * exec
    */
    void exec();

};

}

#endif
