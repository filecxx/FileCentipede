#ifndef PRO_TASKS_EDIT_TASK_H
#define PRO_TASKS_EDIT_TASK_H

#include "../pro_sample.h"

namespace pro::tasks
{

class edit_task : public pro::dialog_sample
{
public:
    edit_task(pro::global& global);


public:
    ~edit_task();


protected:
    /*
     * id
    */
    std::int64_t id_ = 0;
    /*
     * type
    */
    std::uint16_t type_ = 0;
    /*
     * form
    */
    ext::ui::form form_;


protected:
    /*
     * on save
    */
    void on_save();


protected:
    /*
     * init default values
    */
    void init_default_values(const ext::text& type);


public:
    /*
     * type
    */
    std::string_view type(std::uint16_t n);


public:
    /*
     * exec
    */
    void exec(ext::value& json);

};

}


#endif
