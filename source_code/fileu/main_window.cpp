#include "main_window.h"

namespace pro
{

main_window::main_window(ext::ui::application& app) :
    zzz(app),
    methods_(zzz,ui),
    file_browser_(zzz,ui),
    tasks_(zzz,ui)
{
    init_config();
    methods_.init();
}

main_window::~main_window()
{
    ext::ui::clear_timeout(timer_);
    zzz.shutdown();
}


///-------------------------
void main_window::init_ui()
{
    auto font_name = zzz.settings.get("fonts");
    auto font_size = 0;

    if(auto size = zzz.settings.get("font_size");size.is_number()){
        font_size = size.int32();
    }
    zzz.app.font(font_name,font_size);
}

void main_window::init_config()
{
    static std::pair<ext::text,ext::text> default_lang[] = {
        {"__version__",ext::f2str(pro::Version,1)},
        {"__workspace__",zzz.workspace}
    };
    ext::text conf;
    ext::text lang_name;

    if(ext::cfile::read(zzz.workspace / "lib" / pro::FileU_Config_File_Name,conf).value() == 0 && (zzz.settings = ext::json::parse(conf)).is_map()){
        lang_name = zzz.settings.text_view("lang");
        init_ui();
    }
    if(!ext::ui::lang.load_file(zzz.workspace / "lang", ".lang",lang_name.empty() ? ext::ui::language::locale_name() : lang_name,"en_US")){
        ext::debug <<= "load lang failed";
    }
    for(auto& pair : default_lang){
        ext::ui::lang(pair.first,pair.second);
    }
}

void main_window::init_views()
{
    auto view_statusbar = ui.cast_id<ext::ui::action*>("act_view_statusbar");
    auto view_nav       = ui.cast_id<ext::ui::action*>("act_view_nav");
    auto view_catalogs  = ui.cast_id<ext::ui::action*>("act_view_catalogs");

    view_statusbar->on_trigger([this](auto checked){
        zzz.setting("view_statusbar",checked);
        window_->statusBar()->setVisible(checked);
    });
    view_nav->on_trigger([this](auto checked){
        ui("#nav")->object.visible(checked);
        zzz.setting("view_nav",checked);
    });
    view_catalogs->on_trigger([this](auto checked){
        if(current_tab_ == 0){
            ui("#nav_tasks_catalogs_panel")->object.visible(checked);
        }
        zzz.setting("view_catalogs",checked);
    });
    if(zzz.settings.get("view_statusbar") == false){
        window_->statusBar()->hide();
        view_statusbar->checked(false);
    }
    if(zzz.settings.get("view_nav") == false){
        ui("#nav")->object.hide();
        view_nav->checked(false);
    }
    if(zzz.settings.get("view_catalogs") == false){
        ui("#nav_tasks_catalogs_panel")->object.hide();
        view_catalogs->checked(false);
    }
}

void main_window::init_sizes(ext::ui::object& object,bool booting)
{
    int32_t width  = 0;
    int32_t height = 0;

    if(zzz.settings.get("save_window_size") != true){
        object.show("center");
    }else if(zzz.settings.get("maximize") == true){
        window_->move_to_center();
        window_->showMaximized();
    }else{
        if(auto val = zzz.settings.get("width");val.is_number()){
            width = val.int32();
        }
        if(auto val = zzz.settings.get("height");val.is_number()){
            height = val.int32();
        }
        if(width > 200 && height > 100){
            window_->resize(width,height);
        }
        object.show("center");
    }
    if(zzz.settings.get("tray_icon") == true && (zzz.settings.get("silent_mode") == true || booting)){
        object.hide();
        init_tray();
    }
}

void main_window::init_events()
{
    window_->on_drop([this](const auto& paths)
    {
        for(auto& path : paths){
            add_task(path);
        }
    });
    window_->on_resize([this](auto){
        methods_.window_size_changed_ = true;
    });
}

void main_window::init_tabs()
{
    ui.cast_id(main_tab_,"main_tab");
    main_tab_->on_change([this](auto index)
    {
        ui.cast<ext::ui::widget*>("#nav")->layout_items([](auto item){
            item->widget()->hide();
            return false;
        });
        switch(current_tab_ = index)
        {
        case 0:
            return tasks_.init();
        case 1:
            return file_browser_->init(main_tab_,(ext::ui::statusbar*)window_->statusBar());
        case 2:
            return ext::try_new<pro::search_engine::main>(search_engine_,zzz,ui)->init(main_tab_);
        }
    });
    tasks_.init();
}

void main_window::init_actions()
{
    ui.on_action_id("act_tasks_add_catalog",[this](auto){
        (new catalogs::edit(zzz))->exec();
    });

    ///----------------
    ui.on_action_id("act_open",[this](auto){
        open_files();
    });

    ///----------------
    ui.on_action_id("act_view_desktop_shortcuts",[this](auto){
        (new pro::view::desktop_shortcuts(zzz))->exec();
    });
    ui.on_action_id("act_view_statistics",[this](auto){
        ext::try_new<pro::view::statistics>(view_statistics_,zzz)->exec();
    });

    ///----------------
    ui.on_action_id("act_tool_http",[this](auto){
        (new pro::tools::http(zzz))->exec();
    });
    ui.on_action_id("act_tool_create_address",[this](auto){
        (new pro::tools::create_address(zzz))->exec();
    });
    ui.on_action_id("act_tool_create_torrent",[this](auto){
        (new pro::tools::create_torrent(zzz))->exec();
    });
    ui.on_action_id("act_tool_file_merge",[this](auto){
        (new pro::tools::file_merge(zzz))->exec();
    });

    ///----------------
    ui.on_action_id("act_setting_proxy",[this](auto){
        ext::try_new<pro::settings::proxies>(proxies_,zzz)->exec();
    });
    ui.on_action_id("act_setting_site_rules",[this](auto){
        ext::try_new<pro::settings::site_rules>(site_rules_,zzz)->exec();
    });
    ui.on_action_id("act_setting_tracker",[this](auto){
        ext::try_new<pro::settings::trackers>(trackers_,zzz)->exec();
    });
    ui.on_action_id("act_setting_filter",[this](auto){
        ext::try_new<pro::settings::filter>(filter_,zzz)->exec();
    });
    ui.on_action_id("act_setting_torrent_query",[this](auto){
        ext::try_new<pro::settings::torrent_query>(torrent_query_,zzz)->exec();
    });
    ui.on_action_id("act_settings",[&](auto){
        ext::try_new<pro::settings::main>(settings_,zzz,settings_)->exec();
    });


    ///----------------
    ui.on_action_id("act_help_update",[this](auto){
        ext::try_new<pro::help::update>(help_update_,zzz)->exec();
    });
    ui.on_action_id("act_help_install",[this](auto){
        (new pro::help::install(zzz))->exec();
    });
    ui.on_action_id("act_help_uninstall",[this](auto){
        (new pro::help::uninstall(zzz))->exec();
    });
    ui.on_action_id("act_help_translate",[this](auto){
        (new pro::help::translator(zzz))->exec();
    });
    ui.on_action_id("act_help_activation",[this](auto){
        ext::value value;
        on_activation_query(value);
    });


    ///----------------
    ui.on_click("#global_speed_download",[this](auto){
        (new pro::settings::speed_limit(zzz,"download"))->exec();
    });
    ui.on_click("#global_speed_upload",[this](auto){
        (new pro::settings::speed_limit(zzz,"upload"))->exec();
    });
}

void main_window::init_ipc()
{
    Ext_Return_If(zzz.shutting_down);
    ext::debug <<= "init_ipc";

    if(!pro::is_service_running()){
        show_ipc_loading();
    }
    if(!zzz.ipc.start(pro::Client_Bin,pro::IPC_Space,pro::Version_IPC)){
        ext::ui::alert("error","error"_lang,"start ipc error.")();
        return zzz.app.exit();
    }
    zzz.ipc.on_client([this](auto client){
        on_client(client);
    });
    zzz.ipc.on_stop([this]
    {
        if(zzz.service){
            zzz.service->close();
            zzz.service->join();
        }
    });
    connect_service();
}

void main_window::init_tray()
{
    if(ui.import("ui/tray.sml")){
        auto tray = ui.cast_id<ext::ui::tray*>("tray");
        tray->bind(window_);
        tray->show();
        methods_.tray_initialized_ = true;
        zzz.app.quit_on_last_window_closed(false);
        window_->ignore_on_close(true);
    }
}

void main_window::init_clipboard()
{
    static pro::tasks::add_task*         instance = nullptr;
    static std::vector<ext::text>        addresses;
    static std::unordered_set<ext::text> suffixes;

    ext::ui::clipboard::on_change([this](bool is_owner)
    {
        if(!zzz.service || is_owner || !ext::ui::clipboard::has_text() || zzz.settings.get("watch_clipboard") != true){
            return;
        }
        auto& setting = zzz.configs["general_clipboard"];

        if(!setting.is_map()){
            return;
        }
        ext::parser::split(setting.text_view("suffixes"),',',[&](auto text,auto){
            suffixes.emplace(text);
            return false;
        });
        ext::parser::split_lines(ext::ui::clipboard::text(),[&](auto line,auto)
        {
            pro::uri uri;

            if(uri.analyze(line,ext::String,false) && uri.scheme != "hash")
            {
                if(uri.custom_protocol != pro::uri::Custom_None){
                    if(setting.get("enable_"_text + uri.custom_protocol_text()) == false){
                        return false;
                    }
                }else if(setting.get("enable_"_text + uri.scheme) == false){
                    return false;
                }else if((uri.type == protocol::Task_HTTP || uri.type == protocol::Task_FTP || uri.type == protocol::Task_SSH)){
                    ext::uri::address address;

                    if(!ext::uri::parse(uri.config.text(),address) || address.path().suffix().empty() || !suffixes.contains(address.path().suffix())){
                        return false;
                    }
                }
                addresses.emplace_back(boost::trim_copy(line));
            }
            return false;
        });
        if(addresses.empty()){

        }else if(instance){
            if(instance->append(addresses)){
                instance->active();
            }
        }else{
            instance = new pro::tasks::add_task(zzz,false,false);
            instance->on_delete([this]{
                instance = nullptr;
            });
            instance->exec();
            instance->append(addresses);
        }
        addresses.clear();
        suffixes.clear();
    });
    methods_.clipboard_initialized_ = true;
}

void main_window::init_timer()
{
    Ext_Return_If(zzz.shutting_down);

    auto now = ext::time::steady_now();
    timepoint_interval_        = now;
    timepoint_interval_second_ = now;

    on_timer();
}

void main_window::init_plugins()
{

}


///-------------------------
void main_window::show_ipc_loading()
{
    ext::ui::post([this]
    {
        Ext_Return_If(zzz.shutting_down);

        auto title    = ext::text();
        auto text     = ext::text();
        auto messages = zzz.messages();
        auto widget   = messages->modal("#ipc_loading",window_);
        auto visible  = false;

        if(pro::is_service_running()){
            title = "connecting"_lang;
            text  = "trying_to_establish_with_filec"_lang;
        }else{
            visible = true;
            title   = "waiting"_lang;
            text    = "waiting_for_filec_running"_lang;
        }
        messages->ui.cast<ext::ui::label*>("#ipc_loading_title")->text(title);
        messages->ui.cast<ext::ui::label*>("#ipc_loading_text")->text(text);
        messages->ui.cast<ext::ui::tool_button*>("#ipc_loading_launch")->visible(visible);

        widget->move_to_center();
    });
}

void main_window::connect_service()
{
    Ext_Return_If(zzz.shutting_down);

    ext::ipcx::connect(pro::Service_Bin,pro::Version_IPC,[this](auto error,auto connection)
    {
        if(error){
            show_ipc_loading();
            return connect_service();
        }
        ext::ui::post([this,connection]() mutable{
            on_service_connected(connection);
        });
        connection->on_close([this]{
            ext::ui::post(std::bind(&main_window::on_service_close,this));
        });
        connection->on_message([this](auto data,auto size){
            on_message(data,size);
        });
        connection->send({{"@",protocol::Message_Version}});
        connection->send({{"@",protocol::Message_Configs}});
        connection->send({{"@",protocol::Message_Proxies}});
        connection->send({{"@",protocol::Message_Catalogs}});
        connection->send({{"@",protocol::Message_Paths}});
        connection->send({{"@",protocol::Message_Subscribes}});
        connection->send({{"@",protocol::Message_Tasks}});
        connection->send({{"@",protocol::Message_NFS_Hosts}});
    });
}


///-------------------------
void main_window::on_timer()
{
    timer_ = ext::ui::set_timeout([this]
    {
        Ext_Return_If(zzz.shutting_down);
        auto now = ext::time::steady_now();

        if(now - timepoint_interval_ >= 200ms){
            on_timer_200ms(now);
        }
        if(now - timepoint_interval_second_ >= 1s){
            on_timer_1s(now);
        }
        tasks_.on_timer(now);
        on_timer();
    },100ms);
}

void main_window::on_timer_200ms(ext::steady_time_t now)
{
    for(auto& iter : methods_.interval_handlers_){
        ext::ui::methods::call(iter.second.cast<ext::ui::node_t*>());
    }
    if(methods_.window_size_changed_ && zzz.settings.get("save_window_size") == true)
    {
        if(window_->isMaximized()){
            zzz.setting("maximize",true);
        }else{
            zzz.setting("maximize",false);
            zzz.setting("width",window_->width());
            zzz.setting("height",window_->height());
        }
        methods_.window_size_changed_ = false;
    }
    timepoint_interval_ = now;
    zzz.settings_save();
    zzz.send({{"@",protocol::Message_Status}});
}

void main_window::on_timer_1s(ext::steady_time_t now)
{
    if(zzz.service)
    {
        if(!methods_.tray_initialized_ && zzz.settings.get("tray_icon") == true){
            init_tray();
        }
        if(!methods_.clipboard_initialized_ && zzz.settings.get("watch_clipboard") == true){
            init_clipboard();
        }
        if(now - timepoint_interval_activation_ >= dialogs::code::Activation_Interval){
            zzz.send({{"@",protocol::Message_Activation_Expired}});
            timepoint_interval_activation_ = now;
        }
    }
    timepoint_interval_second_ = now;
}


///========================================
void main_window::on_version(ext::value& json)
{
    float version = json.number("version");

    if(version != pro::Version)
    {
        zzz.shutdown();
        ext::text prefix = "["_text + "version"_lang + "] ";
        ext::text text   = prefix + "fileu : " + ext::f2str(pro::Version,1) + "<br/>" + prefix + "filec : " + ext::f2str(version,1);
        ext::ui::alert("error","error"_lang,text)();
        std::exit(9);
    }
}

void main_window::on_stop()
{
    zzz.shutdown();

    if(methods_.tray_initialized_){
        delete ui.cast_id<ext::ui::tray*>("tray");
    }
    std::exit(0);
}

void main_window::on_service_close()
{
    ext::debug <<= "on_service_close";

    zzz.service.reset();
    tasks_.clear();
    file_browser_.clear();

    connect_service();
    show_ipc_loading();
}

void main_window::on_service_connected(std::shared_ptr<ext::ipcx::connection>& connection)
{
    ext::debug <<= "on_service_connected";

    if(!methods_.actions_initialized_){
        methods_.actions_initialized_ = true;
        init_actions();
    }
    if(zzz.settings.uint8("installed") == 1){
        ext::text path = (zzz.workspace / "ui/tools/browsers.sml").lexically_normal();
        ext::ui::arguments arguments(ext::ui::shared_stack,{path,"#main"});
        ext::ui::methods::invokers_global["open-window"](arguments);
        zzz.setting("installed",2);
    }
    zzz.service = connection;
    zzz.messages()->widget("#ipc_loading")->hide(true);

    for(auto& value : queued_messages_){
        zzz.send(value);
    }
    queued_messages_.clear();
}

void main_window::on_subscribe_add(ext::value& json)
{
    auto id   = json.int64("id");
    auto type = json.uint16("type");

    if(type == protocol::Subscribe_Trackers){
        if(trackers_){
            trackers_->subscribe_add(json);
        }
    }
    zzz.subscribes[id] = json;
}

void main_window::on_subscribe_update(ext::value& json)
{
    auto id   = json.int64("id");
    auto type = json.uint16("type");

    if(type == protocol::Subscribe_Trackers){
        if(trackers_){
            trackers_->subscribe_update(json,id);
        }
    }
    zzz.subscribes[id] = json;
}

void main_window::on_subscribe_remove(ext::value& json)
{
    auto id   = json.int64("id");
    auto type = json.uint16("type");

    if(type == protocol::Subscribe_Trackers){
        if(trackers_){
            trackers_->subscribe_remove(json,id);
        }
    }
    zzz.subscribes.erase(id);
}

void main_window::on_error(ext::value& json)
{
    auto text   = json.text("text");
    auto type   = protocol::Message_Types_Text[json.uint16("type")];
    auto string = ext::ui::lang(type) + ":"_text + global::error_text(json.int32("error")) + " " + text;

    ext::ui::alert("error","error"_lang,string)();
}

void main_window::on_client_message(ext::value& json)
{
    auto type = json.get("type");

    if(type == "error"){
        ext::ui::alert("error","error"_lang,global::error_text(json.int32("error")))();
    }else if(type == "active"){
        if(methods_.tray_initialized_ && !window_->visible()){
            window_->show();
        }else{
            window_->show_active();
            window_->show_top(false);
        }
    }else if(type == "event"){
        if(methods_.tray_initialized_){
            ui.cast_id<ext::ui::tray*>("tray")->flashing(6);
        }
        zzz->play_sound("event");
    }else if(type == "add_task"){
        add_task(json.text_view("uri"),true);
    }
}

void main_window::on_xmessage(uint16_t at,ext::value& json)
{
    auto xid  = json.int64("xid");
    auto iter = zzz.ipc_xhandlers_.find(xid);

    if(iter != zzz.ipc_xhandlers_.end()){
        iter->second(json);
    }
}

void main_window::on_message2(uint16_t at,ext::value& json)
{
    if(auto iter = zzz.ipc_handlers_.find(at);iter != zzz.ipc_handlers_.end())
    {
        if(iter->second.is_number()){
            zzz.ipc_invokers_[iter->second.uint32()](json);
        }else if(iter->second.is_caller()){
            ext::ui::methods::call(iter->second.cast<ext::ui::node_t*>(),{json});
        }else for(auto& item : iter->second.cast<ext::ui::node_t*>()->items){
            if(item.is_caller()){
                ext::ui::methods::call(item.cast<ext::ui::node_t*>(),{json});
            }
        }
    }
}

void main_window::on_message(uint16_t at,ext::value& json)
{
    switch(json.erase("@");at)
    {
    case protocol::Message_Version:
        return on_version(json);
    case protocol::Message_Stop:
        return on_stop();
    case protocol::Message_UI:
        return on_client_message(json);
    case protocol::Message_Error:
        return on_error(json);
    case protocol::Message_Task_Refresh_Address:
        return tasks_.on_task_refresh_address(json);
    case protocol::Message_Task_Edit:
        return tasks_.on_task_edit(json);
    case protocol::Message_Task_Confirm_Links:
        return (new tasks::confirm_links(zzz))->exec(json);
    case protocol::Message_Configs:
        zzz.configs = json;
        zzz.configs.erase("@");
        return;
    case protocol::Message_Proxies:
        zzz.proxies = json.extract("items");
        return;
    case protocol::Message_Paths:
        zzz.paths = json.extract("items");
        return;
    case protocol::Message_Subscribes:
        for(zzz.subscribes.clear();auto& item : *json["items"].cast_array()){
            zzz.subscribes.emplace(item.int64("id"),item);
        }
        return;
    case protocol::Message_NFS_Hosts:
        return file_browser_.on_hosts(json);
    case protocol::Message_Catalogs:
        return tasks_.on_catalogs(json);
    case protocol::Message_Status:
        return on_status(json);
    case protocol::Message_Trackers:
        return on_trackers(json);
    case protocol::Message_Path_Add:
        return zzz.paths.emplace_back(json.get("path"));
    case protocol::Message_Catalog_Add:
        return tasks_.on_catalog_add(json);
    case protocol::Message_Catalog_Update:
        return tasks_.on_catalog_update(json);
    case protocol::Message_Catalog_Remove:
        return tasks_.on_catalog_remove(json);
    case protocol::Message_Task_Status:
        return tasks_.on_task_status(json);
    case protocol::Message_Task_Progress:
        return tasks_.on_task_progress(json);
    case protocol::Message_Task_Files:
        return tasks_.on_task_files(json);
    case protocol::Message_Task_Details:
        return tasks_.on_task_detail(json);
    case protocol::Message_Task_Config:
        return tasks_.on_task_config(json);
    case protocol::Message_Task_Rename:
        return tasks_.on_task_renamed(json);
    case protocol::Message_Task_Remove:
        return tasks_.on_task_removed(json);
    case protocol::Message_Subscribe_Add:
        return on_subscribe_add(json);
    case protocol::Message_Subscribe_Update:
        return on_subscribe_update(json);
    case protocol::Message_Subscribe_Remove:
        return on_subscribe_remove(json);
    case protocol::Message_Torrent_Create:
        return on_xmessage(at,json);
    case protocol::Message_FS:
        return file_browser_.on_status(json);
    case protocol::Message_FS_Group_Add:
        return file_browser_.on_group_add(json);
    case protocol::Message_FS_Group_Edit:
        return file_browser_.on_group_edit(json);
    case protocol::Message_FS_Group_Remove:
        return file_browser_.on_group_remove(json);
    case protocol::Message_FS_Host_Add:
        return file_browser_.on_host_add(json);
    case protocol::Message_FS_Host_Edit:
        return file_browser_.on_host_edit(json);
    case protocol::Message_FS_Host_Remove:
        return file_browser_.on_host_remove(json);
    case protocol::Message_Activation_Expired:
        return on_activation_expired(json);
    case protocol::Message_Activation_Query:
    case protocol::Message_Activation_Reset:
        return on_activation_query(json);
    default:
        return on_message2(at,json);
    }
}

void main_window::on_message(uint8_t* data,uint32_t length)
{
    auto json = ext::json::parse(data,length);
    auto type = ext::value();

    if(!json.is_map()){
        ext::debug << "parse json failed " <<= ext::text_view((const char*)data,length);
    }else if(!(type = json.get("@")).is_number()){
        ext::debug <<= "@ field is missing ";
    }else ext::ui::post([this,type = type.uint16(),Ext_Move(json)]() mutable{
        on_message(type,json);
    });
}

void main_window::on_client(std::shared_ptr<ext::ipcx::client> client)
{
    client->on_message([this](auto data,auto size){
        on_message(data,size);
    });
}

void main_window::on_status(ext::value& json)
{
    if(!status_form_){
        status_form_ = ext::ui::form(ui.root());
    }
    for(auto& iter : *json.cast_map())
    {
        auto name = iter.first.string_view();

        if(name == "@"){
            continue;
        }
        if(auto node = ui.id(name);node && node->object)
        {
            ext::value value = iter.second;

            if(name.starts_with("global_speed")){
                value = " " + ext::format_number("bytes/s",iter.second.number());
            }
            ext::ui::methods::invoke(node->object,"text",value);
        }
    }
    status_form_.values(json);
    zzz.status = std::move(json);
}

void main_window::on_trackers(ext::value& json)
{
    if(trackers_){
        trackers_->update(json);
    }
}

void main_window::on_activation_expired(ext::value& json)
{
    Ext_Return_If(json.get("expired") != true);

    ext::value value;
    on_activation_query(value);
}

void main_window::on_activation_query(ext::value& json)
{
    if(auto error = json.get("error");error.is_number())
    {
        if(error.number() != 0){
            ext::ui::alert("error","error"_lang,zzz->error_text(error.int32()))();
        }else{
            ext::ui::alert("info","success"_lang,"success")();
            return;
        }
    }
    ext::try_new<pro::dialogs::code>(dialog_code_,zzz)->exec(json,[this](ext::steady_time_point_t timepoint){
        timepoint_interval_activation_ = timepoint;
        dialog_code_ = nullptr;
    });
}


///-------------------------
void main_window::open_files()
{
    ext::local<128> filter;
    filter << "*.torrent *.m3u8;;" << "all_files"_lang << " (*.*)";

    for(auto& path : ext::ui::file_dialog::open_files("open_file"_lang,"",filter.string_view())){
        add_task(path);
    }
}

void main_window::add_task(ext::text_view text,bool important)
{
    auto uri     = pro::uri();
    auto message = ext::value();

    if(uri.analyze(text,ext::Void)){
        message = {{"@",protocol::Message_Task_Add},{"type",uri.type},{"uri",text}};
    }else{
        message = {{"@",protocol::Message_Task_Add_File},{"path",text}};
    }
    if(zzz.service){
        zzz.send(message);
    }else if(important){
        queued_messages_ << message;
    }
}


///-------------------------
void main_window::create(bool booting)
{
    if(!(ui = sml_.instantiate<ext::ui::model>(zzz.workspace / "ui/main.sml",zzz.error))){
        ext::ui::alert("error","fatal"_lang,"couldn't load ui/main.sml")();
        std::exit(0);
    }
    auto object = ui.id("main")->object;
    window_ = object.cast<ext::ui::window*>();
    window_->central_layout_margin(1);

    init_views();
    init_sizes(object,booting);
    init_events();

    zzz.io_worker()->set_timeout([this]{
        init_tabs();
        init_ipc();
        init_timer();
        init_plugins();
    },100ms);
}


}
