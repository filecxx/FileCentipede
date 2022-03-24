#include "help_uninstall.h"

namespace pro::help
{

uninstall::uninstall(pro::global& global) : pro::dialog_sample<>(global,"ui/help/uninstall.sml")
{
    ui.cast(path_,"#path");
    path_->text(ext::text(zzz.workspace.u8string()));
    dialog_->on_close([this](auto){
        delete this;
    });
    init_actions();

}


///--------------------------
void uninstall::init_actions()
{
    ui.on_click("#btn_uninstall",[this](auto){
        start_uninstall();
    });
}


///--------------------------
void uninstall::uninstall_failed(bool elevatable)
{
    ext::ui::alert("error","error",ext::ui::lang("uninstall_failed")).exec();
}

void uninstall::start_uninstall()
{
    auto input = ui.cast<ext::ui::input_dialog*>("#uninstall_confirm_input");

    if(input->exec() != 0 && input->value() == "123")
    {
        ui("#btn_uninstall")->object.enable(false);

        thread_ = std::jthread([this]
        {
            bool elevatable = false;
            int  ret        = doom::privilege::launch(zzz.workspace.executable(pro::Service_Bin),{"uninstall"},elevatable,true);

            ext::ui::post([this,elevatable]() mutable{
                uninstall_failed(elevatable);
                ui("#btn_uninstall")->object.enable(true);
                //std::exit(1);
            });
        });
    }
}


///--------------------------
void uninstall::exec()
{
    dialog_->exec();
}


}