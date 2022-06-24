#include "dialog_ask_pass.h"

namespace pro::dialogs
{

ask_pass::ask_pass(pro::global& global) : pro::dialog_sample<pro::global>(global,global->workspace / "ui/dialogs/ask_pass.sml")
{
    form_ = ext::ui::form(ui("#main"));
    dialog_->on_close([this](auto)
    {
        ext::value value;

        if(ok_){
            value = form_.values();
        }
        callback_(std::move(value));
        delete this;
    });
    ui.on_click("#ok",[this](auto){
        ok_ = true;
        dialog_->close();
    });
}


///--------------------------------
void ask_pass::message(ext::text_view text)
{
    ui.cast<ext::ui::label*>("#message")->text(text);
}

void ask_pass::values(const ext::value& values)
{
    form_.values(values);
}


///--------------------------------
void ask_pass::exec(ext::text_view address,std::function<void(ext::value)>&& callback)
{
    if(!address.empty()){
        ui.cast<ext::ui::line_view*>("#address")->text(address);
    }
    callback_ = std::move(callback);
    dialog_->show();
}


}