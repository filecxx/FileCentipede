#ifndef PRO_FILE_BROWSER_EDIT_HOST_H
#define PRO_FILE_BROWSER_EDIT_HOST_H

#include "../pro_sample.h"
#include "file_browser_global.h"

namespace pro::file_browser
{

class edit_host : public pro::sample<pro::file_browser::global>
{
public:
    edit_host(pro::file_browser::global& global);


protected:
    /*
     * id
    */
    std::int64_t id_ = 0;
    /*
     * gid
    */
    std::int64_t gid_ = 0;
    /*
     * dialog
    */
    ext::ui::edit_dialog* dialog_ = nullptr;
    /*
     * tab
    */
    ext::ui::tab* tab_ = nullptr;
    /*
     * dialog
    */
    ext::ui::combobox* type_ = nullptr;
    /*
     * port
    */
    ext::ui::spinbox* port_ = nullptr;
    /*
     * form index
    */
    std::uint32_t form_index_ = 0;
    /*
     * forms
    */
    std::array<ext::ui::form,3> forms_ = {};


protected:
    /*
     * init dialog
    */
    void init_dialog();
    /*
     * init form
    */
    void init_form();
    /*
     * init form
    */
    void init_form(const ext::text& type);


public:
    /*
     * add
    */
    void add(std::int64_t gid);
    /*
     * edit
    */
    void edit(std::int64_t id,std::int64_t gid);

};

}

#endif
