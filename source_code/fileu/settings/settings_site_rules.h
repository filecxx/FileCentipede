#ifndef PRO_SETTINGS_SITE_RULES_H
#define PRO_SETTINGS_SITE_RULES_H

#include "../pro_sample.h"

namespace pro::settings
{

class site_rules_edit : public pro::dialog_sample<pro::global>
{
public:
    site_rules_edit(pro::global& global);


protected:
    /*
     * id
    */
    std::int64_t id_ = 0;
    /*
     * current
    */
    std::int32_t current_ = 0;
    /*
     * forms
    */
    std::array<ext::ui::form,protocol::Task_Types_Size> forms_;
    /*
     * protocol
    */
    ext::ui::combobox* protocol_;
    /*
     * config
    */
    ext::ui::group_box* config_;
    /*
     * values
    */
    ext::value values_;


protected:
    /*
     * on change
    */
    void on_change();
    /*
     * on save
    */
    void on_save();


public:
    /*
     * add
    */
    void add();
    /*
     * edit
    */
    void edit(int64_t id,ext::value& values);

};


class site_rules : public pro::dialog_sample<pro::global>
{
public:
    site_rules(pro::global& global);


protected:
    /*
     * table
    */
    ext::ui::table* table_ = nullptr;


protected:
    /*
     * init events
    */
    void init_events();
    /*
     * init messages
    */
    void init_messages();


protected:
    /*
     * on transfer add
    */
    void on_transfer_add();
    /*
     * on transfer edit
    */
    void on_transfer_edit();
    /*
     * on transfer remove
    */
    void on_transfer_remove();
    /*
     * on transfer copy
    */
    void on_transfer_copy();
    /*
     * on transfer paste
    */
    void on_transfer_paste();
    /*
     * on transfer import
    */
    void on_transfer_import();
    /*
     * on transfer export
    */
    void on_transfer_export();


public:
    /*
     * exec
    */
    void exec();

};

}

#endif
