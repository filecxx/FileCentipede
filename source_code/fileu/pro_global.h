#ifndef PRO_GLOBAL_H
#define PRO_GLOBAL_H

#include "pro_headers.h"

namespace pro
{

class global
{
    friend class main_window;
    friend class methods;

public:
    global(ext::ui::application& application);


public:
    ~global();


public:
    pro::global* operator->(){
        return this;
    }


public:
    /*
     * app
    */
    ext::ui::application& app;
    /*
     * named mutex
    */
    ext::named_mutex named_mutex;
    /*
     * error
    */
    ext::error_code error;
    /*
     * workspace
    */
    ext::fs::path& workspace;
    /*
     * mime icons
    */
    ext::ui::icons icons_mime;
    /*
     * country icons
    */
    ext::ui::icons icons_country;
    /*
     * taskbar
    */
    ext::ui::taskbar taskbar;
    /*
     * sound
    */
    ext::audios::simple sound;
    /*
     * ipc
    */
    ext::ipcx::service ipc;
    /*
     * service connection
    */
    std::shared_ptr<ext::ipcx::connection> service;
    /*
     * random
    */
    std::unique_ptr<ext::random> random;


public:
    /*
     * filec state
    */
    ext::value filec_state;
    /*
     * fileu settings
    */
    ext::value settings;
    /*
     * configs
    */
    ext::value configs;
    /*
     * proxies
    */
    ext::value proxies;
    /*
     * catalogs
    */
    ext::value catalogs;
    /*
     * paths
    */
    ext::value paths;
    /*
     * status
    */
    ext::value status;
    /*
     * site rules
    */
    std::unordered_map<int64_t,ext::value> site_rules;
    /*
     * subscribes
    */
    std::unordered_map<int64_t,ext::value> subscribes;
    /*
     * nfs groups
    */
    std::unordered_map<int64_t,ext::value> nfs_groups;
    /*
     * nfs hosts
    */
    std::unordered_map<int64_t,ext::value> nfs_hosts;
    /*
     * xid
    */
    std::atomic_uint64_t xid = 1;


public:
    /*
     * ipdb
    */
    doom::ipdb* ipdb = nullptr;


protected:
    /*
     * settings changed
    */
    ext::boolean_t settings_changed_ = false;
    /*
     * shutting down
    */
    ext::boolean_t shutting_down = false;


protected:
    /*
     * io worker
    */
    std::unique_ptr<ext::worker> io_worker_;
    /*
     * io context
    */
    std::unique_ptr<ext::io_contexts> io_contexts_;
    /*
     * ssl context
    */
    std::unique_ptr<ext::net::ssl::context> ssl_context_;
    /*
     * tcp connector
    */
    std::unique_ptr<ext::tcp::connector> tcp_connector_;


protected:
    /*
     * ipc invokers (for c++ only)
    */
    std::vector<ext::func_void<ext::value&>> ipc_invokers_;
    /*
     * ipc handlers (c++ and sml)
    */
    std::unordered_map<std::uint16_t,ext::value_view> ipc_handlers_;
    /*
     * ipc xhandlers (c++)
    */
    std::unordered_map<std::int64_t,ext::func_void<ext::value&>> ipc_xhandlers_;
    /*
     * messages
    */
    ext::ui::samples::messages* messages_ = nullptr;
    /*
     * messages
    */
    ext::ui::samples::messages* messages_nfs_ = nullptr;


public:
    /*
     * task config
    */
    ext::value task_config(uint8_t type);
    /*
     * task config
    */
    ext::void_t task_config(uint8_t type,ext::text_view url,ext::value& value);
    /*
     * messages
    */
    ext::ui::samples::messages* messages();
    /*
     * messages nfs
    */
    ext::ui::samples::messages* messages_nfs();
    /*
     * io worker
    */
    ext::worker* io_worker();
    /*
     * tcp connector
    */
    ext::tcp::connector* tcp_connector();
    /*
     * endpoint to country
    */
    ext::text endpoint_to_country(const ext::text& endpoint_str);
    /*
     * random temp directory
    */
    ext::fs::path random_temp_directory();


public:
    /*
     * error text
    */
    static ext::text error_text(std::int32_t code);


public:
    /*
     * send
    */
    template<typename...Arguments>
    bool send(Arguments&&...args)
    {
        if(auto ptr = service){
            return ptr->send(std::forward<Arguments>(args)...);
        }
        return false;
    }
    /*
     * send client
    */
    bool send(const std::initializer_list<std::pair<ext::value_view,ext::value_view>>& list)
    {
        if(auto ptr = service){
            return ptr->send(list);
        }
        return false;
    }
    /*
     * ipc bind
    */
    template<typename handler_type>
    void ipc_bind(std::uint16_t at,const handler_type& handler)
    {
        auto slot = ipc_invokers_.size();

        ipc_invokers_.push_back(handler);
        ipc_handlers_[at] = ext::value_view(slot);
    }
    /*
     * ipc xbind
    */
    template<typename handler_type>
    void ipc_xbind(std::int64_t xid,const handler_type& handler)
    {
        ipc_xhandlers_[xid] = handler;
    }
    /*
     * ipc unbind
    */
    void ipc_unbind(std::int64_t xid)
    {
        if(xid != 0){
            ipc_xhandlers_.erase(xid);
        }
    }


public:
    /*
     * setting
    */
    void setting(ext::text_view name,ext::value_view value);
    /*
     * settings save
    */
    void settings_save();
    /*
     * shutdown
    */
    void shutdown();
    /*
     * play sound
    */
    void play_sound(const ext::text& name);

};

}

#endif
