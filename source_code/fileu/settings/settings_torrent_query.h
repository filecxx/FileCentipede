#ifndef PRO_SETTINGS_TORRENT_QUERY_H
#define PRO_SETTINGS_TORRENT_QUERY_H

#include "../pro_sample.h"

namespace pro::settings
{

class torrent_query : public pro::dialog_sample<pro::global>
{
public:
    torrent_query(pro::global& global);


protected:
    /*
     * init events
    */
    void init_events();


public:
    /*
     * exec
    */
    void exec();
};

}


#endif
