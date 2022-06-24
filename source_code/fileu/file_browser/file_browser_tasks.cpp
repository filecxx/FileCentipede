#include "file_browser_tasks.h"

namespace pro::file_browser
{

tasks::tasks(pro::file_browser::global& global,tasks*& self,pro::file_browser::hosts& hosts,ext::ui::node_t* protocol_icons) :
    pro::dialog_sample<pro::file_browser::global>(global,global->workspace / "ui/file_browser/tasks.sml"),
    self_(self),
    hosts_(hosts),
    protocol_icons_(protocol_icons)
{
    ui.cast(tab_,"#tab");
    ui.cast(empty_,"#empty");

    dialog_->on_close([this](auto){
        self_ = nullptr;
        delete this;
    });
    init_actions();

    on_timer();
    start_timer();
}

tasks::~tasks()
{
    ext::ui::clear_timeout(timer_);
}


///---------------------------
void tasks::init_actions()
{
    ui.on_action("#act_delete_task",[](auto){

    });
    ui.on_action("#act_delete_all_task",[](auto){

    });
}

void tasks::init_panel(std::int64_t hid,std::shared_ptr<panel_type>& panel,const std::shared_ptr<file_browser::filesystem>& filesystem)
{
    auto title = filesystem->host_ + ":" + std::to_string(filesystem->port_);
    auto icon  = protocol_icons_->value(filesystem->protocol_);

    panel = std::make_shared<panel_type>(zzz);
    tab_->append(title,icon,panel->ui.cast<ext::ui::widget*>("#main"));
    panels_.emplace(hid,panel);

    for(auto& iter : filesystem->operations_){
        panel->add(filesystem->sid_,iter.first,iter.second);
    }
    for(auto& iter : filesystem->history_){
        panel->add(filesystem->sid_,iter.first,iter.second);
    }
}


///---------------------------
void tasks::on_timer()
{
    for(auto& iter : hosts_.hosts_)
    {
        for(auto& iter2 : iter.second.filesystems){
            on_update(iter2.second);
        }
    }
    empty_->visible(panels_.empty());
    tab_->visible(!panels_.empty());
}

void tasks::on_update(const std::shared_ptr<file_browser::filesystem>& filesystem)
{
    auto hid   = filesystem->hid_;
    auto panel = std::shared_ptr<panel_type>();

    if(auto iter = panels_.find(hid);iter == panels_.end()){
        init_panel(hid,panel,filesystem);
    }else{
        if(filesystem->operations_.empty()){
            //tab_->remove(iter->second->ui.cast<ext::ui::widget*>("#main"));
            //return panels_.erase(iter),void();
            //return;
        }
        panel = iter->second;
    }

}

void tasks::on_alert(alert_type* alert)
{
    auto hid   = ((alert_operation_type*)alert)->hid;
    auto panel = std::shared_ptr<panel_type>();

    if(auto iter = panels_.find(hid);iter != panels_.end()){
        panel = iter->second;
    }
    if(!panel){
        init_panel(hid,panel,hosts_(hid,((alert_operation_type*)alert)->sid));
    }else if(alert->type == Alert_Operation_Add){
        auto ptr = (alert_operation_add_type*)alert;
        panel->add(ptr->sid,ptr->oid,ptr->operation);
    }else if(alert->type == Alert_Operation_State){
        auto ptr = (alert_operation_state_type*)alert;
        panel->state(ptr->sid,ptr->oid,ptr->state,ptr->state2,ptr->state3);
    }else if(alert->type == Alert_Operation_Error){
        auto ptr = (alert_operation_error_type*)alert;
        panel->state(ptr->sid,ptr->oid,protocol::State_FS_Error,0,0);
    }else if(alert->type == Alert_Operation_Done){
        auto ptr = (alert_operation_done_type*)alert;
        panel->state(ptr->sid,ptr->oid,ptr->state,0,0);
    }else if(alert->type == Alert_Operations_Clear){
        auto ptr = (alert_operations_clear_type*)alert;
        panel->clear(ptr->sid);
    }
}


///---------------------------
void tasks::start_timer()
{
    timer_ = ext::ui::set_timeout([this]{
        on_timer();
        start_timer();
    },200ms);
}


///---------------------------
void tasks::exec()
{
    dialog_->show_active();
}


}