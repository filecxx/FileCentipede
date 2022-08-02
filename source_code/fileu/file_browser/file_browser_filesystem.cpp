#include "file_browser_hosts.h"
#include "file_browser_filesystem.h"

namespace pro::file_browser
{

filesystem::filesystem(pro::file_browser::global& global,pro::file_browser::hosts* hosts,ext::ui::tab* tabs,ext::ui::statusbar* statusbar) :
    pro::sample<pro::file_browser::global>(global,global->workspace / "ui/file_browser/filesystem.sml"),
    hosts_(hosts),
    tabs_(tabs),
    statusbar_(statusbar)
{
    ui.cast_id(widget_,"filesystem");
    ui.cast_id(grid_,"grid");
    ui.cast_id(loading_,"loading");
    ui.cast_id(loading_img_,"loading_img");
    ui.cast_id(protocols_,"protocols");
    ui.cast_id(addresses_,"addresses");

    init_actions();
    init_view();
    init_addresses();
    init_grid();
    init_shortcut();
}

filesystem::~filesystem()
{
    if(!operations_.empty()){
        zzz.invoke_alert<alert_operations_clear_type>(Alert_Operations_Clear,hid_,sid_);
    }
    ext::ui::clear_timeout(timer_loading_);
}


///----------------------------
void filesystem::init_actions()
{
    ui.on_action_id("act_upload",[this](auto){
        upload(false);
    });
    ui.on_action_id("act_upload_directory",[this](auto){
        upload(true);
    });
    ui.on_action_id("act_download",[this](auto){
        download();
    });
    ui.on_action_id("act_delete",[this](auto){
        remove();
    });
    ui.on_action_id("act_create_directory",[this](auto){
        create_directory();
    });
    ui.on_action_id("act_create_file",[this](auto){
        create_file();
    });
    ui.on_action_id("act_open",[this](auto){
        open();
    });
    ui.on_action_id("act_edit",[this](auto){
        open(ext::fs::Edit);
    });
    ui.on_action_id("act_open_new_tab",[this](auto){
        open_new_tab();
    });
    ui.on_action_id("act_rename",[this](auto){
        rename();
    });
    ui.on_action_id("act_move",[this](auto){
        move();
    });
    ui.on_action_id("act_cut",[this](auto){
        copy_path(true);
    });
    ui.on_action_id("act_copy",[this](auto){
        copy_path(false);
    });
    ui.on_action_id("act_paste",[this](auto){
        paste();
    });
    ui.on_action_id("act_attribute",[this](auto){
        attribute();
    });
    ui.on_action_id("act_search",[this](auto){
        search();
    });
    ui.on_action_id("act_super_cache",[this](auto){
        super_cache();
    });
    ui.on_action_id("act_clone",[this](auto){
        clone();
    });
    ui.on_action_id("act_filter",[this](auto val)
    {
        ui("#filter")->object.visible(filter_enabled_ = val);

        if(!filter_types_){
            init_filters();
        }
        on_filter();
    });
}

void filesystem::init_view()
{
    ui.on_action_id("act_view_icon",[this](auto){
        view_icon();
    });
    ui.on_action_id("act_view_tree",[this](auto){
        view_grid();
    });
}

void filesystem::init_addresses()
{
    ui.on_action_id("act_go_previous",[this](auto){
        addresses_->go_previous();
    });
    ui.on_action_id("act_go_next",[this](auto){
        addresses_->go_next();
    });
    ui.on_action_id("act_go_up",[this](auto){
        addresses_->go_up();
    });
    ui.on_action_id("act_refresh",[this](auto){
        refresh();
    });
    addresses_->on_uri([this](auto& text)
    {
        auto current = protocols_->value().text();
        text = current + "://" + text;
        return true;
    });
    addresses_->on_text_change([this](auto str)
    {
        ext::text         text = ext::ui::text(str);
        ext::uri::address address;

        if(ext::uri::parse(text,address) && !address.host().protocol().empty()){
            update_protocol(ext::text::lower(address.host().protocol()));
        }
    });
    addresses_->on_change([this](const auto& address)
    {
        if(address.host().empty()){
            return false;
        }
        return on_address_change(address);
    });
    addresses_->on_return([this](const auto& text,bool changed)
    {
        ext::uri::address address;

        if(!changed && ext::uri::parse(text,address) && !path_.empty() && operations_.empty()){
            on_address_change(address);
        }
    });
}

void filesystem::init_shortcut()
{
    grid_->on_key_press([this](auto e)
    {
        if(e->matches(QKeySequence::Copy)){
            return true;
        }else if(e->matches(QKeySequence::Cancel)){
            grid_->clear_selection();
            update_statusbar();
            return true;
        }
        return false;
    });
}

void filesystem::init_filters()
{
    auto& files = zzz->configs["filters"]["torrent_files"];

    ui.cast(filter_types_,"#filter_types");
    ui.cast(filter_rule_,"#filter_rules");
    ui.cast(filter_text_,"#filter_text");

    if(files.is_array())
    {
        for(auto& item : *files.cast_array()){
            filter_rule_->append(item.text_view("name"),item.text_view("rule"));
        }
    }
    filter_rule_->on_change([this](auto str){
        on_filter();
    });
    filter_types_->on_index_change([this](auto index){
        on_filter();
    });
    filter_text_->on_change([this](auto str){
        on_filter();
    });
}

void filesystem::init_grid()
{
    grid_->icons(&zzz->icons_mime);
    grid_->on_context_menu([this](auto){
        on_context_menu();
    });
    grid_->on_selection_changed([this]{
        update_actions();
    });
    grid_->on_double_click([this](auto index){
        on_double_click();
    });
    grid_->on_drop([this](const auto& paths){
        for(auto& path : paths){
            upload(path);
        }
    });
    grid_->sort_handler([this](auto left,auto right)
    {
        auto left_text  = grid_->sibling_text(left,0);
        auto right_text = grid_->sibling_text(right,0);
        auto left_type  = grid_->find_node(left_text);
        auto right_type = grid_->find_node(right_text);

        if(left_type && right_type && left_type->value.type != right_type->value.type)
        {
            if(left_type->value.type == ext::fs::file_type::directory){
                return 1;
            }else if(right_type->value.type == ext::fs::file_type::directory){
                return 0;
            }
        }
        return 2;
    });
}

void filesystem::init(std::int64_t id,std::int64_t sid,std::int64_t tid,std::uint16_t type)
{
    hid_   = id;
    sid_  = sid;
    type_ = type;
    widget_->data(tid);
}


///---------------------------
bool filesystem::on_address_change(const ext::uri::address& address)
{
    auto& host = address.host();

    if(host.protocol() != protocol_ || host.hostname() != host_ || host.port() != port_)
    {
        auto default_protocol = protocols_->value().text();
        auto protocol         = hosts_->convert_protocol(host.protocol(),default_protocol);

        if(protocol::filesystem_type(protocol) == protocol::FS_Types_Size){
            ext::ui::alert("error","error"_lang,"protocol_error"_lang)();
            return false;
        }
        hosts_->connect_host(address,default_protocol);
        return false;
    }
    list(address.path().string_view());
    addresses_->append(addresses_->value());

    return true;

}

void filesystem::on_context_menu()
{
    update_actions();
    grid_->show_context_menu();
}

void filesystem::on_double_click()
{
    open();
}

void filesystem::on_filter()
{
    if(filter_enabled_)
    {
        filter_value_text_ = boost::to_lower_copy(filter_text_->text());
        filter_value_type_ = filter_types_->currentIndex();
        filter_value_rule_regex_.clear();

        ext::parser::split_lines(filter_rule_->value().text_view(),[&](auto str,auto index){
            try{
                filter_value_rule_regex_.emplace_back(ext::text(str),std::regex_constants::ECMAScript | std::regex_constants::optimize | std::regex_constants::icase);
            }catch(...){}

            return false;
        });
    }
    grid_->each([&](auto node)
    {
        auto index = node->value.item->index();

        if(!filter_enabled_){
            grid_->row_visible(node->value.item->index(),true);
        }else{
            grid_->row_visible(index,!matches_filter(node->value.type,boost::to_lower_copy(node->name)));
        }
        return false;
    },true);
}


///---------------------------
void filesystem::on_status(std::uint16_t state,std::int64_t oid,ext::value& values)
{
    auto error = values.get("error");
    auto iter  = operations_.find(oid);

    Ext_Return_If(iter == operations_.end());

    auto& operation = iter->second;

    if(operation.state = state;error.is_number()){
        ext::ui::alert("error","error"_lang,zzz->error_text(error.uint16()) + "<br/>"_text + values.text("msg")).exec();
        erase_operation(iter);
        return zzz.invoke_alert<alert_operation_error_type>(Alert_Operation_Error,hid_,sid_,oid);
    }else if(state == protocol::State_FS_Done || state == protocol::State_FS_Failed || state == protocol::State_FS_Canceled){
        on_done(oid,operation,values);
        erase_operation(iter);
        return zzz.invoke_alert<alert_operation_done_type>(Alert_Operation_Done,hid_,sid_,oid,state);
    }else if(state == protocol::State_FS_Asking_Pass){
        on_ask_pass(values);
    }else if(state == protocol::State_FS_Listing){
        on_list(values);
    }else if(state == protocol::State_FS_Transfer){
        operation.state2 = values.uint16("state2");
        operation.state3 = values.uint16("state3");
    }
    zzz.invoke_alert<alert_operation_state_type>(Alert_Operation_State,hid_,sid_,oid,state,operation.state2,operation.state3);
}

void filesystem::on_done(std::int64_t oid,operation_t& operation,ext::value& values)
{
    switch(operation.method)
    {
    case ext::fs::File:
        return on_file(values);
    case ext::fs::Rename:
        return on_rename(values);
    case ext::fs::Move:
        return on_move(oid,values);
    case ext::fs::Copy:
        return on_copy(oid,values);
    case ext::fs::Remove:
    case ext::fs::Remove_All:
        return on_remove(values);
    case ext::fs::Attribute:
        return on_attribute(values);
    case ext::fs::Chmod:
        return on_chmod(values);
    case ext::fs::Create_File:
        return on_create_file(values);
    case ext::fs::Create_Dir:
        return on_create_dir(values);
    case ext::fs::Upload:
        return on_upload(operation,values);
    case ext::fs::Download:
    case ext::fs::Edit:
    case ext::fs::Open:
        return on_download(operation,values);
    }
}

void filesystem::on_ask_pass(ext::value& values)
{
    auto ask_pass = new pro::dialogs::ask_pass(*zzz);
    ask_pass->message("authentication"_lang);
    ask_pass->values(values);
    ask_pass->exec(make_address(""),[this,values,Ext_Weak_This](auto&& account) mutable
    {
        Ext_Weak_Check;
        ext::value response{{"@",protocol::Message_FS},{"type",type_},{"method",ext::fs::Login}};

        if(account.empty()){
            response["method"] = ext::fs::Cancel;
        }else{
            response["method"] = ext::fs::Login;
        }
        response.merge(ext::value(values));
        response.merge(std::move(account));
        zzz->send(response);
    });
}

void filesystem::on_file(ext::value& values)
{
    if(values.extract("path") == path_){
        update_file(values);
    }
}

void filesystem::on_list(ext::value& values)
{
    hide_loading();
    update_path(path_ = values.text("path"));
    update_actions();
    update_protocol(protocol_.lower());
    update_files(values["files"]);
    update_statusbar();

    if(filter_enabled_){
        on_filter();
    }
}

void filesystem::on_rename(ext::value& values)
{
    auto path = values.text("path");

    if(ext::fs::remove_trailing_separator(path) == ext::fs::remove_trailing_separator(path_))
    {
        auto name_old = values.text("old_name");
        auto name_new = values.text("name");

        if(auto node = grid_->find_node(name_old);node){
            grid_->rename_file(node,name_new,false);
            erase_clipboard(path,node->value.type);
        }
    }
}

void filesystem::on_move(std::int64_t oid,ext::value& values)
{
    if(auto iter = pasting_.find(oid);iter != pasting_.end())
    {
        auto path = ext::fs::remove_trailing_separator(values.text("target"));

        if(path.parent_path() == ext::fs::remove_trailing_separator(path_)){
            update_file(iter->second.values);
        }
    }
    on_remove(values);
}

void filesystem::on_copy(std::int64_t oid,ext::value& values)
{
    if(auto iter = pasting_.find(oid);iter != pasting_.end()){

    }
}

void filesystem::on_remove(ext::value& values)
{
    auto path = ext::fs::remove_trailing_separator(values.text("path"));

    if(path.parent_path() == ext::fs::remove_trailing_separator(path_))
    {
        if(auto node = grid_->find_node(ext::text(path.filename().u8string())))
        {
            auto type = node->value.type;

            if(type == ext::fs::file_type::directory){
                directories_count_--;
            }else{
                files_count_--;
            }
            grid_->remove_file(node);
            erase_clipboard(path,type);
        }
    }
}

void filesystem::on_attribute(ext::value& values)
{

}

void filesystem::on_chmod(ext::value& values)
{

}

void filesystem::on_create_file(ext::value& values)
{
    auto path = ext::fs::remove_trailing_separator(values.text("path"));

    if(path.parent_path() == ext::fs::remove_trailing_separator(path_))
    {
        ext::value item({
            {"type",(uint8_t)ext::fs::file_type::regular},
            {"name",path.filename()},
            {"size",0},
            {"mtime",ext::format_datetime()},
            {"attr",""}
        });
        update_file(item);
    }
}

void filesystem::on_create_dir(ext::value& values)
{
    auto path = ext::fs::remove_trailing_separator(values.text("path"));

    if(path.parent_path() == ext::fs::remove_trailing_separator(path_))
    {
        ext::value item({
            {"type",(uint8_t)ext::fs::file_type::directory},
            {"name",path.filename()},
            {"size",""},
            {"mtime",ext::format_datetime()},
            {"attr",""}
        });
        update_file(item);
    }
}

void filesystem::on_upload(operation_t& operation,ext::value& values)
{
    ext::fs::path path(operation.path_remote);

    if(operation.state == protocol::State_FS_Done && ext::fs::remove_trailing_separator(ext::text(path.parent_path())) == ext::fs::remove_trailing_separator(path_))
    {
        auto current        = grid_->find_node(ext::text(path.filename().u8string()));
        bool directory_mode = values.uint32("mode") & protocol::Task_Mode_Directory;

        if(current){
            grid_->remove_file(current);
        }
        ext::value item({
            {"type",uint8_t(directory_mode ? ext::fs::file_type::directory : ext::fs::file_type::regular)},
            {"name",path.filename()},
            {"size",directory_mode ? "" : values.get("file_size")},
            {"mtime",ext::format_datetime()},
            {"attr",""}
        });
        update_file(item);
    }
}

void filesystem::on_download(operation_t& operation,ext::value& values)
{
    if(operation.state == protocol::State_FS_Done)
    {
        if(operation.method == ext::fs::Open){
            ext::ui::file_dialog::open_local_url(operation.path_local);
        }else if(operation.method == ext::fs::Edit){

        }
    }
}


///---------------------------
void filesystem::view_icon()
{

}

void filesystem::view_grid()
{

}


///---------------------------
void filesystem::show_loading()
{
    timer_loading_ = ext::ui::set_timeout([this]{
        loading_->show();
    },200ms);
}

void filesystem::hide_loading()
{
    loading_->hide();
    ext::ui::clear_timeout(timer_loading_);
}

void filesystem::clear_files()
{
    directories_count_ = 0;
    files_count_       = 0;
    grid_->clear_files();
}

void filesystem::erase_operation(decltype(operations_)::iterator& iter)
{
    if(history_.size() > 512){
        history_.pop_front();
    }
    if(iter->second.method == ext::fs::List || iter->second.method == ext::fs::Refresh){
        hide_loading();
    }
    if(auto iter2 = pasting_.find(iter->first);iter2 != pasting_.end()){
        pasting_.erase(iter2);
    }
    history_ += {iter->first,std::move(iter->second)};
    operations_.erase(iter);
}

void filesystem::erase_clipboard(const ext::text& path,ext::fs::file_type type)
{

}

bool filesystem::matches_filter(ext::fs::file_type file_type,ext::text_view text)
{
    for(auto& rule : filter_value_rule_regex_)
    {
        try{
            if(std::regex_match(text.begin(),text.end(),rule)){
                return true;
            }
        }catch(...){}
    }
    if(filter_value_type_ == 1){
        if(file_type == ext::fs::file_type::directory){
            return true;
        }
    }else if(filter_value_type_ == 2){
        if(file_type != ext::fs::file_type::directory){
            return true;
        }
    }
    return !filter_value_text_.empty() && text.find(filter_value_text_) == std::string::npos;
}


///---------------------------
void filesystem::update_actions()
{
    constexpr ext::text_view names_connected[] = {"create_directory","create_file","refresh","filter","super_cache","upload","upload_directory","attribute"};

    auto selected_files = grid_->selected_files();
    auto selected_file  = 0;
    auto selected_dir   = 0;

    for(auto& file : selected_files)
    {
        if((uint16_t)file->value.type == (int)ext::fs::file_type::directory){
            selected_dir++;
        }else{
            selected_file++;
        }
    }
    for(auto name : {"edit"}){
        //ui("#act_"_text + name)->object.enable(selected_file != 0);
    }
    for(auto name : {"open_new_tab"}){
        ui("#act_"_text + name)->object.enable(selected_dir != 0);
    }
    for(auto name : {"open","rename","move","delete","download"}){
        ui("#act_"_text + name)->object.enable(grid_->has_selection());
    }
    for(auto name : names_connected){
        ui("#act_"_text + name)->object.enable(!path_.empty());
    }
    for(auto name : {"cut"}){
        ui("#act_"_text + name)->object.enable(grid_->has_selection());
    }
    ui("#act_paste")->object.enable(!clipboard_empty());
    ui("#act_go_previous")->object.enable(!addresses_->is_first());
    ui("#act_go_next")->object.enable(!addresses_->is_last());
    ui("#act_go_up")->object.enable(!addresses_->is_root());
}

void filesystem::update_protocol(ext::text_view protocol)
{
    if(protocol == "sftp"){
        protocol = "ssh";
    }
    protocols_->value(protocol);
}

void filesystem::update_statusbar()
{
    ext::text text;
    text += "directories"_lang + ": "_text + std::to_string(directories_count_) + " ";
    text += "files"_lang + ": "_text + std::to_string(files_count_);

    statusbar_->message(text);
}

void filesystem::update_path(const ext::text& path)
{
    if(!path.empty()){
        update_title(path);
        addresses_->value(make_address(path),false);
        addresses_->append(addresses_->value());
    }

}

void filesystem::update_title(ext::text_view title)
{
    if(auto idx = tabs_->indexOf(widget_);idx != -1)
    {
        auto path = ext::fs::remove_trailing_separator(title);

        if(auto name = path.filename();!name.empty()){
            tabs_->title(idx,ext::text(name.u8string()));
        }else{
            tabs_->title(idx,title);
        }
    }
}

void filesystem::update_files(ext::value& files)
{
    ext::text temp;

    for(auto& value : *files.cast_array())
    {
        auto node = update_file(value);

        if(cuts_.empty() || path_.empty()){
            continue;
        }
        temp = path_;
        temp.add_path(node->name);

        if(ext::fs::is_directory(node->value.type)){
            temp += '/';
        }
        if(cuts_.contains(temp)){
            grid_->cut(true,node);
        }
    }
}

auto filesystem::update_file(ext::value& file) -> ext::ui::filesystem::node_type*
{
    auto type = (ext::fs::file_type)file.int32("type");
    auto node = grid_->add_file(file,file.text_view("name"),{},type);
    auto item = grid_->sibling(node->value.item,1);

    switch(item->setData((int32_t)type);type)
    {
    case ext::fs::file_type::directory:
        grid_->sibling(node->value.item,"size")->text("");
        item->text("directory"_lang);
        break;
    case ext::fs::file_type::regular:
        item->text("regular"_lang);
        break;
    case ext::fs::file_type::symlink:
        item->text("symlink"_lang);
        break;
    case ext::fs::file_type::block:
        item->text("block"_lang);
        break;
    case ext::fs::file_type::character:
        item->text("character"_lang);
        break;
    case ext::fs::file_type::fifo:
        item->text("fifo"_lang);
        break;
    case ext::fs::file_type::socket:
        item->text("socket"_lang);
        break;
    case ext::fs::file_type::unknown:
        item->text("unknown"_lang);
        break;
    }
    if(node->name.starts_with('.')){

    }
    if(type != ext::fs::file_type::directory){
        files_count_++;
    }else{
        directories_count_++;
    }
    return node;
}

auto filesystem::send_operation(std::uint16_t method,const ext::json::list_t& list,const ext::text& path_remote,const ext::text& path_local,const ext::value& parameter) -> int64_t
{
    ext::text    buffer;
    std::int64_t oid = ++oid_;
    ext::json::stringify(buffer,{
        {"@",protocol::Message_FS},
        {"type",type_},
        {"method",method},
        {"sid",sid_},
        {"oid",oid}
    },list);
    auto iter = operations_.emplace(oid,operation_t{method,protocol::State_FS_Starting,0,0,ext::timestamp(),path_remote,path_local,parameter});

    zzz.invoke_alert<alert_operation_add_type>(Alert_Operation_Add,hid_,sid_,oid,iter.first->second);
    zzz->send(buffer);

    return oid;
}


///---------------------------
bool filesystem::clipboard_empty()
{
    return /*!ext::ui::clipboard::has_urls() && */cuts_.empty() && copies_.empty();
}


///---------------------------
ext::text filesystem::make_address(const ext::text& path)
{
    return protocol_ + "://" + host_ + ":" + std::to_string(port_) + path;
}

ext::text filesystem::make_path(ext::text_view name,bool trailing_separator)
{
    auto path = path_;

    if(!path.ends_with('/')){
        path += '/';
    }
    path += name;

    if(trailing_separator){
        path += "/";
    }
    return path;
}


///---------------------------
void filesystem::refresh()
{
    clear_files();
    show_loading();
    send_operation(ext::fs::Refresh,{{"path",path_}},path_);
}

void filesystem::upload(bool directory)
{
    Ext_Return_If(sid_ == 0);
    std::vector<ext::text> paths;

    if(!directory){
        paths = ext::ui::file_dialog::open_files("upload"_lang,"","all_files"_lang + " (*.*)"_text);
    }else if(auto text = ext::ui::file_dialog::open_directory("upload"_lang);!text.empty()){
        paths.emplace_back(text);
    }
    for(auto& text : paths){
        upload(text);
    }
}

void filesystem::upload(ext::text_view text)
{
    Ext_Return_If(sid_ == 0);

    ext::fs::path path(ext::fs::remove_trailing_separator(text));
    ext::text     file_name   = path.filename();
    ext::text     path_remote = make_path(file_name,false);
    ext::text     save_path   = path.parent_path();
    std::uint16_t file_type   = (uint16_t)ext::fs::status(path).type();

    send_operation(ext::fs::Upload,{{"file_type",file_type},{"path",path_remote},Ext_Pairs((save_path)(file_name))},path_remote,path);
}

void filesystem::download()
{
    Ext_Return_If(sid_ == 0);
    using file_dialog = ext::ui::file_dialog;

    auto files = grid_->selected_files();
    auto send  = [&](auto file_type,auto name,auto save_path,auto file_name)
    {
        ext::text path_remote = make_path(name,false);
        ext::text path_local  = save_path.path(file_name);

        send_operation(ext::fs::Download,{{"file_type",file_type},{"path",path_remote},Ext_Pairs((save_path)(file_name))},path_remote,path_local);
    };
    if(files.size() == 1)
    {
        auto& name = files[0]->name;
        auto  type = (uint8_t)files[0]->value.type;

        if(auto text = file_dialog::save_file("save_as"_lang,name);!text.empty()){
            auto local_path = ext::fs::path(text);
            send(type,name,ext::text(local_path.parent_path()),ext::text(local_path.filename()));
        }
    }else if(auto text = file_dialog::open_directory("save_path"_lang);!text.empty()){
        for(auto node : files){
            send((uint8_t)node->value.type,node->name,text,node->name);
        }
    }
}

void filesystem::remove()
{
    auto selected = grid_->selected_files();
    auto result   = ext::value(0);

    if(selected.empty() || !(result = zzz->messages_nfs()->alert("#delete_file")->call()).is_number() || result == 0){
        return;
    }
    for(auto node : grid_->selected_files())
    {
        if(node->value.type == ext::fs::file_type::directory){
            auto path_remote = make_path(node->name,true);
            send_operation(ext::fs::Remove_All,{{"path",path_remote}},path_remote);
        }else{
            auto path_remote = make_path(node->name,false);
            send_operation(ext::fs::Remove,{{"path",path_remote}},path_remote);
        }
    }
}

void filesystem::create_directory()
{
    Ext_Return_If(sid_ == 0);
    auto sample = std::make_unique<pro::dialog_sample<pro::file_browser::global>>(zzz,"ui/file_browser/create_directory.sml");

    sample->ui.on_click("#ok",[&](auto)
    {
        auto name = sample->ui.query_value("#name").text();

        if(!ext::fs::filename_valid(name)){
            ext::ui::alert("error","error"_lang,"invalid_name"_lang).exec();
        }else{
            ext::text path_remote = make_path(name,false);
            send_operation(ext::fs::Create_Dir,{{"path",path_remote}},path_remote);
            sample->dialog()->close();
        }
    });
    sample->dialog()->exec();
}

void filesystem::create_file()
{
    Ext_Return_If(sid_ == 0);
    auto sample = std::make_unique<pro::dialog_sample<pro::file_browser::global>>(zzz,"ui/file_browser/create_file.sml");

    sample->ui.on_click("#ok",[&](auto)
    {
        auto name = sample->ui.query_value("#name").text();

        if(!ext::fs::filename_valid(name)){
            ext::ui::alert("error","error"_lang,"invalid_name"_lang).exec();
        }else{
            ext::text path_remote = make_path(name,false);
            send_operation(ext::fs::Create_File,{{"path",path_remote}},path_remote);
            sample->dialog()->close();
        }
    });
    sample->dialog()->exec();
}

void filesystem::open(std::uint16_t operation)
{
    Ext_Return_If(sid_ == 0);
    for(auto node : grid_->selected_files())
    {
        auto file_type = node->value("type").int32();

        if(file_type == (int)ext::fs::file_type::directory){
            addresses_->value(make_address(make_path(node->name,true)));
            continue;
        }
        auto path_remote = make_path(node->name,false);
        auto save_path   = zzz->random_temp_directory();
        auto file_name   = node->name;

        send_operation(operation,
            {{"file_type",file_type},{"path",path_remote},{"save_path",save_path.u8string()},{"file_name",file_name}},
            path_remote,save_path / file_name
        );
    }
}

void filesystem::open_new_tab()
{
    Ext_Return_If(sid_ == 0);
    for(auto node : grid_->selected_files())
    {
        if(node->value("type").uint8() == (int)ext::fs::file_type::directory){
            zzz->send({{"@",protocol::Message_FS},{"type",type_},{"id",hid_},{"path",make_path(node->name,true)}});
        }
    }
}

void filesystem::rename()
{
    Ext_Return_If(sid_ == 0);
    for(auto node : grid_->selected_files())
    {
        auto input    = zzz->messages()->input("#rename_task");
        auto old_name = node->name;
        auto folder   = false;

        if(node->value("type").uint8() == (int)ext::fs::file_type::directory){
            folder = true;
        }
        if(input->exec(node->name) != 0){
            auto new_name = input->value();
            send_operation(ext::fs::Rename,{{"path",path_},{"old_name",old_name},{"name",new_name},{"folder",folder}},path_.path(old_name),{},new_name);
        }
    }
}

void filesystem::move()
{
    for(auto node : grid_->selected_files())
    {
        auto result = ext::text();
        auto path   = make_path(node->name,node->value.type == ext::fs::file_type::directory);
        auto input  = zzz->messages_nfs()->input("#move_file");

        if(input->exec(path) == 0 || (result = input->value().text()).empty() || result == path){
            return;
        }
        auto oid = move(path,result,node->value.type);
        pasting_.emplace(oid,copy_item_type{node->value.type,node->value.values});
    }
}

auto filesystem::move(const ext::text& from,const ext::text& to,ext::fs::file_type type) -> int64_t
{
    Ext_Return_If(sid_ == 0 || from == to,0);

    return send_operation(ext::fs::Move,{{"path",from},{"target",to},{"file_type",(uint8_t)type}},from,{},to);
}

auto filesystem::copy(const ext::text& from,const ext::text& to,ext::fs::file_type type) -> int64_t
{
    Ext_Return_If(sid_ == 0 || from == to,0);

    return send_operation(ext::fs::Copy,{{"path",from},{"target",to},{"folder",type == ext::fs::file_type::directory}},from,{},to);
}

void filesystem::copy_path(bool cut)
{
    if(!cuts_.empty()){
        grid_->each([&](auto node){
            grid_->cut(false,node);
            return false;
        },true);
    }
    cuts_.clear();
    copies_.clear();

    for(auto node : grid_->selected_files())
    {
        auto type = (ext::fs::file_type)node->value("type").uint8();
        auto path = make_path(node->name,type == ext::fs::file_type::directory);

        if(cut){
            grid_->cut(true,node);
            cuts_.emplace(path,copy_item_type{type,node->value.values});
        }else{
            copies_.emplace(path,copy_item_type{type,node->value.values});
        }
    }
}

void filesystem::paste()
{
    for(auto& iter : cuts_){
        auto oid = move(iter.first,path_.path(ext::parser::split_path(iter.first)),iter.second.file_type);
        pasting_.emplace(oid,iter.second);
    }
    for(auto& iter : copies_){
        auto oid = copy(iter.first,path_.path(ext::parser::split_path(iter.first)),iter.second.file_type);
        pasting_.emplace(oid,iter.second);
    }
    cuts_.clear();
}

void filesystem::attribute()
{

}

void filesystem::search()
{

}

void filesystem::super_cache()
{
    (new pro::file_browser::super_cache(zzz))->exec();
}

void filesystem::clone()
{
    (new pro::file_browser::clone(zzz))->exec();
}

void filesystem::list(ext::text_view path)
{
    clear_files();
    show_loading();
    send_operation(ext::fs::List,{{"path",path}},path);
}


}