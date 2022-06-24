#ifndef PRO_FILE_BROWSER_SUPER_CACHE_H
#define PRO_FILE_BROWSER_SUPER_CACHE_H

#include "../pro_sample.h"
#include "file_browser_global.h"

namespace pro::file_browser
{

class super_cache : public pro::dialog_sample<pro::file_browser::global>
{
public:
    super_cache(pro::file_browser::global& global);


public:
    /*
     * exec
    */
    void exec();


};

}


#endif
