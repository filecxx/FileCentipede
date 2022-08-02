#ifndef PRO_DIALOG_CODE_H
#define PRO_DIALOG_CODE_H

#include "../pro_global.h"
#include "../pro_sample.h"

namespace pro::dialogs
{

class code : public pro::dialog_sample<pro::global>
{
    using callback_type = ext::func_void<ext::steady_time_point_t>;


public:
    constexpr static auto Activation_Interval = 2min;


public:
    code(pro::global& global);


protected:
    /*
     * callback
    */
    callback_type callback_;
    /*
     * form
    */
    ext::ui::form form_;


public:
    /*
     * exec
    */
    void exec(ext::value& values,callback_type&& callback);


};

}

#endif
