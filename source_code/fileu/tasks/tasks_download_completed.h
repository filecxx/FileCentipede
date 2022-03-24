#ifndef PRO_TASKS_DOWNLOAD_COMPLETED_H
#define PRO_TASKS_DOWNLOAD_COMPLETED_H

#include "../pro_sample.h"

namespace pro::tasks
{

class download_completed : public pro::dialog_sample<ext::ui::frameless_dialog>
{
public:
    download_completed(pro::global& global,std::int64_t id,ext::func_void<int64_t>&& callback);


public:
    ~download_completed();


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
    void exec(ext::value& values,const ext::text& error);


};

}



#endif
