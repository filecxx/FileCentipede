#include "tasks_refresh_address.h"

namespace pro::tasks
{

refresh_address::refresh_address(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/tasks/refresh_address.sml")
{
    dialog_->on_close([this](auto){
        delete this;
    });

}

refresh_address::~refresh_address()
{

}


///--------------------------
ext::text refresh_address::address(pro::global& zzz,int64_t id,uint16_t type,ext::text_view page_url,ext::text_view resid)
{
    ext::local<8_KB> address;
    address << "http://127.0.0.1:" << std::to_string(zzz.configs["service"].uint16("port"))
            << "/?browser_act=refresh_address&id=" << std::to_string(id)
            << "&type=" << std::to_string(type)
            << "&resid=" << resid
            << "&url=" << ext::crypto::base64::encode(page_url);

    return address.string_view();
}


///--------------------------
void refresh_address::exec(int64_t id,uint16_t type,ext::text_view page_url,ext::text_view resid)
{
    auto addr = address(zzz,id,type,page_url,resid);
    auto form = ext::ui::form(ui("#main"));

    form.values({{"address",addr},{"page_url",page_url},{"resid",ext::convert::uri::decode(resid)}});

    ui.cast<ext::ui::checkbox*>("#no_refresh_address_dialog")->on_toggle([this](auto val){
        zzz->setting("no_refresh_address_dialog",val);
    });
    dialog_->show_active();
}


}