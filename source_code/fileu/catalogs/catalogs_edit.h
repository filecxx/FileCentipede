#ifndef PRO_CATALOGS_EDIT_H
#define PRO_CATALOGS_EDIT_H

#include "../pro_sample.h"

namespace pro::catalogs
{

class edit : public ext::ui::sample
{
public:
    edit(pro::global& global);


protected:
    /*
     * global
    */
    pro::global& zzz;
    /*
     * dialog
    */
    ext::ui::edit_dialog* dialog_ = nullptr;


public:
    /*
     * add
    */
    void exec();
    /*
     * edit
    */
    void exec(ext::text_view name);

};

}



#endif
