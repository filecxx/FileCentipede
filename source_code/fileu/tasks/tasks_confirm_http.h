#ifndef PRO_TASKS_CONFIRM_HTTP_H
#define PRO_TASKS_CONFIRM_HTTP_H

#include "../pro_sample.h"

namespace pro::tasks
{

class confirm_http : public pro::dialog_sample<pro::global>
{
public:
    confirm_http(pro::global& global,ext::value& json,ext::func<void(int64_t,bool)>&& callback);


protected:
    /*
     * callback
    */
    ext::func<void(int64_t,bool)> callback_;
    /*
     * files
    */
    ext::ui::filesystem* files_ = nullptr;
    /*
     * paths
    */
    ext::ui::combobox* paths_combobox_ = nullptr;
    /*
     * proxy
    */
    ext::ui::combobox* proxy_combobox_ = nullptr;
    /*
     * form
    */
    ext::ui::form form_;
    /*
     * ids
    */
    std::int64_t id_;
    /*
     * destroying
    */
    ext::boolean_t destroying_ = false;
    /*
     * confirmed
    */
    ext::boolean_t confirmed_ = false;
    /*
     * values
    */
    ext::value values_;


protected:
    /*
     * init ui
    */
    void init_ui();


protected:
    /*
     * on download
    */
    void on_download(bool later);


protected:
    /*
     * load catalogs
    */
    void load_catalogs();
    /*
     * load proxies
    */
    void load_proxies();


public:
    /*
     * exec
    */
    void update(ext::value& json);
    /*
     * exec
    */
    void exec(ext::value& json,uint16_t state);
    /*
     * destroy
    */
    void destroy();

};

}



#endif
