#ifndef PRO_FILE_BROWSER_HOSTS_H
#define PRO_FILE_BROWSER_HOSTS_H

#include "file_browser_edit_host.h"
#include "file_browser_filesystem.h"

namespace pro::file_browser
{

class hosts
{
    friend class main;
    friend class tasks;

    using filesystems_t = std::unordered_map<std::int64_t,std::shared_ptr<filesystem>>;

    struct host_t
    {
        ext::ui::list_item* item;
        std::uint16_t       type;
        filesystems_t       filesystems;
    };


public:
    hosts(pro::file_browser::global& global,ext::ui::model& instance);


public:
    /*
     * get host
    */
    host_t* operator()(std::int64_t hid);
    /*
     * get filesystem instance
    */
    std::shared_ptr<filesystem> operator()(std::int64_t hid,std::int64_t sid);


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
     * group all
    */
    ext::ui::collapsible_list::group_t* group_all_ = nullptr;
    /*
     * hosts panel
    */
    ext::ui::widget* nav_hosts_panel_ = nullptr;
    /*
     * hosts panel
    */
    ext::ui::collapsible_list* nav_hosts_ = nullptr;
    /*
     * hosts filter
    */
    ext::ui::line_edit* nav_hosts_filter_ = nullptr;
    /*
     * context menu
    */
    ext::ui::menu* context_menu_ = nullptr;
    /*
     * protocol icons
    */
    ext::ui::node_t* protocol_icons_ = nullptr;


protected:
    /*
     * groups
    */
    std::unordered_map<std::int64_t,ext::ui::collapsible_list::group_t*> groups_;
    /*
     * hosts
    */
    std::unordered_map<std::int64_t,host_t> hosts_;


protected:
    /*
     * on change
    */
    std::function<void(uint8_t,host_t&)> on_change_;
    /*
     * on change
    */
    std::function<void(host_t&)> on_remove_;


protected:
    /*
     * make host name
    */
    auto make_host_name(const ext::value& data) -> ext::text;
    /*
     * matches_filter
    */
    bool matches_filter(ext::text_view text);


protected:
    /*
     * init actions
    */
    void init_actions();
    /*
     * init events
    */
    void init_events();
    /*
     * init data
    */
    void init_data();


protected:
    /*
     * on edit group
    */
    void on_edit_group(int64_t id);
    /*
     * on context menu
    */
    void on_context_menu();


public:
    /*
     * convert protocol
    */
    ext::text convert_protocol(ext::text_view protocol,ext::text_view default_protocol);


public:
    /*
     * add group
    */
    void add_group(const ext::value& data);
    /*
     * add host
    */
    void add_host(const ext::value& data,bool connect = false);
    /*
     * edit group
    */
    void edit_group(std::int64_t id,const ext::value& data);
    /*
     * edit host
    */
    void edit_host(std::int64_t id,const ext::value& data);
    /*
     * remove group
    */
    void remove_group(std::int64_t id);
    /*
     * remove host
    */
    void remove_host(std::int64_t id);
    /*
     * connect host
    */
    void connect_host(const ext::uri::address& address,ext::text_view default_protocol);


public:
    /*
     * on change
    */
    template<typename handler_type>
    void on_change(const handler_type& handler)
    {
        on_change_ = handler;
    }
    /*
     * on remove
    */
    template<typename handler_type>
    void on_remove(const handler_type& handler)
    {
        on_remove_ = handler;
    }


public:
    /*
     * show
    */
    void show();
    /*
     * clear
    */
    void clear();
    /*
     * init
    */
    void init(ext::ui::node_t* protocol_icons);

};

}

#endif
