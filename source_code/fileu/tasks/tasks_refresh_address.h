#ifndef PRO_TASKS_REFRESH_ADDRESS_H
#define PRO_TASKS_REFRESH_ADDRESS_H

#include "../pro_sample.h"

namespace pro::tasks
{

class refresh_address : public pro::dialog_sample<>
{
public:
    refresh_address(pro::global& global);


public:
    ~refresh_address();


public:
    /*
     * address
    */
    static ext::text address(pro::global& zzz,int64_t id,uint16_t type,ext::text_view page_url,ext::text_view resid);


public:
    /*
     * exec
    */
    void exec(int64_t id,uint16_t type,ext::text_view page_url,ext::text_view resid);

};

}


#endif
