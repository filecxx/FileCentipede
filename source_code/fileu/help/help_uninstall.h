#ifndef PRO_HELP_UNINSTALL_H
#define PRO_HELP_UNINSTALL_H

#include "../pro_sample.h"

namespace pro::help
{

class uninstall : public pro::dialog_sample
{
public:
    uninstall(pro::global& global);


protected:
    /*
     * path
    */
    ext::ui::line_view* path_ = nullptr;


protected:
    /*
     * thread
    */
    std::jthread thread_;


protected:
    /*
     * init actions
    */
    void init_actions();


protected:
    /*
     * uninstall failed
    */
    void uninstall_failed(bool elevatable);
    /*
     * start uninstall
    */
    void start_uninstall();


public:
    /*
     * exec
    */
    void exec();

};

}

#endif
