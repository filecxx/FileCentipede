#include "file_browser_super_cache.h"

namespace pro::file_browser
{

super_cache::super_cache(pro::file_browser::global& global) : pro::dialog_sample<pro::file_browser::global>(global,global->workspace / "ui/file_browser/super_cache.sml")
{
    dialog_->on_close([this](auto){
        delete this;
    });
}


///------------------------
void super_cache::exec()
{
    dialog_->show();
}


}