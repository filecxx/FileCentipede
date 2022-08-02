#ifndef PRO_TASKS_MAIN_H
#define PRO_TASKS_MAIN_H

#include "../catalogs/catalogs_main.h"
#include "tasks_add_task.h"
#include "tasks_edit_task.h"
#include "tasks_details.h"
#include "tasks_confirm_torrent.h"
#include "tasks_confirm_http.h"
#include "tasks_refresh_address.h"
#include "tasks_transfer_completed.h"
#include "../tools/tool_checksum.h"

namespace pro::tasks
{

class main
{
    using file_type = ext::ui::filesystem::file_type;
    using node_type = ext::ui::filesystem::node_type;

    struct task_t
    {
        std::uint16_t  type;
        std::uint16_t  state       = protocol::State_Invalid;
        std::uint32_t  files       = 0;
        std::uint32_t  requery     = 0;
        ext::boolean_t full_status = false;
        node_type*     node        = nullptr;
    };
    struct active_task_t
    {
        std::uint16_t  type;
        std::uint16_t  state;
        ext::boolean_t full_status = false;
        std::int32_t   progress    = 0;
    };
    struct task_directory_t
    {
        int32_t checked[3]  = {0,0,0};
        int64_t transferred = 0;
        int64_t file_size   = 0;
    };


public:
    main(pro::global& global,ext::ui::model& instance);


public:
    ~main();


protected:
    /*
     * global
    */
    pro::global& zzz;
    /*
     * ui
    */
    ext::ui::model& ui;


protected:
    /*
     * catalogs
    */
    pro::catalogs::main* catalogs_ = nullptr;
    /*
     * detailbar
    */
    pro::tasks::details details_;


protected:
    /*
     * tasks
    */
    ext::ui::filesystem* tasks_ = nullptr;
    /*
     * status panel
    */
    ext::ui::widget* nav_status_panel_ = nullptr;
    /*
     * catalogs panel
    */
    ext::ui::widget* nav_catalogs_panel_ = nullptr;
    /*
     * status
    */
    ext::ui::list* nav_status_ = nullptr;
    /*
     * catalogs
    */
    ext::ui::list* nav_catalogs_ = nullptr;


protected:
    /*
     * need recount text2
    */
    ext::boolean_t need_recount_text2_ = false;
    /*
     * timepoint interval
    */
    ext::steady_time_point_t timepoint_interval_;
    /*
     * timepoint
    */
    ext::steady_time_point_t timepoint_seconds_;
    /*
     * active tasks
    */
    std::unordered_map<int64_t,active_task_t> active_tasks_;
    /*
     * tasks
    */
    std::unordered_map<int64_t,task_t> all_tasks_;
    /*
     * confirming tasks
    */
    std::unordered_map<int64_t,std::pair<uint16_t,void*>> confirming_tasks_;
    /*
     * selected states
    */
    std::vector<int32_t> selected_states_;
    /*
     * selected state
    */
    ext::text selected_state_;
    /*
     * selected catalogs
    */
    std::vector<ext::ui::list_item*> selected_catalogs_;


public:
    /*
     * find task
    */
    template<typename handler_type>
    void find_task(int64_t id,const handler_type& handler)
    {
        if(auto iter = all_tasks_.find(id);iter != all_tasks_.end()){
            handler(iter->first,iter->second);
        }
    }
    /*
     * find task
    */
    template<typename handler_type>
    void find_task(ext::value& values,const handler_type& handler)
    {
        find_task(values.int64("id"),handler);
    }


protected:
    /*
     * convert nav states
    */
    void convert_nav_states(ext::text_view text,std::vector<int32_t>& states);
    /*
     * filter tasks
    */
    void filter_tasks();
    /*
     * matches filter
    */
    bool matches_filter(task_t& task);
    /*
     * recount text2
    */
    void recount_text2();


protected:
    /*
     * init actions
    */
    void init_actions();
    /*
     * init nav
    */
    void init_nav();
    /*
     * init catalogs
    */
    void init_catalogs();
    /*
     * init filter
    */
    void init_filter();
    /*
     * init tasks
    */
    void init_tasks();


protected:
    /*
     * query status
    */
    void query_status(int64_t id,uint16_t type,bool extended = false);
    /*
     * query progress
    */
    void query_progress(int64_t id,uint16_t type);
    /*
     * query files
    */
    void query_files(int64_t id,uint16_t type,uint32_t offset,uint32_t size);


protected:
    /*
     * add task
    */
    void add_task(uint16_t type,uint16_t state,int64_t id,uint32_t mode,ext::value& json,bool full_status);
    /*
     * update task
    */
    bool update_task(uint16_t state,int64_t id,uint32_t mode,ext::value& json,bool full_status);
    /*
     * update task files
    */
    void update_task_files(int64_t id,task_t& task,ext::value& json);
    /*
     * update tasks catalog
    */
    void update_tasks_catalog(ext::text_view name,ext::text_view new_name);
    /*
     * update active task state
    */
    void update_active_task_state(ext::value& json,std::int64_t id,task_t& task);
    /*
     * erase active task
    */
    bool erase_active_task(int64_t id,task_t& task);
    /*
     * erase task
    */
    bool erase_task(int64_t id);


public:
    /*
     * start task
    */
    void start_task(int64_t id);
    /*
     * start all tasks
    */
    void start_all_tasks();
    /*
     * start selected tasks
    */
    void start_selected_tasks();
    /*
     * stop task
    */
    void stop_task(int64_t id);
    /*
     * stop all tasks
    */
    void stop_all_tasks();
    /*
     * stop selected tasks
    */
    void stop_selected_tasks();
    /*
     * delete task
    */
    void delete_task(int64_t id,bool delete_file);
    /*
     * delete all tasks
    */
    void delete_all_tasks();
    /*
     * delete selected tasks
    */
    void delete_selected_tasks();
    /*
     * rename task
    */
    bool rename_task(std::int64_t id,const ext::value& idx,std::string_view current_name,std::string& new_name);
    /*
     * rename selected tasks
    */
    void rename_selected_tasks();
    /*
     * redownload task
    */
    void redownload_task(int64_t id);
    /*
     * redownload selected tasks
    */
    void redownload_selected_tasks();
    /*
     * refresh task address
    */
    void refresh_task_address(int64_t id);
    /*
     * refresh task address
    */
    void refresh_task_address(int64_t id,uint16_t type,ext::text_view page_url,ext::text_view resid);
    /*
     * refresh selected tasks address
    */
    void refresh_selected_tasks_address();
    /*
     * edit task
    */
    void edit_task(int64_t id);
    /*
     * edit selected tasks
    */
    void edit_selected_tasks();
    /*
     * open task file
    */
    void open_task_file(ext::ui::filesystem::node_type* node,bool completed_only);
    /*
     * open selected tasks files
    */
    void open_selected_tasks_file();
    /*
     * open selected tasks with
    */
    void open_selected_tasks_with();
    /*
     * open selected tasks directories
    */
    void open_selected_tasks_directories();
    /*
     * move selected tasks
    */
    void move_selected_tasks();
    /*
     * move task
    */
    bool move_task(int64_t id,std::string_view path);
    /*
     * open selected tasks addresses
    */
    void copy_selected_tasks_addresses();
    /*
     * copy selected tasks names
    */
    void copy_selected_tasks_names();
    /*
     * copy selected tasks hashes
    */
    void copy_selected_tasks_hashes();
    /*
     * export selected tasks torrent
    */
    void export_selected_tasks_torrent();
    /*
     * calc_checksum
    */
    void calc_checksum();
    /*
     * show detail
    */
    void show_detail(int64_t id);
    /*
     * show completed
    */
    void show_completed_dialog(int64_t id,ext::value& values,const ext::text& error = {});


public:
    /*
     * on timer
    */
    void on_timer(ext::steady_time_point_t now);
    /*
     * on timer
    */
    void on_timer_second(ext::steady_time_point_t now);
    /*
     * on timer actives
    */
    void on_timer_actives(ext::steady_time_point_t now);


public:
    /*
     * on catalog add
    */
    void on_catalog_add(ext::value& json);
    /*
     * on catalog update
    */
    void on_catalog_update(ext::value& json);
    /*
     * on catalog remove
    */
    void on_catalog_remove(ext::value& json);
    /*
     * on catalogs
    */
    void on_catalogs(ext::value& json);


public:
    /*
     * on http confirming
    */
    void on_http_confirming(ext::value& json,int64_t id,uint16_t type,uint16_t state);
    /*
     * on torrent confirming
    */
    void on_torrent_confirming(ext::value& json,int64_t id,uint16_t type,uint16_t state);
    /*
      * on task confirmed
     */
    void on_task_confirmed(std::int64_t id,ext::boolean_t confirmed);
    /*
     * on task confirming
    */
    void on_task_confirming(ext::value& json,int64_t id,uint16_t type,uint16_t state);
    /*
     * on confirming files
    */
    void on_confirming_files(int64_t id,uint16_t type,ext::value& json,void* ptr);


public:
    /*
     * on task error
    */
    bool on_task_error(int64_t id,task_t& task,uint16_t old_state,const ext::text& error);
    /*
     * on task completed
    */
    bool on_task_completed(int64_t id,task_t& task,uint16_t old_state);
    /*
     * on task state
    */
    void on_task_state(ext::value& json,int64_t id,task_t& task,uint16_t old_state);
    /*
     * on task status
    */
    void on_task_status(ext::value& json);
    /*
     * on task progress
    */
    void on_task_progress(ext::value& json);
    /*
     * on task files
    */
    void on_task_files(ext::value& json);
    /*
     * on task detail
    */
    void on_task_detail(ext::value& json);
    /*
     * on task edit
    */
    void on_task_edit(ext::value& json);
    /*
     * on task renamed
    */
    void on_task_renamed(ext::value& json);
    /*
     * on task removed
    */
    void on_task_removed(ext::value& json);
    /*
     * on task refresh address
    */
    void on_task_refresh_address(ext::value& json);
    /*
     * on task edit
    */
    void on_task_config(ext::value& json);
    /*
     * on selection changed
    */
    void on_selection_changed();
    /*
     * on context menu
    */
    void on_context_menu();


public:
    /*
     * init
    */
    void init();
    /*
     * clear
    */
    void clear();


};

}

#endif
