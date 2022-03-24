#ifndef PRO_TASKS_ADD_TASK_H
#define PRO_TASKS_ADD_TASK_H

#include "../pro_sample.h"

namespace pro::tasks
{

class add_task : public pro::dialog_sample<>
{
    struct config_t
    {
        std::uint16_t type;
        ext::value    values;
    };


public:
    add_task(pro::global& global,ext::boolean_t is_stream,std::string_view ui_path);


public:
    ~add_task();


protected:
    /*
     * is stream
    */
    ext::boolean_t is_stream_ = false;
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
     * timer
    */
    std::int64_t timer_ = 0;
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


public:
    /*
     * on delete
    */
    template<typename handler_type>
    void on_delete(const handler_type& handler)
    {
        on_delete_ = handler;
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
