#ifndef PRO_HELP_INSTALL_H
#define PRO_HELP_INSTALL_H

#include "../pro_sample.h"

namespace pro::help
{

class install : public pro::dialog_sample<>
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
    /*
     * values
    */
    ext::value values_;
    

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
     * load settings
    */
    ext::value load_settings(const ext::fs::path& path,ext::text_view lang);


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
     * save lang file
    */
    void save_lang_file(ext::ui::language& lang,const ext::fs::path& path);
    /*
     * create desktop shortcuts
    */
    void create_desktop_shortcuts(const ext::text& name);
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
