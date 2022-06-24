#include "file_browser_handler.h"

namespace pro::file_browser
{

handler::handler(pro::global& global,ext::ui::model& instance) : zzz(global),ui(instance)
{

}


///-----------------------------
void handler::on_status(ext::value& json)
{
    if(file_browser_){
        file_browser_->on_status(json);
    }
}


///-----------------------------
void handler::on_hosts(ext::value& json)
{
    for(auto& iter : *json["groups"].cast_array()){
        on_group_add(iter);
    }
    for(auto& iter : *json["hosts"].cast_array()){
        on_host_add(iter);
    }
}

void handler::on_group_add(ext::value& json)
{
    if(file_browser_){
        file_browser_->hosts().add_group(json);
    }
    zzz->nfs_groups[json.int64("id")] = json;
}

void handler::on_group_edit(ext::value& json)
{
    auto id = json.int64("id");

    if(file_browser_){
        file_browser_->hosts().edit_group(id,json);
    }
    zzz->nfs_groups[id] = json;
}

void handler::on_group_remove(ext::value& json)
{
    auto id = json.int64("id");

    if(file_browser_){
        file_browser_->hosts().remove_group(id);
    }
    zzz->nfs_groups.erase(id);
}

void handler::on_host_add(ext::value& json)
{
    if(file_browser_){
        auto connect = json.extract("connect");
        file_browser_->hosts().add_host(json,connect == true);
    }
    zzz->nfs_hosts[json.int64("id")] = json;
}

void handler::on_host_edit(ext::value& json)
{
    auto id = json.int64("id");

    if(file_browser_){
        file_browser_->hosts().edit_host(id,json);
    }
    zzz->nfs_hosts[id] = json;
}

void handler::on_host_remove(ext::value& json)
{
    auto id = json.int64("id");

    if(file_browser_){
        file_browser_->hosts().remove_host(id);
    }
    zzz->nfs_hosts.erase(id);
}


///---------------------------
void handler::clear()
{
    if(file_browser_){
        file_browser_->clear();
    }
    zzz->nfs_groups.clear();
    zzz->nfs_hosts.clear();
}



}