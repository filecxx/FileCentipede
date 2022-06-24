#ifndef PRO_TASKS_DOWNLOAD_COMPLETED_H
#define PRO_TASKS_DOWNLOAD_COMPLETED_H

#include "../pro_sample.h"

namespace pro::tasks
{

class transfer_completed : public pro::dialog_sample<pro::global,ext::ui::frameless_dialog>
{
public:
    transfer_completed(pro::global& global,std::int64_t id,ext::func_void<int64_t>&& callback);


public:
    ~transfer_completed();


protected:
    /*
     * form
    */
    ext::ui::form form_;
    /*
     * ids
    */
    std::int64_t id_;
    /*
     * callback
    */
    ext::func_void<int64_t> callback_;
    /*
     * timer
    */
    std::int64_t timer_ = 0;


protected:
    /*
     * filename
    */
    ext::text file_name_;
    /*
     * save path
    */
    ext::fs::path save_path_;


public:
    /*
     * exec
    */
    void exec(ext::value& values,const ext::text& error,std::uint32_t mode);


};

}



#endif
