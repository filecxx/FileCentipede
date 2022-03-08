#ifndef PRO_LOCAL_FILES_MAIN_H
#define PRO_LOCAL_FILES_MAIN_H

#include "../pro_global.h"

namespace pro::local_files
{

class main
{
public:
    main(pro::global& global,ext::ui::model& instance);


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
     * init actions
    */
    void init_actions();


public:
    /*
     * init
    */
    void init();

};


}


#endif
