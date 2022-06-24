#ifndef PRO_SETTINGS_FILTER_H
#define PRO_SETTINGS_FILTER_H

#include "../pro_sample.h"

namespace pro::settings
{

class filter : public pro::dialog_sample<pro::global>
{
public:
    filter(pro::global& global);


protected:
    /*
     * form
    */
    ext::ui::form form_;
    /*
     * table
    */
    ext::ui::table* torrent_files_filter_ = nullptr;


protected:
    /*
     * init events
    */
    void init_events();
    /*
     * init actions
    */
    void init_actions();


public:
    /*
     * exec
    */
    void exec();

};

}



#endif
