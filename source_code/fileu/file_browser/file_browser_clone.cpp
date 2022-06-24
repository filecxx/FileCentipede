#include "file_browser_clone.h"

namespace pro::file_browser
{

clone::clone(pro::file_browser::global& global) : pro::dialog_sample<pro::file_browser::global>(global,global->workspace / "ui/file_browser/clone.sml")
{
    dialog_->on_close([this](auto){
        delete this;
    });
}


///------------------------
void clone::exec()
{
    dialog_->show();
}


}