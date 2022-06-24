#ifndef PRO_VIEW_STATISTICS_H
#define PRO_VIEW_STATISTICS_H

#include "../pro_sample.h"

namespace pro::view
{

class statistics : public pro::dialog_sample<pro::global>
{
public:
    statistics(pro::global& global);


protected:
    /*
     * form
    */
    ext::ui::form form_;
    /*
     * timer
    */
    std::int64_t timer_ = 0;


protected:
    /*
     * on timer
    */
    void on_timer();


public:
    /*
     * exec
    */
    void exec();

};

}

#endif
