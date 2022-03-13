#include "pro_global.h"

namespace pro
{

global::global(ext::ui::application& application) :
    app(application),
    named_mutex(ext::os::cpu::hash(),pro::Client_Bin),
    workspace(application.variables.workspace),
    icons_mime((workspace / "icons").u8string(),"png","mimetypes",(workspace / "icons/mimetypes/24/none.png").u8string()),
    icons_country((workspace / "icons" / "country").u8string(),"svg")
{

}

global::~global()
{
    if(io_contexts_){
        io_contexts_->stop();
        io_contexts_->join();
    }
    if(io_worker_){
        io_worker_->stop();
        io_worker_->join();
    }
    delete ipdb;
}


///----------------------------
ext::ui::samples::messages* global::messages()
{
    if(messages_){
        return messages_;
    }
    auto path = workspace / "ui/messages.sml";
    messages_ = new ext::ui::samples::messages(path);

    if(!messages_->ui){
        ext::ui::alert("error","error",ext::text(u8"Load UI file " + path.u8string() + u8" failed."))();
        ext::safe_delete(messages_);
    }
    return messages_;
}

ext::worker* global::io_worker()
{
    if(!io_worker_){
        io_worker_ = std::make_unique<ext::worker>();
        io_worker_->start();
    }
    return io_worker_.get();
}

ext::tcp::connector* global::tcp_connector()
{
    if(!io_contexts_){
        io_contexts_ = std::make_unique<ext::io_contexts>(2);
        ssl_context_ = std::make_unique<ext::net::ssl::context>(ext::net::ssl::context::sslv23);
        io_contexts_->start();
    }
    if(!tcp_connector_){
        tcp_connector_ = std::make_unique<ext::tcp::connector>(*io_contexts_,*ssl_context_);
    }
    return tcp_connector_.get();
}

ext::text global::endpoint_to_country(const ext::text& endpoint_str)
{
    if(!ipdb){
        ext::text text;
        ext::try_new(ipdb)->open(workspace / "lib" / "ip.mmdb",text);
    }
    if(ipdb->is_open() && !endpoint_str.empty())
    {
        auto error2   = std::error_code();
        auto endpoint = ext::net::tcp::make_endpoint(endpoint_str,error2);

        if(!error2 && !endpoint.address().is_unspecified()){
            return ipdb->country(endpoint.address());
        }
    }
    return {};
}


///----------------------------
ext::text global::error_text(std::int32_t code)
{
    ext::text error_text = ext::ui::lang(errors::text(code));

    if(errors::is_custom(code)){
        error_text += " " + std::to_string(errors::to_custom_code(code));
    }
    return error_text;
}


///----------------------------
ext::value global::task_config(uint8_t type)
{
    switch(type)
    {
    case protocol::Task_HTTP:
        return configs["http_task"];
    case protocol::Task_FTP:
        return configs["ftp_task"];
    case protocol::Task_Torrent:
        return configs["torrent_task"];
    case protocol::Task_Ed2k:
        return configs["ed2k_task"];
    }
    return {};
}


///----------------------------
void global::setting(ext::text_view name,ext::value_view value)
{
    settings[name]    = value;
    settings_changed_ = true;
}

void global::settings_save()
{
    if(settings_changed_){
        settings_changed_ = false;
        ext::cfile::write(workspace / "lib" / FileU_Config_File_Name,"wb",settings.stringify());
    }
}

void global::shutdown()
{
    shutting_down = true;

    if(service){
        service->close();
        service->join();
    }
    ipc.stop();
    ipc.join();
    named_mutex.unlock();
}

}
