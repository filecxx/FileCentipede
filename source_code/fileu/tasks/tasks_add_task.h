#ifndef PRO_TASKS_ADD_TASK_H
#define PRO_TASKS_ADD_TASK_H

#include "../pro_sample.h"

namespace pro::tasks
{

class add_task : public pro::dialog_sample<pro::global>
{
    struct config_t
    {
        std::uint16_t type;
        ext::value    values;
    };


public:
    add_task(pro::global& global,ext::boolean_t is_stream,ext::boolean_t is_directory);


public:
    ~add_task();


protected:
    /*
     * is stream
    */
    ext::boolean_t is_stream_ = false;
    /*
     * is directory
    */
    ext::boolean_t is_directory_ = false;
    /*
     * tab
    */
    ext::ui::tab* tab_ = nullptr;
    /*
     * addresses
    */
    ext::ui::text_edit* addresses_ = nullptr;
    /*
     * forms
    */
    std::array<ext::ui::form,protocol::Task_Types_Size> forms_ = {};
    /*
     * combobox configs
    */
    std::array<ext::ui::combobox*,protocol::Task_Types_Size> combobox_configs_ = {};
    /*
     * current configs
    */
    std::array<config_t*,protocol::Task_Types_Size> current_configs_ = {};
    /*
     * default values
    */
    std::array<ext::value,protocol::Task_Types_Size> default_values_ = {};
    /*
     * timer
    */
    std::int64_t timer_ = 0;
    /*
     * default save path
    */
    ext::text default_save_path_;
    /*
     * uris
    */
    std::unordered_map<ext::text,config_t> uris_;
    /*
     * configs
    */
    std::unordered_map<ext::text,config_t> configs_;
    /*
     * cached uris
    */
    std::unordered_set<ext::text> cached_uris_;
    /*
     * on delete
    */
    std::function<void()> on_delete_;
    /*
     * placeholders
    */
    ext::ui::node_t* placeholders_ = nullptr;


public:
    /*
     * on delete
    */
    template<typename handler_type>
    void on_delete(const handler_type& handler)
    {
        on_delete_ = handler;
    }


public:
    /*
     * default_save_path
    */
    ext::text_view default_save_path()
    {
        if(!default_save_path_.empty()){
            return default_save_path_;
        }
        return zzz->configs["general"].text_view("default_save_path");
    }


protected:
    /*
     * analyze addresses
    */
    void analyze_addresses();
    /*
     * download now
    */
    void download(bool immediately);
    /*
     * change save path
    */
    void change_save_path(const ext::text& path);


protected:
    /*
     * init widget
    */
    void init_widget(const ext::text& name,std::uint16_t config_type,ext::ui::object& object);
    /*
     * init form
    */
    void init_form(const ext::text& name,uint16_t type);
    /*
     * init events
    */
    void init_events();


public:
    /*
     * exec
    */
    void exec();
    /*
     * active
    */
    void active();
    /*
     * append
    */
    bool append(const std::vector<ext::text>& addresses);

};

}

#endif
