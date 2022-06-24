#ifndef PRO_FILE_BROWSER_GLOBAL_H
#define PRO_FILE_BROWSER_GLOBAL_H

#include "../pro_global.h"
#include "../pro_sample.h"
#include "file_browser_alert.h"

namespace pro::file_browser
{


class global
{
public:
    global(pro::global& ref) : zzz(ref)
    {

    }


public:
    pro::global& operator*()
    {
        return zzz;
    }
    pro::global* operator->()
    {
        return &zzz;
    }


public:
    pro::global& zzz;


public:
    /*
     * tasks alert
    */
    std::function<void(alert_type*)> tasks_alert;
    /*
     * current tid
    */
    std::atomic_int64_t current_tid = 0;


public:
    /*
     * invoke alert
    */
    template<typename T,typename...Arguments>
    void invoke_alert(Arguments&&...arguments)
    {
        T alert{std::forward<Arguments>(arguments)...};
        tasks_alert(&alert);
    }

};

}

#endif
