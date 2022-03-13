#ifndef PRO_HELP_INSTALL_H
#define PRO_HELP_INSTALL_H

#include "../pro_sample.h"

namespace pro::help
{

class install : public pro::dialog_sample
{
public:
    install(pro::global& global);


public:
    ~install();


protected:
    /*
     * licence
    */
    ext::ui::edit* licence_ = nullptr;
    /*
     * path
    */
    ext::ui::path_edit* path_ = nullptr;
    /*
     * language
    */
    ext::ui::combobox* language_ = nullptr;
    /*
     * form
    */
    ext::ui::form form_;
    

protected:
    /*
     * thread
    */
    std::jthread thread_;
    /*
     * install path
    */
    ext::fs::path install_path_;


protected:
    /*
     * init languages
    */
    void init_languages();
    /*
     * init actions
    */
    void init_actions();


protected:
    /*
     * create desktop shortcuts
    */
    void create_desktop_shortcuts();
    /*
     * start install
    */
    void start_install();
    /*
     * install failed
    */
    void install_write_conf_failed();
    /*
     * install failed
    */
    void install_failed(int ret,bool elevatable);
    /*
     * install success
    */
    void install_success();


public:
    /*
     * exec
    */
    void exec(bool show = false);

};

}

#endif
