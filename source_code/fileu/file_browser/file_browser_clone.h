#ifndef PRO_FILE_BROWSER_CLONE_H
#define PRO_FILE_BROWSER_CLONE_H

#include "file_browser_global.h"

namespace pro::file_browser
{

class clone : public pro::dialog_sample<pro::file_browser::global>
{
public:
    clone(pro::file_browser::global& global);


public:
    /*
     * exec
    */
    void exec();

};

}

#endif
