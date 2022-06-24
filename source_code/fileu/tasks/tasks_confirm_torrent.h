#ifndef PRO_TASKS_CONFIRM_TORRENT_H
#define PRO_TASKS_CONFIRM_TORRENT_H

#include "../pro_sample.h"

namespace pro::tasks
{

class confirm_torrent : public pro::dialog_sample<pro::global>
{
    struct task_directory_t
    {
        int32_t checked[3] = {0,0,0};
        int64_t downloaded = 0;
        int64_t file_size  = 0;
    };

public:
    confirm_torrent(pro::global& global,ext::value& json,ext::func<void(int64_t,bool)>&& callback);


protected:
    /*
     * loader
    */
    ext::ui::widget* loader_ = nullptr;
    /*
     * files
    */
    ext::ui::filesystem* files_ = nullptr;
    /*
     * filter
    */
    ext::ui::combobox* filter_ = nullptr;
    /*
     * callback
    */
    ext::func<void(int64_t,bool)> callback_;
    /*
     * form attributes
    */
    ext::ui::form form_attributes_;
    /*
     * form information
    */
    ext::ui::form form_information_;
    /*
     * attr loaded
    */
    ext::boolean_t attr_loaded_ = false;
    /*
     * meta loaded
    */
    ext::boolean_t meta_loaded_ = false;
    /*
     * files loaded
    */
    ext::boolean_t files_loaded_ = false;
    /*
     * confirmed
    */
    ext::boolean_t confirmed_ = false;
    /*
     * destroying
    */
    ext::boolean_t destroying_ = false;
    /*
     * id
    */
    std::int64_t id_ = 0;


protected:
    /*
     * init actions
    */
    void init_actions();


protected:
    /*
     * on ok
    */
    void on_ok();
    /*
     * on checked
    */
    void on_checked(ext::ui::filesystem::node_type* node);
    /*
     * on filter
    */
    void on_filter();


protected:
    /*
     * load catalogs
    */
    void load_catalogs();
    /*
     * load filters
    */
    void load_filters();


public:
    /*
     * exec
    */
    void exec(ext::value& json,uint16_t state);
    /*
     * update
    */
    void update(ext::value& json,uint16_t state);
    /*
     * update files
    */
    void update_files(ext::value& json,uint32_t total,uint32_t offset,uint32_t size);
    /*
     * destroy
    */
    void destroy();

};

}



#endif
