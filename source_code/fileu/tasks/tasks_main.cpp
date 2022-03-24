#include "tasks_main.h"

namespace pro::tasks
{

main::main(pro::global& global,ext::ui::model& instance) :
    zzz(global),
    ui(instance),
    details_(zzz)
{

}

main::~main()
{

}


///---------------------------
void main::convert_nav_states(ext::text_view text,std::vector<int32_t>& states)
{
    if(text == "delay"){
        states = {protocol::State_Download_Later};
    }else if(text == "downloading"){
        states = {protocol::State_Downloading_Metadata,protocol::State_Downloading,protocol::State_Starting};
    }else if(text == "uploading"){
        states = {protocol::State_Uploading};
    }else if(text == "seeding"){
        states = {protocol::State_Seeding,protocol::State_Uploading};
    }else if(text == "stopped"){
        states = {protocol::State_Stopped};
    }else if(text == "completed"){
        states = {protocol::State_Completed};
    }else if(text == "failed"){
        states = {protocol::State_Error};
    }else if(text == "queuing"){
        states = {protocol::State_Queuing};
    }else{
        states.clear();
    }
}

void main::filter_tasks()
{
    for(auto& iter : all_tasks_){
        tasks_->visible(iter.second.node,matches_filter(iter.second));
    }
}

bool main::matches_filter(task_t& task)
{
    auto catalog = task.node->value("catalog").text_view();

    if(!selected_states_.empty() && std::find(selected_states_.begin(),selected_states_.end(),task.state) == selected_states_.end()){
        return false;
    }
    if(selected_catalogs_.empty()){
        return true;
    }
    for(auto item : selected_catalogs_)
    {
        if(item == nav_catalogs_->item(0) || catalog == item->text()){
            return true;
        }
    }
    return false;
}

void main::recount_text2()
{
    static std::vector<int32_t> temp_states;

    std::uint32_t count_states[protocol::State_Size] = {0};

    for(auto& iter : all_tasks_){
        count_states[iter.second.state]++;
    }
    nav_status_->each([&](auto i,auto item)
    {
        auto text   = nav_status_->item_data(item).text();
        auto number = std::uint32_t(0);

        if(text == "all"){
            number = all_tasks_.size();
        }else{
            convert_nav_states(text,temp_states);

            for(auto state : temp_states){
                number += count_states[state];
            }
        }
        item->text2(number == 0 ? nullptr : ext::value(number));
        return false;
    });
    need_recount_text2_ = false;
}


///---------------------------
void main::init_actions()
{
    /*
    #include <ShlObj.h>
    OPENASINFO info = {0};
    info.pcszFile = L"C:\\Users\\xx\\Desktop\\test.png";
    info.pcszClass = NULL;
    info.oaifInFlags = OAIF_ALLOW_REGISTRATION | OAIF_EXEC;

    SHOpenWithDialog(NULL, &info);
    */
    ui.on_action_id("act_task_add",[this](auto){
        (new pro::tasks::add_task(zzz,false,"ui/tasks/add_task.sml"))->exec();
    });
    ui.on_action_id("act_task_add_stream",[this](auto){
        (new pro::tasks::add_task(zzz,true,"ui/tasks/add_stream.sml"))->exec();
    });
    ui.on_action_id("act_task_start",std::bind(&main::start_selected_tasks,this));
    ui.on_action_id("act_task_start_all",std::bind(&main::start_all_tasks,this));
    ui.on_action_id("act_task_stop",std::bind(&main::stop_selected_tasks,this));
    ui.on_action_id("act_task_stop_all",std::bind(&main::stop_all_tasks,this));
    ui.on_action_id("act_task_delete",std::bind(&main::delete_selected_tasks,this));
    ui.on_action_id("act_task_delete_all",std::bind(&main::delete_all_tasks,this));
    ui.on_action_id("act_task_rename",std::bind(&main::rename_selected_tasks,this));
    ui.on_action_id("act_task_move",std::bind(&main::move_selected_tasks,this));
    ui.on_action_id("act_task_open_file",std::bind(&main::open_selected_tasks_file,this));
    ui.on_action_id("act_task_open_with",std::bind(&main::open_selected_tasks_with,this));
    ui.on_action_id("act_task_open_directory",std::bind(&main::open_selected_tasks_directories,this));
    ui.on_action_id("act_task_redownload",std::bind(&main::redownload_selected_tasks,this));
    ui.on_action_id("act_task_refresh_address",std::bind(&main::refresh_selected_tasks_address,this));
    ui.on_action_id("act_task_edit",std::bind(&main::edit_selected_tasks,this));
    ui.on_action_id("act_task_copy_name",std::bind(&main::copy_selected_tasks_names,this));
    ui.on_action_id("act_task_copy_address",std::bind(&main::copy_selected_tasks_addresses,this));
    ui.on_action_id("act_task_copy_hash",std::bind(&main::copy_selected_tasks_hashes,this));
    ui.on_action_id("act_task_export_torrent",std::bind(&main::export_selected_tasks_torrent,this));
}


///---------------------------
void main::init_nav()
{
    nav_status_ = ui.cast_id<ext::ui::list*>("tasks_nav_list");
    nav_status_->on_current_item_change([this](auto item,auto prev)
    {
        selected_state_ = nav_status_->current_data().text();
        convert_nav_states(selected_state_,selected_states_);
        filter_tasks();
    });
}

void main::init_catalogs()
{
    nav_catalogs_ = ui.cast_id<ext::ui::list*>("tasks_nav_catalogs");
    nav_catalogs_->on_selection_change([this]{
        selected_catalogs_ = nav_catalogs_->selected_items();
        filter_tasks();
    });
    nav_catalogs_->on_context_menu([this](auto){
        ext::try_new<pro::catalogs::main>(catalogs_,zzz,nav_catalogs_)->show_context_menu(nav_catalogs_->current_row());
    });
}

void main::init_filter()
{
    auto filter = ui.cast_id<ext::ui::combobox*>("tasks_filter");

    filter->on_text_change([this](auto text){
        tasks_->filter(0,ext::ui::text(text));
    });
}

void main::init_tasks()
{
    details_.init_details(ui.cast_id<ext::ui::splitter*>("tasks_splitter"),ui.cast_id<ext::ui::widget*>("tasks_details"));

    tasks_ = ui.cast_id<ext::ui::filesystem*>("tasks_list");
    tasks_->icons(&zzz.icons_mime);
    tasks_->on_click([this](auto index)
    {
        if(auto node = tasks_->selected_file()){
            show_detail(node->value("id").int64());
        }
    });
    tasks_->on_key_press([this](auto e)
    {
        if(e->matches(QKeySequence::Copy)){
            copy_selected_tasks_names();
            return true;
        }
        return false;
    });
    tasks_->on_checked([this](auto node)
    {
        auto id   = node->value("id").int64();
        auto iter = all_tasks_.find(id);

        if(iter != all_tasks_.end() && node->value.type != ext::fs::file_type::directory && node->value.checked != 1)
        {
            zzz.send({
                {"@",protocol::Message_Task_Files_Enable},
                {"type",iter->second.type},
                {"id",id},
                {"idx",node->value("idx").int32()},
                {"enable",node->value.checked == 2}
            });
        }
    });
    tasks_->on_insert([this](auto node,auto auto_created)
    {
        if(auto_created){
            node->value.type                = ext::fs::file_type::directory;
            node->value.values["id"]        = node->parent->value("id");
            node->value.values["file_name"] = node->name;
        }
    });
    tasks_->on_selection_changed([this](auto,auto){
        on_selection_changed();
    });
    tasks_->on_double_click([this](auto index)
    {
        Ext_Return_If(!tasks_->has_selection());

        if(auto node = tasks_->selected_file();!node->value.item->has_children()){
            open_task_file(node,true);
        }
    });
    tasks_->on_context_menu([this](auto)
    {
        if(tasks_->has_selection()){
            on_context_menu();
        }
    });
}


///---------------------------
void main::query_status(int64_t id,uint16_t type,bool extended)
{
    zzz.send({
        {"@",protocol::Message_Task_Status},
        {"type",type},
        {"id",id},
        {"extended",extended}
    });
}

void main::query_progress(int64_t id,uint16_t type)
{
    zzz.send({{"@",protocol::Message_Task_Progress},{"type",type},{"id",id}});
}


///---------------------------
void main::add_task(uint16_t type,uint16_t state,int64_t id,ext::value& json,const ext::value& files,bool full_status)
{
    auto  node = tasks_->add_file(json,std::to_string(id),json.text_view("file_path"));
    auto& task = all_tasks_.emplace(id,task_t{type,state,full_status,node}).first->second;

    if(files.is_array() && !files.empty()){
        update_task_files(id,task,files);
        tasks_->type(ext::fs::file_type::directory,node);
    }
    if(state < protocol::State_Completed/* || type == protocol::Task_Torrent*/){
        active_tasks_.emplace(id,type);
    }
    on_task_state(json,id,task,state);
}

bool main::update_task(uint16_t state,int64_t id,ext::value& json,const ext::value& files,bool full_status)
{
    auto iter = all_tasks_.find(id);

    if(iter == all_tasks_.end()){
        return false;
    }
    if(!iter->second.full_status && full_status){
        iter->second.full_status = full_status;
    }
    if(json.text_view("file_name") != iter->second.node->value.item->text()){
        iter->second.node->value.type = ext::fs::file_type::none;
    }
    tasks_->update_file(json,std::to_string(id),iter->second.node);

    if(files.is_array() && !files.empty()){
        update_task_files(id,iter->second,files);
        tasks_->type(ext::fs::file_type::directory,iter->second.node);
    }else{
        tasks_->type(ext::fs::file_type::regular,iter->second.node);
    }
    if(iter->second.state != state){
        auto current_state = iter->second.state;
        iter->second.state = state;
        on_task_state(json,id,iter->second,current_state);
    }
    return true;
}

void main::update_task_files(int64_t id,task_t& task,const ext::value& items)
{
    for(auto& values : *items.cast_array())
    {
        auto path     = values.text("file_path");
        auto priority = values.uint8("priority");

        values["id"] = id;
        path = path.empty() ? std::to_string(id) : (std::to_string(id) + "/" + path);

        if(auto node = tasks_->update_file(std::move(values),values.text("file_name"),path,true)){
            tasks_->checked(priority != 0 ? 2 : 0,node);
        }
    }
    tasks_->recurse<task_directory_t>([this](node_type* node,auto& dir)
    {
        Ext_Return_If(!node->parent);
        dir.checked[node->value.checked]++;

        if(node->value.checked != 0){
            dir.downloaded += node->value("downloaded").int64();
            dir.file_size  += node->value("file_size").int64();
        }
    },[this](node_type* node,auto& dir)
    {
        Ext_Return_If(!node->parent);
        node->value("downloaded",dir.downloaded);
        node->value("file_size",dir.file_size);

        tasks_->checked(tasks_->parent_check_state(dir.checked),node);
        tasks_->siblings(node->value.item,node->value.values);
    });
}

void main::update_tasks_catalog(ext::text_view name,ext::text_view new_name)
{
    for(auto& iter : all_tasks_)
    {
        auto  node    = iter.second.node;
        auto& catalog = node->value.values["catalog"];

        if(catalog == name){
            tasks_->sibling(node->value.item,"catalog",catalog = new_name);
        }
    }
}

bool main::erase_active_task(int64_t id,task_t& task)
{
    active_tasks_.erase(id);
    return true;
}

bool main::erase_task(int64_t id)
{
    if(auto iter = all_tasks_.find(id);iter != all_tasks_.end())
    {
        tasks_->remove_file(iter->second.node);
        erase_active_task(id,iter->second);
        all_tasks_.erase(iter);
        need_recount_text2_ = true;
        return true;
    }
    return false;
}


///---------------------------
void main::start_task(int64_t id)
{
    if(auto iter = all_tasks_.find(id);iter != all_tasks_.end()){
        zzz.send({{"@",protocol::Message_Task_Resume},{"type",iter->second.type},{"id",id}});
    }
}

void main::start_all_tasks()
{
    for(auto& iter : all_tasks_)
    {
        if(tasks_->visible(iter.second.node)){
            zzz.send({{"@",protocol::Message_Task_Resume},{"type",iter.second.type},{"id",iter.first}});
        }
    }
}

void main::start_selected_tasks()
{
    for(auto node : tasks_->selected_files()){
        start_task(node->value("id").int64());
    }
}

void main::stop_task(int64_t id)
{
    if(auto iter = all_tasks_.find(id);iter != all_tasks_.end()){
        zzz.send({{"@",protocol::Message_Task_Stop},{"type",iter->second.type},{"id",id}});
    }
}

void main::stop_all_tasks()
{
    for(auto& iter : all_tasks_)
    {
        if(tasks_->visible(iter.second.node) && iter.second.state != protocol::State_Stopped){
            zzz.send({{"@",protocol::Message_Task_Stop},{"type",iter.second.type},{"id",iter.first}});
        }
    }
}

void main::stop_selected_tasks()
{
    for(auto node : tasks_->selected_files()){
        stop_task(node->value("id").int64());
    }
}

void main::delete_task(int64_t id,bool delete_file)
{
    if(auto iter = all_tasks_.find(id);iter != all_tasks_.end()){
        zzz.send({{"@",protocol::Message_Task_Remove},{"type",iter->second.type},{"id",id},{"delete_file",delete_file}});
    }
}

void main::delete_all_tasks()
{
    std::vector<int64_t> ids;

    for(auto& iter : all_tasks_)
    {
        if(tasks_->visible(iter.second.node)){
            ids.emplace_back(iter.first);
        }
    }
    if(ids.empty()){
        return;
    }
    auto ret = zzz.messages()->alert("#delete_all_tasks")->call();

    if(!ret.is_number() || ret == 0){
        return;
    }
    if(auto input = zzz.messages()->input("#delete_all_tasks_confirm");input->exec() != 0 && input->value() == "123")
    {
        for(auto id : ids){
            delete_task(id,ret == 2);
        }
    }
}

void main::delete_selected_tasks()
{
    auto selected = tasks_->selected_files();
    auto result   = ext::value(0);

    if(selected.empty() || !(result = zzz.messages()->alert("#delete_task")->call()).is_number() || result == 0){
        return;
    }
    for(auto node : selected){
        delete_task(node->value("id").int64(),result == 2);
    }
}

bool main::rename_task(std::int64_t id,const ext::value& idx,std::string_view current_name,std::string& new_name)
{
    if(auto iter = all_tasks_.find(id);iter != all_tasks_.end())
    {
        auto input = zzz.messages()->input("#rename_task");

        if(input->exec(current_name) == 0){
            return false;
        }
        zzz.send({{"@",protocol::Message_Task_Rename},{"type",iter->second.type},{"id",id},{"idx",idx},{"name",new_name = input->value().text()}});
        query_status(id,iter->second.type);
        return true;
    }
    return false;
}

void main::rename_selected_tasks()
{
    Ext_Return_If(!tasks_->has_selection());

    auto node     = tasks_->selected_file();
    auto idx      = ext::value(-1);
    auto name     = node->value("file_name").string();
    auto new_name = ext::text();

    if(auto val = node->value("idx");val.is_number()){
        idx = val.int32();
    }else if(node->value.type == ext::fs::file_type::directory && node->parent){
        if((idx = tasks_->path(node->value.item->index(),true,'/')).empty()){
            return;
        }
    }
    rename_task(node->value("id").int64(),idx,name,new_name);
}

void main::redownload_task(int64_t id)
{
    find_task(id,[this](auto id,auto& task){
        zzz.send({{"@",protocol::Message_Task_Redownload},{"type",task.type},{"id",id}});
        active_tasks_.emplace(id,task.type);
    });
}

void main::redownload_selected_tasks()
{
    for(auto node : tasks_->selected_files()){
        redownload_task(node->value("id").int64());
    }
}

void main::refresh_task_address(int64_t id)
{
    if(auto iter = all_tasks_.find(id);iter != all_tasks_.end())
    {
        auto node     = iter->second.node;
        auto page_url = node->value("page_url").text_view();
        auto resid    = node->value("redis").text_view();

        if(!page_url.empty() && !resid.empty()){
            refresh_task_address(id,iter->second.type,page_url,resid);
        }else{
            zzz.send({{"@",protocol::Message_Task_Config},{"#",protocol::Message_Task_Refresh_Address},{"type",iter->second.type},{"id",id}});
        }
    }
}

void main::refresh_task_address(int64_t id,uint16_t type,ext::text_view page_url,ext::text_view resid)
{
    if(zzz.settings["no_refresh_address_dialog"] == true){
        ext::ui::file_dialog::open_url(tasks::refresh_address::address(zzz,id,type,page_url,resid));
    }else{
        (new pro::tasks::refresh_address(zzz))->exec(id,type,page_url,resid);
    }
}

void main::refresh_selected_tasks_address()
{
    for(auto node : tasks_->selected_files()){
        refresh_task_address(node->value("id").int64());
    }
}

void main::edit_task(int64_t id)
{
    find_task(id,[this](auto id,auto& task){
        zzz.send({{"@",protocol::Message_Task_Config},{"#",protocol::Message_Task_Edit},{"type",task.type},{"id",id}});
    });
}

void main::edit_selected_tasks()
{
    for(auto node : tasks_->selected_files()){
        edit_task(node->value("id").int64());
    }
}

void main::open_task_file(ext::ui::filesystem::node_type* node,bool completed_only)
{
    if(auto iter = all_tasks_.find(node->value("id").int64());iter != all_tasks_.end())
    {
        auto save_path = iter->second.node->value("save_path");

        if(completed_only && iter->second.node == node && iter->second.state != protocol::State_Completed && iter->second.state != protocol::State_Seeding){
            return;
        }
        if(!save_path.empty()){
            tasks_->open_file(node->value.item,save_path.text());
        }
    }
}

void main::open_selected_tasks_file()
{
    for(auto node : tasks_->selected_files()){
        open_task_file(node,false);
    }
}

void main::open_selected_tasks_with()
{

}

void main::open_selected_tasks_directories()
{
    for(auto node : tasks_->selected_files())
    {
        auto iter = all_tasks_.find(node->value("id").int64());

        if(iter == all_tasks_.end()){
            continue;
        }
        if(auto save_path = iter->second.node->value("save_path");!save_path.empty()){
            tasks_->reveal_file(node->value.item,save_path.text());
        }
    }
}

void main::move_selected_tasks()
{
    auto path = ext::ui::file_dialog::open_directory(ext::ui::lang("move_to"));

    if(path.empty()){
        return;
    }
    for(auto node : tasks_->selected_files()){
        move_task(node->value("id").int64(),path);
    }
}

bool main::move_task(int64_t id,std::string_view path)
{
    if(auto iter = all_tasks_.find(id);iter != all_tasks_.end()){
        zzz.send({{"@",protocol::Message_Task_Move},{"type",iter->second.type},{"id",id},{"path",path}});
        return true;
    }
    return false;
}

void main::copy_selected_tasks_addresses()
{
    ext::text text;

    for(auto node : tasks_->selected_files())
    {
        find_task(node->value("id").int64(),[&](auto id,auto task)
        {
            ext::text_view uri;

            if(task.type == protocol::Task_Torrent){
                uri = node->value("magnet").text();
            }else{
                uri = node->value("uri").text();
            }
            text.append_line(uri);
        });
    }
    ext::ui::clipboard::text(text);
}

void main::copy_selected_tasks_names()
{
    ext::text text;

    for(auto node : tasks_->selected_files()){
        text.append_line(node->value("file_name").text_view());
    }
    ext::ui::clipboard::text(text);
}

void main::copy_selected_tasks_hashes()
{
    ext::text text;

    for(auto node : tasks_->selected_files())
    {
        find_task(node->value("id").int64(),[&](auto id,auto task){
            text.append_line(node->value("hash").text_view());
        });
    }
    ext::ui::clipboard::text(text);
}

void main::export_selected_tasks_torrent()
{
    auto files = tasks_->selected_files();

    if(files.size() == 1)
    {
        find_task(files[0]->value("id").int64(),[&](auto id,auto task)
        {
            auto path = ext::ui::file_dialog::save_file(ext::ui::lang("save_as"),files[0]->value("file_name").text() + ".torrent");

            if(!path.empty()){
                zzz.send({{"@",protocol::Message_Task_Export_Torrent},{"type",task.type},{"id",id},{"path",path}});
            }
        });
    }else if(files.size() > 1){
        auto path = ext::ui::file_dialog::open_directory(ext::ui::lang("save_as"));

        if(path.empty()){
            return;
        }
        for(auto node : files)
        {
            find_task(files[0]->value("id").int64(),[&](auto id,auto task){
                auto name = files[0]->value("file_name").text() + ".torrent";
                zzz.send({{"@",protocol::Message_Task_Export_Torrent},{"type",task.type},{"id",id},{"path",(ext::fs::path(path) / name).u8string()}});
            });
        }
    }
}

void main::show_detail(int64_t id)
{
    find_task(id,[&](auto id,auto& task)
    {
        bool try_status = false;

        if(!task.full_status && task.state >= protocol::State_Stopped){
            try_status = true;
        }
        details_.display(task.type,id,task.node->value.values);
        details_.query_detail(try_status);
    });
}

void main::show_completed_dialog(int64_t id,ext::value& values,const ext::text& error)
{
    if(zzz.settings["sound_effects"] == true){
        zzz.sound.play(zzz.workspace / "sounds" / (error.empty() ? "transfer_completed.wav" : "transfer_error.wav"));
    }
    if(zzz.settings["no_completed_dialog"] == true){
        return;
    }
    if(auto mode = values.get("mode");mode.is_number())
    {
        if((mode.uint32() & protocol::Task_Mode_Internal) || (mode.uint32() & protocol::Task_Mode_Upgrade)){
            return;
        }
    }
    auto dialog = new tasks::download_completed(zzz,id,[this](auto id){

    });
    dialog->exec(values,error);
}


///---------------------------
void main::on_timer(ext::steady_time_point_t now)
{
    auto seconds  = now - timepoint_seconds_ >= 1s;
    auto interval = 100ms;

    if(active_tasks_.size() > 20){
        interval = 200ms;
    }else if(active_tasks_.size() > 40){
        interval = 500ms;
    }
    if(seconds)
    {
        for(auto& iter : confirming_tasks_){
            if(iter.second.first == protocol::Task_Torrent){
                query_status(iter.first,iter.second.first);
            }
        }
        for(auto& iter : active_tasks_){
            query_status(iter.first,iter.second.type,!iter.second.extend_status_loaded);
        }
        details_.query_detail();

        if(need_recount_text2_){
            recount_text2();
        }
        timepoint_seconds_  = now;
        timepoint_interval_ = now;
    }else if(now - timepoint_interval_ >= interval){
        for(auto& iter : active_tasks_){
            if(iter.second.type != protocol::Task_Torrent){
                query_progress(iter.first,iter.second.type);
            }
        }
        timepoint_interval_ = now;
    }
}

void main::on_catalog_add(ext::value& json)
{
    auto name    = json.text("name");
    auto catalog = new ext::ui::list_item("icons/24/catalog.svg",name);

    nav_catalogs_->append(catalog);
    zzz.catalogs.emplace(name,std::move(json));
}

void main::on_catalog_update(ext::value& json)
{
    auto name     = json.extract("name").text();
    auto old_name = json.extract("old_name").text();
    auto path     = json.text("path");

    if(name.empty() || old_name.empty()){
        return;
    }
    if(name == old_name){
        zzz.catalogs[name] = json;
        return;
    }
    zzz.catalogs.erase(old_name);
    zzz.catalogs[name] = json;

    nav_catalogs_->each([&](auto i,auto item)
    {
        if(item != nav_catalogs_->item(0) && item->text() == old_name){
            item->text(name);
            return true;
        }
        return false;
    });
    update_tasks_catalog(old_name,name);
}

void main::on_catalog_remove(ext::value& json)
{
    auto name = json.text("name");

    nav_catalogs_->each([&](auto i,auto item)
    {
        if(item != nav_catalogs_->item(0) && item->text() == name){
            nav_catalogs_->remove(i);
            zzz.catalogs.erase(name);
            return true;
        }
        return false;
    });
    if(auto new_name = json.get("new_name");new_name.is_string()){
        update_tasks_catalog(name,new_name.text_view());
    }
    nav_catalogs_->current_row(0);
}

void main::on_catalogs(ext::value& json)
{
    zzz.catalogs = json.get("items");

    for(auto i=nav_catalogs_->count() - 1;i>0;--i){
        nav_catalogs_->remove(i);
    }
    if(zzz.catalogs.is_map())
    {
        for(auto& iter : *zzz.catalogs.cast_map()){
            auto catalog = new ext::ui::list_item("icons/24/catalog.svg",iter.first.string());
            nav_catalogs_->append(catalog);
        }
    }
}


///------------------------------------
void main::on_http_confirming(ext::value& json,int64_t id,uint16_t type,uint16_t state)
{
    auto iter = confirming_tasks_.find(id);

    if(iter != confirming_tasks_.end()){
        return;
    }
    auto pointer = new pro::tasks::confirm_http(zzz,json,[this](auto id,bool confirmed){
        on_task_confirmed(id,confirmed);
    });
    pointer->exec(json,state);
    confirming_tasks_.emplace(id,std::make_pair(type,pointer));
}

void main::on_torrent_confirming(ext::value& json,int64_t id,uint16_t type,uint16_t state)
{
    auto iter = confirming_tasks_.find(id);

    if(iter != confirming_tasks_.end()){
        return ((pro::tasks::confirm_torrent*)iter->second.second)->update(json,state);
    }
    auto pointer = new pro::tasks::confirm_torrent(zzz,json,[this](auto id,bool confirmed){
        on_task_confirmed(id,confirmed);
    });
    pointer->exec(json,state);
    confirming_tasks_.emplace(id,std::make_pair(type,pointer));
}


///------------------------------------
void main::on_task_error(int64_t id,task_t& task,uint16_t old_state,const ext::text& error)
{
    if(old_state == protocol::State_Downloading || old_state == protocol::State_Downloading_Metadata || old_state == protocol::State_Starting){
        show_completed_dialog(id,task.node->value.values,error);
    }
    need_recount_text2_ = true;
    erase_active_task(id,task);
}

void main::on_task_completed(int64_t id,task_t& task,uint16_t old_state)
{
    if(old_state == protocol::State_Downloading){
        show_completed_dialog(id,task.node->value.values);
    }
    erase_active_task(id,task);
}

void main::on_task_state(ext::value& json,int64_t id,task_t& task,uint16_t old_state)
{
    auto item         = tasks_->sibling(task.node->value.item,"state");
    auto color        = ext::value();
    bool need_recount = true;

    tasks_->visible(task.node,matches_filter(task));

    if(task.state == protocol::State_Error){
        auto text = global::error_text(json.int32("error"));
        on_task_error(id,task,old_state,text);
        tasks_->row_color(item,"#ad1c1f");
        return item->text(text);
    }
    switch(task.state)
    {
    case protocol::State_Download_Later:
    case protocol::State_Queuing:
        color = "#025a75";
        break;
    case protocol::State_Starting:
    case protocol::State_Resuming:
    case protocol::State_Checking:
    case protocol::State_Stopping:
    case protocol::State_Removing:
    case protocol::State_Restarting:
    case protocol::State_Merging:
        color        = "#013d6a";
        need_recount = false;
        break;
    case protocol::State_Downloading_Metadata:
        color = "#146ab4";
        break;
    case protocol::State_Downloading:
        color = "#104e9f";
        break;
    case protocol::State_Uploading:
    case protocol::State_Seeding:
        color = "#057816";
        break;
    case protocol::State_Stopped:
        color = "#714a1c";
        erase_active_task(id,task);
        goto bottom;
    case protocol::State_Completed:
        color = "#1f1f1f";
        on_task_completed(id,task,old_state);
        goto bottom;
    }
    if(auto iter = active_tasks_.find(id);iter == active_tasks_.end()){
        active_tasks_.emplace(id,task.type);
    }
    bottom:
    item->text(ext::ui::lang(protocol::Task_States_Text[task.state]));
    tasks_->row_color(item,color);
    need_recount_text2_ = need_recount;
}

void main::on_task_confirmed(std::int64_t id,ext::boolean_t confirmed)
{
    if(auto iter = confirming_tasks_.find(id);iter != confirming_tasks_.end())
    {
        if(confirmed){
            query_status(id,iter->second.first,true);
        }
        confirming_tasks_.erase(iter);
        active_tasks_.emplace(id,iter->second.first);
    }
}

void main::on_task_confirming(ext::value& json,int64_t id,uint16_t type,uint16_t state)
{
    erase_task(id);

    switch(type)
    {
    case protocol::Task_HTTP:
        on_http_confirming(json,id,type,state);
        break;
    case protocol::Task_Stream:
        break;
    case protocol::Task_Torrent:
        on_torrent_confirming(json,id,type,state);
        break;
    default:
        break;
    }
}

void main::on_task_status(ext::value& json)
{
    auto id          = json.int64("id");
    auto type        = json.extract("type").uint16();
    auto state       = json.extract("state").uint16();
    auto extended    = json.extract("__extended__");
    auto full_status = json.extract("#");

    if(type >= protocol::Task_Types_Size){
        return ext::debug << "[tasks_main]main::on_task_status type error :" <<= type,void();
    }
    if(json.uint16("substate") == protocol::Substate_Confirming){
        return on_task_confirming(json,id,type,state);
    }
    if(auto files = json.extract("files");!update_task(state,id,json,files,full_status == true)){
        add_task(type,state,id,json,files,full_status == true);
    }
    if(details_.id_ == id && details_.expanded()){
        details_.update(type,json);
    }
    if(extended == true)
    {
        if(auto iter = active_tasks_.find(id);iter != active_tasks_.end()){
            iter->second.extend_status_loaded = true;
        }
    }
}

void main::on_task_progress(ext::value& json)
{
    find_task(json,[&](auto id,auto& task){
        tasks_->siblings(task.node->value.item,json);
    });
}

void main::on_task_detail(ext::value& json)
{
    find_task(json,[&](auto id,auto& task){
        details_.update(task.type,json);
    });
}

void main::on_task_config(ext::value& json)
{
    find_task(json,[&](auto id,auto& task)
    {
        for(auto& iter : *json.cast_map()){
            task.node->value.values[iter.first.string_view()] = iter.second;
        }
        tasks_->siblings(task.node->value.item,json);
    });
}

void main::on_task_renamed(ext::value& json)
{
    find_task(json,[&](auto id,auto& task)
    {
        if(auto node = tasks_->find_node(std::to_string(id) + "/" + json.text("old_path"))){
            auto file_name = json.text_view("file_name");
            node->value.values["file_name"] = file_name;
            tasks_->rename_file(node,file_name);
        }
    });
}

void main::on_task_removed(ext::value& json)
{
    erase_task(json.int64("id"));
}

void main::on_task_refresh_address(ext::value& json)
{
    auto type     = json.uint16("type");
    auto page_url = json.text_view("page_url");
    auto resid    = json.text_view("resid");

    if(!page_url.empty() && !resid.empty()){
        refresh_task_address(json.int64("id"),type,page_url,resid);
    }
}

void main::on_task_edit(ext::value& json)
{
    (new pro::tasks::edit_task(zzz))->exec(json);
}

void main::on_selection_changed()
{
    using masks = protocol::task_masks;

    constexpr std::pair<ext::text_view,std::uint64_t> actions[] = {
        {"start",masks::Mask_Task},
        {"stop",masks::Mask_Task},
        {"move",masks::Mask_Task},
        {"delete",masks::Mask_Task},
        {"delete_fully",masks::Mask_Task},
        {"redownload",masks::Mask_Task_HTTP | masks::Mask_Task_FTP | masks::Mask_Task_Stream},
        {"refresh_address",masks::Mask_Task_HTTP | masks::Mask_Task_Stream},
        {"edit",masks::Mask_Task},
        {"copy_address",masks::Mask_Task},
        {"copy_hash",masks::Mask_Task_Torrent},
        {"export_torrent",masks::Mask_Task_Torrent}
    };
    auto mask  = uint64_t(0);
    auto files = tasks_->selected_files();

    if(files.empty()){
        details_.hide();
    }else if(files.size() == 1){
        show_detail(files[0]->value("id").int64());
    }
    for(auto file : files)
    {
        if(file->value.item->parent()){
            mask |= masks::Mask_File;
        }else if(auto iter = all_tasks_.find(file->value("id").int64());iter != all_tasks_.end()){
            mask |= protocol::to_mask(iter->second.type);
        }
    }
    for(auto& item : actions)
    {
        if(auto action = ui.cast_id<ext::ui::action*>("act_task_" + std::string(item.first))){
            action->enable(mask == 0 || (mask & item.second));
        }
    }
}

void main::on_context_menu()
{
    auto set_catalog = ui.cast<ext::ui::menu*>("#task_set_catalog");

    for(auto action : set_catalog->actions()){
        action->deleteLater();
    }
    set_catalog->clear();

    for(auto& iter : *zzz.catalogs.cast_map())
    {
        auto action = new ext::ui::action;
        auto text   = iter.first.string();

        action->icon(ext::ui::icon("icons/16/directory.svg"));
        action->text(iter.first.string());
        action->on_trigger([this,text](auto)
        {
            std::unordered_set<int64_t> ids;

            for(auto node : tasks_->selected_files()){
                ids.emplace(node->value("id").int64());
            }
            for(auto id : ids)
            {
                if(auto iter = all_tasks_.find(id);iter != all_tasks_.end()){
                    zzz.send({{"@",protocol::Message_Task_Set_Catalog},{"type",iter->second.type},{"id",id},{"catalog",text}});
                }
            }
        });
        set_catalog->append(action);
    }
    tasks_->show_context_menu();
}


///---------------------------
void main::init()
{
    init_tasks();
    init_actions();
    init_nav();
    init_catalogs();
    init_filter();
}

void main::clear()
{
    active_tasks_.clear();
    all_tasks_.clear();
    tasks_->clear_files();

    for(auto iter : confirming_tasks_)
    {
        if(iter.second.first == protocol::Task_HTTP){
            ((pro::tasks::confirm_http*)iter.second.second)->destroy();
        }else if(iter.second.first == protocol::Task_Torrent){
            ((pro::tasks::confirm_torrent*)iter.second.second)->destroy();
        }
    }
    confirming_tasks_.clear();
}


}