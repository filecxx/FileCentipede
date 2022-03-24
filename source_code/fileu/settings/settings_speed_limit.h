#ifndef PRO_SETTINGS_SPEED_LIMIT_H
#define PRO_SETTINGS_SPEED_LIMIT_H

#include "../pro_sample.h"

namespace pro::settings
{

class speed_limit : public pro::dialog_sample<>
{
public:
    speed_limit(pro::global& global,const ext::text& type);


protected:
    /*
     * type
    */
    ext::text type_;
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
     * start timer
    */
    void start_timer();


public:
    /*
     * exec
    */
    void exec();


};

}

#endif
