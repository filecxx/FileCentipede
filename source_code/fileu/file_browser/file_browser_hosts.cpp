#include "file_browser_hosts.h"

namespace pro::file_browser
{

hosts::hosts(pro::file_browser::global& global,ext::ui::model& instance): zzz(global),ui(instance)
{

}


///---------------------------
hosts::host_t* hosts::operator()(std::int64_t hid)
{
    if(auto iter = hosts_.find(hid);iter != hosts_.end()){
        return &iter->second;
    }
    return nullptr;
}

std::shared_ptr<filesystem> hosts::operator()(std::int64_t hid,std::int64_t sid)
{
    if(auto iter = hosts_.find(hid);iter != hosts_.end())
    {
        if(auto iter2 = iter->second.filesystems.find(sid);iter2 != iter->second.filesystems.end()){
            return iter2->second;
        }
    }
    return nullptr;
}


///---------------------------
auto hosts::make_host_name(const ext::value& data) -> ext::text
{
    auto name = data.text("name");

    if(name.empty()){
        name = data.text("host") + ":" + data.uint16_s("port");
    }
    return name;
}

bool hosts::matches_filter(ext::text_view text)
{
    auto filter_text = boost::to_lower_copy(nav_hosts_filter_->text());

    return !filter_text.empty() && text.find(filter_text) == std::string::npos;
}


///---------------------------
void hosts::init_events()
{
    nav_hosts_filter_->on_change([this](auto str)
    {
        nav_hosts_->each([this](auto i,auto item)
        {
            if(!nav_hosts_->is_group((ext::ui::list_item*)item)){
                nav_hosts_->visible(i,!matches_filter(item->text()));
            }
            return false;
        });
    });
    nav_hosts_->on_item_double_click([this](auto item)
    {
        if(nav_hosts_->is_group((ext::ui::list_item*)item)){
            return;
        }
        if(auto id = ((ext::ui::list_item*)item)->data();id.is_number()){
            zzz->send({{"@",protocol::Message_FS},{"type",hosts_[id.int64()].type},{"id",id.int64()}});
        }
    });
    nav_hosts_->on_context_menu([this](auto){
        on_context_menu();
    });

}

void hosts::init_actions()
{
    ui.on_action("#act_nfs_host_add",[this](auto)
    {
        auto current = nav_hosts_->current_item();
        auto gid     = int64_t(0);

        if(nav_hosts_->is_group(current)){
            gid = current->data().int64();
        }
        (new file_browser::edit_host(zzz))->add(gid);
    });
    ui.on_action("#act_nfs_host_add_group",[this](auto)
    {
        auto input = ui.cast<ext::ui::input_dialog*>("#nfs_edit_group");

        if(input->exec() != 0)
        {
            if(auto name = input->value().text();!name.empty()){
                zzz->send({{"@",protocol::Message_FS_Group_Add},{"name",name.string_view()}});
            }
        }
    });
    ui.on_action("#act_nfs_host_edit",[this](auto)
    {
        auto current = nav_hosts_->current_item();
        auto id      = current->data().int64();

        if(id != 0)
        {
            if(nav_hosts_->is_group(current)){
                return on_edit_group(id);
            }
            (new file_browser::edit_host(zzz))->edit(id,zzz->nfs_hosts[id]["gid"].int64());
        }
    });
    ui.on_action("#act_nfs_host_connect",[this](auto)
    {
        for(auto item : nav_hosts_->selected_items())
        {
            if(auto id = item->data().int64();!nav_hosts_->is_group(item)){
                zzz->send({{"@",protocol::Message_FS},{"type",hosts_[id].type},{"id",id}});
            }
        }
    });
    ui.on_action("#act_nfs_host_remove",[this](auto)
    {
        for(auto item : nav_hosts_->selected_items())
        {
            auto id = item->data().int64();

            if(nav_hosts_->is_group(item) && id != 0){
                zzz->send({{"@",protocol::Message_FS_Group_Remove},{"id",id}});
            }else if(id != 0){
                zzz->send({{"@",protocol::Message_FS_Host_Remove},{"id",id}});
            }
        }
    });
}

void hosts::init_data()
{
    add_group({{"id",0},{"name","all"_lang}});

    for(auto& iter : zzz->nfs_groups){
        add_group(iter.second);
    }
    for(auto& iter : zzz->nfs_hosts){
        add_host(iter.second);
    }
}


///---------------------------
void hosts::on_edit_group(int64_t id)
{
    auto input = ui.cast<ext::ui::input_dialog*>("#nfs_edit_group");

    if(input->exec(groups_[id]->text()) != 0)
    {
        if(auto name = input->value().text();!name.empty()){
            zzz->send({{"@",protocol::Message_FS_Group_Edit},{"id",id},{"name",name.string_view()}});
        }
    }
}

void hosts::on_context_menu()
{
    auto current = nav_hosts_->current_item();

    for(auto& name : {"connect","disconnect"}){
        if(auto action = ui.cast_id<ext::ui::action*>("act_nfs_host_" + ext::text(name))){
            action->enable(current && !nav_hosts_->is_group(current));
        }
    }
    for(auto& name : {"edit","remove"}){
        if(auto action = ui.cast_id<ext::ui::action*>("act_nfs_host_" + ext::text(name))){
            action->enable(current && current != group_all_->item);
        }
    }
    context_menu_->show_context_menu();
}


///---------------------------
ext::text hosts::convert_protocol(ext::text_view protocol,ext::text_view default_protocol)
{
    if(protocol.empty()){
        protocol = default_protocol;
    }else if(protocol == "http"){
        protocol = "webdav";
    }else if(protocol == "https"){
        protocol = "webdavs";
    }
    return protocol;
}


///---------------------------
void hosts::add_group(const ext::value& data)
{
    auto id    = data.int64("id");
    auto group = nav_hosts_->add_group(data.text_view("name"),protocol_icons_->value("group").text_view());

    if(id == 0){
        group_all_ = group;
    }
    group->item->data(id);
    groups_[id] = group;
}

void hosts::add_host(const ext::value& data,bool connect)
{
    auto id       = data.int64("id");
    auto protocol = data.text_view("protocol");
    auto type     = protocol::filesystem_type(protocol);
    auto group    = group_all_;

    if(auto iter = groups_.find(data.int64("gid"));iter != groups_.end()){
        group = iter->second;
    }
    auto item = nav_hosts_->add(group,make_host_name(data),protocol_icons_->value(protocol).text_view());
    item->data(id);
    hosts_.emplace(id,host_t{item,type});

    if(connect){
        zzz->send({{"@",protocol::Message_FS},Ext_Pairs((type)(id))});
    }
}

void hosts::edit_group(std::int64_t id,const ext::value& data)
{
    if(auto iter = groups_.find(id);iter != groups_.end()){
        iter->second->text(data.text_view("name"));
    }
}

void hosts::edit_host(std::int64_t id,const ext::value& data)
{
    if(auto iter = hosts_.find(id);iter != hosts_.end())
    {
        auto protocol = data.text_view("protocol");
        auto type     = protocol::filesystem_type(protocol);

        iter->second.item->text(make_host_name(data));
        iter->second.item->icon(protocol_icons_->value(protocol).text_view());
        iter->second.type = type;
    }
}

void hosts::remove_group(std::int64_t id)
{
    if(auto iter = groups_.find(id);iter != groups_.end())
    {
        for(auto item : iter->second->children){
            nav_hosts_->move_to(item,group_all_);
        }
        iter->second->children.clear();
        nav_hosts_->remove_group(iter->second);
        groups_.erase(iter);
    }
}

void hosts::remove_host(std::int64_t id)
{
    if(auto iter = hosts_.find(id);iter != hosts_.end()){
        on_remove_(iter->second);
        nav_hosts_->remove(iter->second.item);
        hosts_.erase(iter);
    }
}

void hosts::connect_host(const ext::uri::address& address,ext::text_view default_protocol)
{
    auto& host     = address.host();
    auto  protocol = convert_protocol(host.protocol(),default_protocol);
    auto  hostname = host.hostname();
    auto  port     = host.port();
    auto  path     = address.path().full();

    if(hostname.empty()){
        return;
    }
    auto type = protocol::filesystem_type(protocol);

    for(auto& nfs_host : zzz->nfs_hosts)
    {
        if(nfs_host.second.text_view("host") == hostname && nfs_host.second.text_view("protocol") == protocol && nfs_host.second.uint16("port") == port){
            return zzz->send({{"@",protocol::Message_FS},{"id",nfs_host.first},Ext_Pairs((type)(path))}),void();
        }
    }
    auto config = ext::value(zzz->configs["nfs"]);

    if(!host.user().empty()){
        config["user"] = host.user();
    }
    if(!host.password().empty()){
        config["pass"] = host.password();
    }
    config.merge({
        {"@",protocol::Message_FS_Host_Add},
        {"gid",0},
        {"connect",true},
        {"host",hostname},

        Ext_Pairs((type)(protocol)(hostname)(port)(path))
    });
    zzz->send(config);
}


///---------------------------
void hosts::show()
{
    nav_hosts_panel_->show();
}

void hosts::clear()
{
    decltype(hosts_) hosts;
    std::swap(hosts_,hosts);
    groups_.clear();
    nav_hosts_->clear();
    add_group({{"id",0},{"name","all"_lang}});
}

void hosts::init(ext::ui::node_t* protocol_icons)
{
    protocol_icons_ = protocol_icons;

    ui.cast(nav_hosts_panel_,"#nav_nfs_hosts_panel");
    ui.cast(nav_hosts_,"#nav_nfs_hosts");
    ui.cast(nav_hosts_filter_,"#nav_nfs_hosts_filter");
    ui.cast(context_menu_,"#nfs_hosts_context_menu");
    ui("#nav")->object.cast<ext::ui::widget*>()->layout()->addWidget(nav_hosts_panel_);

    init_events();
    init_actions();
    init_data();
}

}