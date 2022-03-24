#include "settings_torrent_query.h"

namespace pro::settings
{

torrent_query::torrent_query(pro::global& global) : pro::dialog_sample<>(global,"ui/settings/torrent_query.sml")
{
    dialog_->on_close([this](auto){

    });
    init_events();
}


///-------------------------
void torrent_query::init_events()
{

}


///-------------------------
void torrent_query::exec()
{
    dialog_->show();
}


}