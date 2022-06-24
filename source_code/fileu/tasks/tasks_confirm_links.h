#ifndef PRO_TASKS_CONFIRM_LINKS_H
#define PRO_TASKS_CONFIRM_LINKS_H

#include "../pro_sample.h"

namespace pro::tasks
{

class confirm_links : public pro::dialog_sample<pro::global>
{
public:
    confirm_links(pro::global& global);


protected:
    /*
     * form
    */
    ext::ui::form form_;
    /*
     * table
    */
    ext::ui::table* table_ = nullptr;
    /*
     * proxy
    */
    ext::ui::combobox* proxy_combobox_ = nullptr;
    /*
     * filter
    */
    ext::ui::combobox* filter_rule_ = nullptr;
    /*
     * filter field
    */
    ext::ui::combobox* filter_field_ = nullptr;
    /*
     * filter text
    */
    ext::ui::line_edit* filter_text_ = nullptr;
    /*
     * urls
    */
    std::unordered_set<ext::text> urls_;


protected:
    /*
     * matches_filter
    */
    bool matches_filter(ext::text_view text);


protected:
    /*
     * init actions
    */
    void init_actions();
    /*
     * init form
    */
    void init_form();
    /*
     * init events
    */
    void init_events();


protected:
    /*
     * on filter
    */
    void on_filter();
    /*
     * on download
    */
    void on_download(bool immediately);


protected:
    /*
     * load catalogs
    */
    void load_catalogs();
    /*
     * load filters
    */
    void load_filters();
    /*
     * load proxies
    */
    void load_proxies();


public:
    /*
     * add
    */
    void add(ext::value& value);


public:
    /*
     * exec
    */
    void exec(ext::value& values);

};

}



#endif
