#include "dialog_code.h"

namespace pro::dialogs
{

code::code(pro::global& global) : pro::dialog_sample<pro::global>(global,global->workspace / "ui/dialogs/code.sml")
{
    form_ = ext::ui::form(ui("#main"));
    dialog_->on_close([this](auto){
        callback_(ext::time::steady_now() + dialogs::code::Activation_Interval);
        delete this;
    });
    ext::crypto::bts1 bts1("activation");
    ext::local<16>    local;
    local << uint64_t(std::max<uint64_t>(ext::os::cpu::hash(),11101) * 10111);

    ui.set_value("#uid",bts1.encode(local.string_view()));
    ui.on_click("#get",[this](auto){
        ext::ui::file_dialog::open_url(ui.query_value("#addr").string());
    });
    ui.on_click("#later",[this](auto){
        dialog_->close();
    });
    ui.on_click("#ok",[this](auto)
    {
        auto value = form_.values();
        value["@"] = protocol::Message_Activation_Reset;
        zzz.send(value);
        dialog_->close();
    });
}

void code::exec(ext::value& values,callback_type&& callback)
{
    if(values.empty()){
        zzz.send({{"@",protocol::Message_Activation_Query}});
    }else{
        form_.values(values);
    }
    callback_ = std::move(callback);
    dialog_->show_active();
}


}