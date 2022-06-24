#ifndef PRO_FILE_BROWSER_TASKS_H
#define PRO_FILE_BROWSER_TASKS_H

#include "../pro_sample.h"
#include "file_browser_global.h"
#include "file_browser_hosts.h"

namespace pro::file_browser
{

class panel_type : public pro::sample<pro::file_browser::global>
{
    using rows_type = std::unordered_map<int64_t,ext::ui::standard_item*>;


public:
    panel_type(pro::file_browser::global& zzz) : pro::sample<pro::file_browser::global>(zzz,zzz->workspace / "ui/file_browser/tasks_panel.sml")
    {
        ui.cast(table_,"Table");
    }


protected:
    /*
     * table
    */
    ext::ui::table* table_;
    /*
     * rows (sid -> oid -> row)
    */
    std::unordered_map<int64_t,rows_type> rows_;


protected:
    /*
     * state text
    */
    ext::text state_text(uint16_t state,uint16_t state2,uint16_t state3)
    {
        ext::text_view text;

        if(state != protocol::State_FS_Transfer){
            text = protocol::Filesystem_States_Text[state];
        }else if(state3 == protocol::Substate_None){
            text = protocol::Task_States_Text[state2];
        }else{
            text = protocol::Task_Substate_Text[state3];
        }
        return ext::ui::lang(text);
    }
    /*
     * state text
    */
    ext::text state_text(operation_t& operation)
    {
        return state_text(operation.state,operation.state2,operation.state3);
    }


public:
    /*
     * colorize
    */
    void colorize(auto row,std::uint16_t state)
    {
        switch(state)
        {
        case protocol::State_FS_Done:
        case protocol::State_FS_Canceled:
            return table_->row_color(row,"black");
        case protocol::State_FS_Error:
        case protocol::State_FS_Failed:
            return table_->row_color(row,"#ad1c1f");
        }
        table_->row_color(row,"#1f1f1f");
    }
    /*
     * add
    */
    void add(int64_t sid,int64_t oid,operation_t& operation)
    {
        auto cells = table_->create_row({
            ext::ui::lang(ext::fs::Operation_Text[operation.method]),
            state_text(operation),
            operation.time_start,
            operation.path_remote,
            operation.parameter.stringify(false)
        });
        table_->append_row(cells);
        rows_[sid][oid] = (ext::ui::standard_item*)cells[0];
        colorize(cells[0],operation.state);
    }
    /*
     * update
    */
    void update(int64_t sid,int64_t oid,ext::text_view name,const ext::text& text)
    {
        table_->sibling(rows_[sid][oid],name,text);
    }
    /*
     * state
    */
    void state(int64_t sid,int64_t oid,uint16_t state,uint16_t state2,uint16_t state3)
    {
        auto item = rows_[sid][oid];
        table_->sibling(item,"state",state_text(state,state2,state3));
        colorize(item,state);
    }
    /*
     * remove
    */
    void remove(int64_t sid,int64_t oid)
    {
        auto& container = rows_[sid];

        if(auto iter = container.find(oid);iter != container.end()){
            table_->remove_row(iter->second);
        }
    }
    /*
     * clear
    */
    void clear(int64_t sid)
    {
        for(auto& iter : rows_[sid]){
            table_->remove_row(iter.second);
        }
    }

};


class tasks : public pro::dialog_sample<pro::file_browser::global>
{
    friend class main;


public:
    tasks(pro::file_browser::global& global,tasks*& self,pro::file_browser::hosts& hosts,ext::ui::node_t* protocol_icons);
    ~tasks();


protected:
    /*
     * self
    */
    tasks*& self_;
    /*
     * hosts
    */
    pro::file_browser::hosts& hosts_;
    /*
     * protocol icons
    */
    ext::ui::node_t* protocol_icons_;
    /*
     * timer
    */
    std::int64_t timer_ = 0;
    /*
     * empty
    */
    ext::ui::widget* empty_ = nullptr;
    /*
     * tab
    */
    ext::ui::tab* tab_ = nullptr;
    /*
     * panels
    */
    std::unordered_map<std::int64_t,std::shared_ptr<panel_type>> panels_;


protected:
    /*
     * init actions
    */
    void init_actions();
    /*
     * init panel
    */
    void init_panel(std::int64_t hid,std::shared_ptr<panel_type>& panel,const std::shared_ptr<file_browser::filesystem>& filesystem);


protected:
    /*
     * on timer
    */
    void on_timer();
    /*
     * on update
    */
    void on_update(const std::shared_ptr<file_browser::filesystem>& filesystem);
    /*
     * on alert
    */
    void on_alert(alert_type* alert);


protected:
    /*
     * start timer
    */
    void start_timer();


public:
    /*
     * exec
    */
    void exec();

};

}

#endif
