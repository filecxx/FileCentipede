#ifndef PRO_GLOBAL_H
#define PRO_GLOBAL_H

#include "pro_headers.h"

namespace pro
{

class global
{
    friend class main_window;

public:
    global(ext::ui::application& application);


public:
    ~global();


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
    std::error_code error;
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


public:
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
     * subscribes
    */
    std::unordered_map<int64_t,ext::value> subscribes;
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


public:
    /*
     * task config
    */
    ext::value task_config(uint8_t type);
    /*
     * messages
    */
    ext::ui::samples::messages* messages();
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
        if(service){
            return service->send(std::forward<Arguments>(args)...);
        }
        return false;
    }
    /*
     * send client
    */
    bool send(const std::initializer_list<std::pair<ext::value_view,ext::value_view>>& list)
    {
        if(service){
            return service->send(list);
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

};

}

#endif
