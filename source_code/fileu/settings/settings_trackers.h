#ifndef PRO_SETTINGS_TRACKERS_H
#define PRO_SETTINGS_TRACKERS_H

#include "../pro_sample.h"

namespace pro::settings
{

class trackers : public pro::dialog_sample
{
public:
    trackers(pro::global& global);


protected:
    /*
     * form
    */
    ext::ui::form form_;
    /*
     * table
    */
    ext::ui::table* subscribes_ = nullptr;


protected:
    /*
     * init events
    */
    void init_events();
    /*
     * init actions
    */
    void init_actions();
    /*
     * init messages
    */
    void init_messages();


public:
    /*
     * add subscribe
    */
    void subscribe_add(ext::value& json);
    /*
     * update subscribe
    */
    void subscribe_update(ext::value& json,std::int64_t id);
    /*
     * remove subscribe
    */
    void subscribe_remove(ext::value& json,std::int64_t id);


public:
    /*
     * update
    */
    void update(ext::value& json);
    /*
     * exec
    */
    void exec();

};

}

#endif
