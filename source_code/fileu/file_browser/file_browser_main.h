#ifndef PRO_FILE_BROWSER_MAIN_H
#define PRO_FILE_BROWSER_MAIN_H

#include "file_browser_hosts.h"
#include "file_browser_filesystem.h"
#include "file_browser_tasks.h"

namespace pro::file_browser
{

class main
{
    friend class global;
    friend class handler;


public:
    main(pro::file_browser::global& global,ext::ui::model& instance);


protected:
    /*
     * global
    */
    pro::file_browser::global& zzz;
    /*
     * ui
    */
    ext::ui::model& ui;


protected:
    /*
     * increased tab id
    */
    std::int64_t increased_tab_id_ = 0;
    /*
     * client layout
    */
    ext::ui::object client_layout_;
    /*
     * protocol icons
    */
    ext::ui::node_t* protocol_icons_ = nullptr;
    /*
     * tabs
    */
    ext::ui::tab* tabs_ = nullptr;
    /*
     * statusbar
    */
    ext::ui::statusbar* statusbar_ = nullptr;
    /*
     * tasks button
    */
    ext::ui::state_button* tasks_button_ = nullptr;
    /*
     * default filesystem
    */
    std::shared_ptr<file_browser::filesystem> default_filesystem_;
    /*
     * mapped (tid -> {host_id,sid})
    */
    std::unordered_map<int64_t,std::pair<int64_t,int64_t>> mapped_;


protected:
    /*
     * hosts
    */
    pro::file_browser::hosts hosts_;
    /*
     * tasks
    */
    pro::file_browser::tasks* tasks_ = nullptr;


public:
    /*
     * hosts
    */
    pro::file_browser::hosts& hosts(){
        return hosts_;
    }


protected:
    /*
     * on status
    */
    void on_status(ext::value& values);
    /*
     * on tab close
    */
    void on_tab_close(uint32_t index);


protected:
    /*
     * recalc tasks
    */
    void recalc_tasks();
    /*
     * create tab
    */
    void create_tab(std::int64_t id,std::int64_t sid,ext::value& values);
    /*
     * create default
    */
    void create_default();


protected:
    /*
     * init events
    */
    void init_events();


public:
    /*
     * init
    */
    void init(ext::ui::tab* main_tab,ext::ui::statusbar* statusbar);
    /*
     * clear
    */
    void clear();

};

}



#endif
