#ifndef PRO_VIEW_DESKTOP_SHORTCUTS_H
#define PRO_VIEW_DESKTOP_SHORTCUTS_H

#include "../pro_sample.h"

namespace pro::view
{

class desktop_shortcuts : public pro::dialog_sample<pro::global>
{
public:
    desktop_shortcuts(pro::global& global);


protected:
    /*
     * init events
    */
    void init_events();


public:
    /*
     * create shortcut
    */
    void create_shortcut(ext::text_view display,ext::text_view name,ext::text_view args = {},bool use_categories = false);
    /*
     * exec
    */
    void exec();
};

}



#endif
