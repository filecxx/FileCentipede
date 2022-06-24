#ifndef PRO_FILE_MANAGER_MAIN_H
#define PRO_FILE_MANAGER_MAIN_H

#include "../pro_global.h"

namespace pro::file_manager
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
