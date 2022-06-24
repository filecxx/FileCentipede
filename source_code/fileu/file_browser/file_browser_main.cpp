#include "file_browser_main.h"

namespace pro::file_browser
{

main::main(pro::file_browser::global& global,ext::ui::model& instance) :
    zzz(global),
    ui(instance),
    hosts_(zzz,ui)
{

}


///---------------------------
void main::on_status(ext::value& values)
{
    auto id    = values.int64("id");
    auto sid   = values.int64("sid");
    auto oid   = values.get("oid");
    auto state = values.uint16("state");

    if(!oid.is_number())
    {
        if(state == protocol::State_FS_Running){
            create_tab(id,sid,values);
        }
    }else if(auto filesystem = hosts_(id,sid);!filesystem){
        ext::debug << "no filesystem session id " <<= sid;
    }else if(oid.is_number()){
        filesystem->on_status(state,oid.int64(),values);
    }
}

void main::on_tab_close(uint32_t index)
{
    auto tid = tabs_->item_data(index).int64();
    Ext_Return_If(tid == 0);

    auto& mapped = mapped_[tid];
    auto  host   = hosts_(mapped.first);

    zzz->send({{"@",protocol::Message_FS},{"type",host->type},{"method",ext::fs::Disconnect},{"id",mapped.first},{"sid",mapped.second},{"oid",0}});

    host->filesystems.erase(mapped.second);
    tabs_->remove(index);
    mapped_.erase(tid);

    if(tabs_->count() == 0){
        create_default();
    }

}


///---------------------------
void main::recalc_tasks()
{
    auto  all     = size_t(0);
    auto  current = size_t(0);
    auto& mapped  = mapped_[zzz.current_tid];

    for(auto iter = hosts_.hosts_.begin();iter != hosts_.hosts_.end();)
    {
        auto  id          = iter->first;
        auto& filesystems = (iter++)->second.filesystems;

        for(auto& filesystem : filesystems)
        {
            if(mapped.first == id && mapped.second == filesystem.second->sid_){
                current += filesystem.second->operations_.size();
            }
            all += filesystem.second->operations_.size();
        }
    }
    tasks_button_->text(0,1,std::to_string(current));
    tasks_button_->text(1,1,std::to_string(all));
    tasks_button_->icon(all == 0 ? 0 : 1);
}

void main::create_tab(std::int64_t id,std::int64_t sid,ext::value& values)
{
    auto& config     = zzz->nfs_hosts[id];
    auto  filesystem = std::move(default_filesystem_);
    auto  tid        = ++increased_tab_id_;
    auto  path       = values.text("path");

    if(!filesystem){
        filesystem = std::make_shared<file_browser::filesystem>(zzz,&hosts_,tabs_,statusbar_);
    }else{
        tabs_->remove(0);
        default_filesystem_.reset();
    }
    if(path.empty()){
        path = config.text("path");
    }
    filesystem->init(id,sid,tid,values.uint16("type"));
    filesystem->protocol_ = config.text("protocol");
    filesystem->host_     = config.text("host");
    filesystem->port_     = config.uint16("port");
    filesystem->update_path(path);

    mapped_[tid] = {id,sid};
    hosts_(id)->filesystems.emplace(sid,filesystem);

    tabs_->current(tabs_->append("",protocol_icons_->value("folder"),filesystem->widget_));
    filesystem->list(path);
}

void main::create_default()
{
    default_filesystem_ = std::make_shared<file_browser::filesystem>(zzz,&hosts_,tabs_,statusbar_);
    default_filesystem_->widget_->data(0);

    tabs_->append("...",protocol_icons_->value("folder"),default_filesystem_->widget_);
}


///---------------------------
void main::init_events()
{
    zzz.tasks_alert = [this](alert_type* alert)
    {
        if(tasks_){
            tasks_->on_alert(alert);
        }
        recalc_tasks();
    };
    tasks_button_->on_click([this](auto e){
        ext::try_new<pro::file_browser::tasks>(tasks_,zzz,tasks_,hosts_,protocol_icons_)->exec();
    });
    tabs_->on_change([this](auto index)
    {
        if(auto tid = tabs_->item_data(index).int64();tid != zzz.current_tid){
            zzz.current_tid = tid;
            recalc_tasks();
        }
    });
    tabs_->on_tab_close([this](auto index){
        on_tab_close(index);
    });
    hosts_.on_remove([this](auto& host)
    {
        for(auto iter = host.filesystems.begin();iter != host.filesystems.end();)
        {
            if(auto index = tabs_->indexOf((iter++)->second->widget_);index != -1){
                on_tab_close(index);
            }
        }
    });
    hosts_.on_change([this](auto type,auto& host){

    });
}


///---------------------------
void main::init(ext::ui::tab* main_tab,ext::ui::statusbar* statusbar)
{
    if(!ui.import("ui/file_browser/main.sml")){
        return;
    }else if(protocol_icons_){
        return hosts_.show();
    }
    ui.cast(tabs_,"#tabs");
    ui.cast(tasks_button_,"#nav_nfs_tasks");

    hosts_.init(protocol_icons_ = ui("#nfs_protocol_icons"));
    init_events();

    statusbar_     = statusbar;
    client_layout_ = ui("#nfs_layout")->object;
    main_tab->layout(1,client_layout_);
    create_default();
}

void main::clear()
{
    tabs_->clear();
    hosts_.clear();
    mapped_.clear();

    recalc_tasks();
    create_default();
}


}