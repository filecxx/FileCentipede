#ifndef PRO_FILE_BROWSER_HANDLER_H
#define PRO_FILE_BROWSER_HANDLER_H

#include "file_browser_main.h"

namespace pro::file_browser
{

class handler
{
public:
    handler(pro::global& global,ext::ui::model& instance);


public:
    pro::file_browser::main* operator->(){
        if(!file_browser_){
            file_browser_ = new pro::file_browser::main(zzz,ui);
        }
        return file_browser_;
    }


protected:
    /*
     * tasks global
    */
    pro::file_browser::global zzz;
    /*
     * ui
    */
    ext::ui::model& ui;
    /*
     * network files
    */
    pro::file_browser::main* file_browser_ = nullptr;


public:
    /*
     * on status
    */
    void on_status(ext::value& json);


public:
    /*
     * on nfs hosts
    */
    void on_hosts(ext::value& json);
    /*
     * on nfs group add
    */
    void on_group_add(ext::value& json);
    /*
     * on nfs group edit
    */
    void on_group_edit(ext::value& json);
    /*
     * on nfs group remove
    */
    void on_group_remove(ext::value& json);
    /*
     * on nfs host add
    */
    void on_host_add(ext::value& json);
    /*
     * on nfs host edit
    */
    void on_host_edit(ext::value& json);
    /*
     * on nfs host remove
    */
    void on_host_remove(ext::value& json);


public:
    /*
     * clear
    */
    void clear();

};

}


#endif
