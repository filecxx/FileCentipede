#ifndef PRO_DIALOG_ASK_PASS_H
#define PRO_DIALOG_ASK_PASS_H

#include "../pro_global.h"
#include "../pro_sample.h"

namespace pro::dialogs
{

class ask_pass : public pro::dialog_sample<pro::global>
{
public:
    ask_pass(pro::global& global);


protected:
    /*
     * form
    */
    ext::ui::form form_;
    /*
     * callback
    */
    std::function<void(ext::value)> callback_;
    /*
     * ok
    */
    ext::boolean_t ok_ = false;


public:
    /*
     * message
    */
    void message(ext::text_view text);
    /*
     * set values
    */
    void values(const ext::value& values);


public:
    /*
     * exec
    */
    void exec(ext::text_view address,std::function<void(ext::value)>&& callback);

};

}

#endif
