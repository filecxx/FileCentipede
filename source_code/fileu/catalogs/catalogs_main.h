#ifndef PRO_CATALOGS_MAIN_H
#define PRO_CATALOGS_MAIN_H

#include "../pro_sample.h"
#include "catalogs_edit.h"

namespace pro::catalogs
{

class main : public pro::sample<>
{
public:
    main(pro::global& global,ext::ui::list* list);


protected:
    /*
     * list
    */
    ext::ui::list* list_ = nullptr;
    /*
     * context menu
    */
    ext::ui::menu* context_menu_ = nullptr;


protected:
    /*
     * init actions
    */
    void init_actions();


protected:
    /*
     * remove catalog
    */
    void remove_catalog();
    /*
     * merge catalogs
    */
    void merge_catalogs();


public:
    /*
     * show context menu
    */
    void show_context_menu(int32_t row);

};


}

#endif
