#ifndef PRO_SAMPLE_H
#define PRO_SAMPLE_H

#include "pro_global.h"

namespace pro
{

class sample : public ext::ui::sample
{
public:
    sample(pro::global& global,const ext::fs::path& path) : ext::ui::sample(global.workspace / path),
        zzz(global)
    {

    }


protected:
    /*
     * global
    */
    pro::global& zzz;

};

template<typename dialog_type=ext::ui::dialog>
class dialog_sample : public ext::ui::sample
{
public:
    dialog_sample(pro::global& global,const ext::fs::path& path,ext::text_view dialog_id = "main") : ext::ui::sample(global.workspace / path),
        zzz(global)
    {
        if(!dialog_id.empty()){
            dialog_ = ui.cast_id<dialog_type*>("main");
        }
    }


protected:
    /*
     * global
    */
    pro::global& zzz;
    /*
     * dialog
    */
    dialog_type* dialog_ = nullptr;


public:
    /*
     * dialog
    */
    dialog_type* dialog()
    {
        return dialog_;
    }

};


}

#endif
