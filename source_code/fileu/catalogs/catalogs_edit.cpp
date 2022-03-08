#include "catalogs_edit.h"

namespace pro::catalogs
{

edit::edit(pro::global& global) : ext::ui::sample(global.workspace / "ui/catalogs/edit.sml"),zzz(global)
{
    dialog_ = ui.cast_id<ext::ui::edit_dialog*>("main");
    dialog_->on_add([this](auto&& values){
        values.merge({{"@",protocol::Message_Catalog_Add}});
        zzz.send(values);
    });
    dialog_->on_edit([this](auto&& values,auto name){
        values.merge({{"@",protocol::Message_Catalog_Update},{"old_name",name}});
        zzz.send(values);
    });
}


///=========================
void edit::exec()
{
    dialog_->form().values({{"path",zzz.configs["general"]["default_save_path"]}});
    dialog_->add();
    delete this;
}

void edit::exec(ext::text_view name)
{
    auto values = zzz.catalogs.get(name);
    dialog_->edit(ext::value::merge({{"name",name}},values),name);
    delete this;
}

}