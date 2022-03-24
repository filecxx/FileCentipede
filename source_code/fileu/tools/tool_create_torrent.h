#ifndef PRO_TOOL_CREATE_TORRENT_H
#define PRO_TOOL_CREATE_TORRENT_H

#include "../pro_sample.h"

namespace pro::tools
{

class create_torrent : public pro::dialog_sample<>
{
public:
    create_torrent(pro::global& global);


protected:
    /*
     * form
    */
    ext::ui::form form_;
    /*
     * xid
    */
    std::int64_t xid_ = zzz.xid++;


protected:
    /*
     * init values
    */
    void init_values();
    /*
     * init actions
    */
    void init_actions();
    /*
     * init catalogs
    */
    void init_catalogs();


protected:
    /*
     * create
    */
    void create();


public:
    /*
     * exec
    */
    void exec();

};

}



#endif
