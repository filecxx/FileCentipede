#include "tasks_details.h"

namespace pro::tasks
{

details::details(pro::global& global) : zzz(global)
{

}

details::~details()
{
    for(auto& item : details_){
        delete item.sample;
    }
}


///---------------------------
ext::text details::type_to_filename(uint16_t type)
{
    switch(type)
    {
    case protocol::Task_HTTP:
        return "details_http.sml";
    case protocol::Task_FTP:
        return "details_ftp.sml";
    case protocol::Task_Torrent:
        return "details_torrent.sml";
    case protocol::Task_Ed2k:
        return "details_ed2k.sml";
    case protocol::Task_Stream:
        return "details_stream.sml";
    }
    return "";
}


///---------------------------
void details::init_details(ext::ui::splitter* splitter,ext::ui::widget* detailbars)
{
    tasks_splitter_ = splitter;
    detailbars_     = detailbars;

    tasks_splitter_->on_move([this](auto){
        sizes_ = tasks_splitter_->sizes();
    });
}

void details::init_detailbar(ext::ui::detailbar* detailbar,std::uint16_t type)
{
    detailbar->on_change([this,detailbar](auto index)
    {
        if(index == -1){
            sizes_ = tasks_splitter_->sizes();
            minimize();
        }else{
            subset_ = detailbar->at(index)->subset;

            if(!sizes_.empty()){
                tasks_splitter_->setSizes(sizes_);
            }
            query_detail();
        }
        for(auto i=0;i<tasks_splitter_->count();++i){
            tasks_splitter_->handle(i)->setDisabled(index == -1);
        }
    });
    detailbars_->layout()->addWidget(detailbar);

    if(type == protocol::Task_Torrent){
        init_torrent_details();
    }
}

void details::init_torrent_tracker_actions(ext::ui::model& ui)
{
    auto table = ui.cast_id<ext::ui::table*>("tracker_list");

    ui.on_click("#add_tracker",[this,&ui](auto)
    {
        auto node   = ui("#dialog_add_tracker");
        auto values = ext::ui::form(node).values();

        values["@"]    = protocol::Message_Task_Tracker_Add;
        values["id"]   = id_;
        values["type"] = type_;

        zzz.send(values);
        ext::ui::methods::invoke(node->object,"close");
    });
    ui.on_action_id("act_edit_tracker",[this,table,&ui](auto)
    {
        if(auto url = table->current_text("url");!url.empty() && !(url.text_view().front() == '[' && url.text_view().back() == ']'))
        {
            ext::ui::input_dialog dialog;
            dialog.setMinimumWidth(500);

            if(dialog.exec(url.text()) == 0){
                return;
            }
            if(auto url_new = dialog.value();!url_new.empty()){
                zzz.send({{"@",protocol::Message_Task_Tracker_Edit},{"id",id_},{"type",type_},{"url",url.text()},{"url_new",url_new.text()}});
            }
        }
    });
    ui.on_action_id("act_remove_tracker",[this,table,&ui](auto){
        if(auto text = table->selected_rows_text("url");!text.empty()){
            zzz.send({{"@",protocol::Message_Task_Tracker_Remove},{"id",id_},{"type",type_},{"url",text}});
        }
    });
    ui.on_action_id("act_copy_tracker",[this,table,&ui](auto)
    {
        if(auto text = table->selected_rows_text("url");!text.empty()){
            ext::ui::clipboard::text(text);
        }
    });
    ui.on_action_id("act_force_reannounce",[this,table,&ui](auto){
        if(auto text = table->selected_rows_text("url");!text.empty()){
            zzz.send({{"@",protocol::Message_Task_Tracker_Force_Reannounce},{"id",id_},{"type",type_},{"url",text}});
        }
    });
    ui.on_action_id("act_force_reannounce_all",[this,table,&ui](auto){
        zzz.send({{"@",protocol::Message_Task_Tracker_Force_Reannounce},{"id",id_},{"type",type_}});
    });
}

void details::init_torrent_peers_actions(ext::ui::model& ui)
{
    auto table = ui.cast_id<ext::ui::table*>("peer_list");

    ui.on_click("#add_peer",[this,&ui](auto)
    {
        auto node   = ui("#dialog_add_peer");
        auto values = ext::ui::form(node).values();

        values["@"]    = protocol::Message_Task_Peer_Add;
        values["id"]   = id_;
        values["type"] = protocol::Task_Torrent;

        zzz.send(values);
        ext::ui::methods::invoke(node->object,"close");
    });
    ui.on_action_id("act_copy_peer_endpoint",[this,table,&ui](auto){
        if(auto text = table->selected_rows_text("address");!text.empty()){
            ext::ui::clipboard::text(text);
        }
    });
    ui.on_action_id("act_copy_peer_client",[this,table,&ui](auto){
        if(auto text = table->selected_rows_text("client");!text.empty()){
            ext::ui::clipboard::text(text);
        }
    });
    ui.on_action_id("act_disconnect_peer",[this,table,&ui](auto){
        if(auto text = table->selected_rows_text("address");!text.empty()){
            zzz.send({{"@",protocol::Message_Task_Peer_Operation},{"id",id_},{"type",type_},{"operation",protocol::Peer_Disconnect},{"endpoints",text}});
        }
    });
    ui.on_action_id("act_ban_peer",[this,table,&ui](auto){
        if(auto text = table->selected_rows_text("address");!text.empty()){
            zzz.send({{"@",protocol::Message_Task_Peer_Operation},{"id",id_},{"type",type_},{"operation",protocol::Peer_Ban_IP},{"endpoints",text}});
        }
    });
}

void details::init_torrent_web_seeds_actions(ext::ui::model& ui)
{
    auto table = ui.cast_id<ext::ui::table*>("web_seeds_list");

    ui.on_click("#add_web_seed",[this,&ui](auto)
    {
        auto node   = ui("#dialog_add_web_seed");
        auto values = ext::ui::form(node).values();

        values["@"]    = protocol::Message_Task_Web_Seed_Add;
        values["id"]   = id_;
        values["type"] = protocol::Task_Torrent;

        zzz.send(values);
        ext::ui::methods::invoke(node->object,"close");
    });
    ui.on_action_id("act_edit_web_seed",[this,table,&ui](auto)
    {
        ext::value url = table->current_text("url");

        if(!url.is_string() && !url.empty())
        {
            ext::ui::input_dialog dialog;
            dialog.setMinimumWidth(500);

            if(dialog.exec(url) == 0){
                return;
            }
            if(auto url_new = dialog.value();!url_new.empty()){
                zzz.send({{"@",protocol::Message_Task_Web_Seed_Edit},{"id",id_},{"type",type_},{"url",url.text()},{"url_new",url_new}});
            }
        }
    });
    ui.on_action_id("act_remove_web_seed",[this,table,&ui](auto)
    {
        if(auto text = table->selected_rows_text("url");!text.empty()){
            zzz.send({{"@",protocol::Message_Task_Web_Seed_Remove},{"id",id_},{"type",type_},{"url",text}});
        }
    });
    ui.on_action_id("act_copy_web_seed",[this,table,&ui](auto){
        if(auto text = table->selected_rows_text("url");!text.empty()){
            ext::ui::clipboard::text(text);
        }
    });
}

void details::init_torrent_details()
{
    auto& ui        = details_[protocol::Task_Torrent].sample->ui;
    auto  trackers  = ui.cast_id<ext::ui::table*>("tracker_list");
    auto  web_seeds = ui.cast_id<ext::ui::table*>("web_seeds_list");
    auto  peers     = ui.cast_id<ext::ui::table*>("peer_list");

    trackers->on_double_click([this,&ui](auto index){
        ui("#act_edit_tracker")->object.cast<ext::ui::action*>()->trigger();
    });
    trackers->on_context_menu([this,trackers](auto)
    {
        trackers->show_context_menu();

        if(trackers->current_index().isValid()){

        }
    });
    web_seeds->on_double_click([this,&ui](auto index){
        //todo: edit
        ui("#act_edit_web_seed")->object.cast<ext::ui::action*>()->trigger();
    });
    web_seeds->on_context_menu([this,web_seeds](auto)
    {
        if(web_seeds->current_index().isValid()){

        }
        web_seeds->show_context_menu();
    });

    peers->on_context_menu([this,peers](auto)
    {
        if(peers->current_index().isValid()){

        }
        peers->show_context_menu();
    });
    init_torrent_tracker_actions(ui);
    init_torrent_peers_actions(ui);
    init_torrent_web_seeds_actions(ui);
}


///---------------------------
void details::query_detail(bool try_status)
{
    Ext_Return_If(!zzz.service);

    if(expanded()){
        zzz.send({{"@",protocol::Message_Task_Details},{"type",type_},{"subset",subset_},{"id",id_},{"try_status",try_status}});
    }
}


///---------------------------
void details::update_partials(ext::ui::table* table,ext::value& values)
{
    for(auto& item : *values.cast_array())
    {
        if(!item.is_map()){
            continue;
        }
        auto range = item.text("range");

        if(auto iter = mapped_partials_.find(range);iter != mapped_partials_.end()){
            table->siblings(iter->second,item);
            mapped_partials_temp_.emplace(iter->first,iter->second);
            mapped_partials_.erase(iter);
        }else{
            auto cells = table->create_row(item);
            table->append_row(cells);
            mapped_partials_temp_.emplace(range,(ext::ui::standard_item*)cells[0]);
        }
    }
    for(auto& iter : mapped_partials_){
        table->remove_row(iter.second);
    }
    mapped_partials_ = std::move(mapped_partials_temp_);
    mapped_partials_temp_.clear();
}

void details::update_segments(ext::ui::table* table,ext::value& values)
{
    for(auto& item : *values.cast_array())
    {
        if(!item.is_map()){
            continue;
        }
        auto index = item.uint32("index");

        if(auto iter = mapped_segments_.find(index);iter != mapped_segments_.end()){
            table->siblings(iter->second,item);
            mapped_segments_temp_.emplace(iter->first,iter->second);
            mapped_segments_.erase(iter);
        }else{
            auto cells = table->create_row(item);
            table->append_row(cells);
            mapped_segments_temp_.emplace(index,(ext::ui::standard_item*)cells[0]);
        }
    }
    for(auto& iter : mapped_segments_){
        table->remove_row(iter.second);
    }
    mapped_segments_ = std::move(mapped_segments_temp_);
    mapped_segments_temp_.clear();
}

void details::update_trackers(ext::ui::table* table,ext::value& values)
{
    for(auto& item : *values.cast_array())
    {
        if(!item.is_map()){
            continue;
        }
        auto  url    = item.text("url");
        auto& status = item["status"];

        status = ext::ui::lang(protocol::Tracker_Status_Text[status.uint16()]);

        if(auto iter = mapped_trackers_.find(url);iter != mapped_trackers_.end()){
            table->siblings(iter->second,item);
            mapped_trackers_temp_.emplace(iter->first,iter->second);
            mapped_trackers_.erase(iter);
        }else{
            auto cells = table->create_row(item);
            table->append_row(cells);
            mapped_trackers_temp_.emplace(url,(ext::ui::standard_item*)cells[0]);
        }
    }
    for(auto& iter : mapped_trackers_){
        table->remove_row(iter.second);
    }
    mapped_trackers_ = std::move(mapped_trackers_temp_);
    mapped_trackers_temp_.clear();
}

void details::update_web_seeds(ext::ui::table* table,ext::value& values)
{
    for(auto& item : *values.cast_array())
    {
        if(!item.is_map()){
            continue;
        }
        auto url = item.text("url");

        if(auto iter = mapped_web_seeds_.find(url);iter != mapped_web_seeds_.end()){
            table->siblings(iter->second,item);
            mapped_web_seeds_temp_.emplace(iter->first,iter->second);
            mapped_web_seeds_.erase(iter);
        }else{
            auto cells = table->create_row(item);
            table->append_row(cells);
            mapped_web_seeds_temp_.emplace(url,(ext::ui::standard_item*)cells[0]);
        }
    }
    for(auto& iter : mapped_web_seeds_){
        table->remove_row(iter.second);
    }
    mapped_web_seeds_ = std::move(mapped_web_seeds_temp_);
    mapped_web_seeds_temp_.clear();
}

void details::update_peers(ext::ui::table* table,ext::value& values)
{
    for(auto& peer : *values.cast_array())
    {
        if(!peer.is_map()){
            continue;
        }
        auto address = peer.text("address");

        if(auto iter = mapped_peers_.find(address);iter != mapped_peers_.end()){
            table->siblings(iter->second,peer);
            mapped_peers_temp_.emplace(iter->first,iter->second);
            mapped_peers_.erase(iter);
        }else{
            auto cells    = table->create_row(peer);
            auto location = zzz.endpoint_to_country(address);

            table->append_row(cells);
            mapped_peers_temp_.emplace(address,(ext::ui::standard_item*)cells[0]);

            if(!location.empty()){
                auto item = (ext::ui::standard_item*)cells[0];
                item->text(location);
                item->icon(zzz.icons_country.get(boost::to_lower_copy(location),{24,18}));
            }
        }
    }
    for(auto& iter : mapped_peers_){
        table->remove_row(iter.second);
    }
    mapped_peers_ = std::move(mapped_peers_temp_);
    mapped_peers_temp_.clear();
}


///---------------------------
void details::minimize()
{
    detailbars_->resize(9999,1);
    tasks_splitter_->setSizes({9999,1});
}

void details::display(uint16_t type,int64_t id,ext::value& values)
{
    if(current_ == &details_[type]){
        goto bottom;
    }
    if(!details_[type].sample)
    {
        auto sample    = new ext::ui::sample(zzz.workspace / ("ui/tasks/" + type_to_filename(type)));
        auto node      = sample->ui("#details");
        auto detailbar = node->object.cast<ext::ui::detailbar*>();
        
        details_[type] = {sample,detailbar,ext::ui::form(node)};

        if(detailbar){
            init_detailbar(detailbar,type);
        }
    }
    if(current_ && current_->detailbar){
        current_->detailbar->hide();
    }
    if(current_ = &details_[type];current_->detailbar)
    {
        current_->detailbar->show();

        for(auto i=0;i<tasks_splitter_->count();++i){
            tasks_splitter_->handle(i)->setEnabled(current_->detailbar->is_expanded());
        }
        if(!current_->detailbar->is_expanded()){
            minimize();
        }else if(!sizes_.empty()){
            tasks_splitter_->setSizes(sizes_);
        }
    }
    detailbars_->show();

    bottom:
    type_    = type;
    id_      = id;
    current_ = &details_[type];
    update(type,values);
}

void details::hide()
{
    if(current_ && current_->detailbar)
    {
        if(current_->detailbar->is_expanded()){
            sizes_ = tasks_splitter_->sizes();
        }
        minimize();
        current_->detailbar->hide();
        current_ = nullptr;
    }
    detailbars_->hide();
}

void details::update(uint16_t type,ext::value& values)
{
    auto subset = values.extract("subset");

    for(auto iter : *values.cast_map())
    {
        if(iter.second.is_bool()){
            iter.second = ext::ui::lang(iter.second == true ? "true" : "false");
        }
    }
    if(type == protocol::Task_HTTP)
    {
        if(subset == "attributes"){
            if(auto state = values.get("state");state.is_number()){
                values["state"] = ext::ui::lang(protocol::Task_States_Text[state.uint16()]);
            }
            if(auto connectivity = values.get("connectivity");connectivity.is_number()){
                values["connectivity"] = ext::ui::lang(protocol::Connectivity_Types_Text[connectivity.uint16()]);
            }
        }else if(subset == "partials"){
            if(auto& partials = values["partials"];partials.is_array()){
                update_partials(details_[type].sample->ui.cast_id<ext::ui::table*>("partials"),partials);
            }
        }
    }else if(type == protocol::Task_Stream){
        if(subset == "segments"){
            if(auto& segments = values["segments"];segments.is_array()){
                update_segments(details_[type].sample->ui.cast_id<ext::ui::table*>("segments"),segments);
            }
        }
    }else if(type == protocol::Task_Torrent)
    {
        if(subset == "trackers"){
            if(auto& trackers = values["trackers"];trackers.is_array()){
                update_trackers(details_[type].sample->ui.cast_id<ext::ui::table*>("tracker_list"),trackers);
            }
        }else if(subset == "web_seeds"){
            if(auto& web_seeds = values["web_seeds"];web_seeds.is_array()){
                update_web_seeds(details_[type].sample->ui.cast_id<ext::ui::table*>("web_seeds_list"),web_seeds);
            }
        }else if(subset == "peers"){
            if(auto& peers = values["peers"];peers.is_array()){
                update_peers(details_[type].sample->ui.cast_id<ext::ui::table*>("peer_list"),peers);
            }
        }
    }
    details_[type].form.values(values);
}


}