#include "view_statistics.h"

namespace pro::view
{

statistics::statistics(pro::global& global) : pro::dialog_sample(global,"ui/view/statistics.sml")
{
    form_ = ext::ui::form(ui("#main"));
    dialog_->on_close([this](auto){
        ext::ui::clear_timeout(timer_);
    });
}


///--------------------------
void statistics::on_timer()
{
    zzz.send({{"@",protocol::Message_Statistics}});

    timer_ = ext::ui::set_timeout([this]{
        on_timer();
    },1s);
}


///--------------------------
void statistics::exec()
{
    on_timer();
    dialog_->show_active();
}


}