#include "file_browser_edit_host.h"

namespace pro::file_browser
{

edit_host::edit_host(pro::file_browser::global& global) : pro::sample<pro::file_browser::global>(global,global->workspace / "ui/file_browser/edit_host.sml")
{
    ui.cast(type_,"#protocol");
    ui.cast(port_,"#port");
    ui.cast(dialog_,"#main");
    ui.cast(tab_,"#tab");

    init_dialog();
}


///=========================
void edit_host::init_dialog()
{
    dialog_->on_add([this](auto&& values)
    {
        auto& form = forms_[form_index_];
        auto  type = protocol::filesystem_type(values.text_view("protocol"));

        values.merge({{"@",protocol::Message_FS_Host_Add},{"gid",gid_},{"type",type}});

        if(form){
            values.merge(form.values());
        }
        zzz->send(values);
    });
    dialog_->on_edit([this](auto&& values,auto)
    {
        auto& form = forms_[form_index_];
        auto  type = protocol::filesystem_type(values.text_view("protocol"));

        values.merge({{"@",protocol::Message_FS_Host_Edit},{"gid",gid_},{"type",type},{"id",id_}});

        if(form){
            values.merge(form.values());
        }
        zzz->send(values);
    });
}

void edit_host::init_form()
{
    auto proxy_combobox = ui.cast_id<ext::ui::combobox*>("proxy");
    auto on_type_change = [this](auto)
    {
        auto type = type_->value().text();
        auto port = ext::uri::default_port(type);

        init_form(type);
        port_->value(port);
    };
    if(zzz->proxies.is_map() && proxy_combobox)
    {
        for(auto& iter : *zzz->proxies.cast_map()){
            proxy_combobox->append(iter.first.text(),iter.first.text());
        }
    }
    type_->on_change(on_type_change);
    on_type_change(0);
}

void edit_host::init_form(const ext::text& type)
{
    std::int32_t index = 0;
    ext::text    name;

    if(type == "http" || type == "https"){
        index = 1;
        name  = "http";
    }else if(type == "webdav" || type == "webdavs"){
        index = 2;
        name  = "webdav";
    }
    if((form_index_ = index) != 0 && !forms_[index])
    {
        ui.import(tab_->item_data(index).string());
        auto layout = ui('#' + name);
        forms_[index] = ext::ui::form(layout);
        tab_->layout(index,layout->object);

        if(id_ != 0){
            forms_[index].values(zzz->nfs_hosts[id_]);
        }
    }
    for(auto i=1;i<forms_.size();++i){
        tab_->visible(i,i == index);
    }
}


///=========================
void edit_host::add(std::int64_t gid)
{
    gid_ = gid;
    init_form();
    dialog_->default_values(ext::value(zzz->configs["nfs"]));
    dialog_->add();

    delete this;
}

void edit_host::edit(std::int64_t id,std::int64_t gid)
{
    id_  = id;
    gid_ = gid;
    init_form();
    dialog_->edit(zzz->nfs_hosts[id],nullptr);

    delete this;
}


}