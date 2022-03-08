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

class dialog_sample : public ext::ui::sample
{
public:
    dialog_sample(pro::global& global,const ext::fs::path& path,ext::text_view dialog_id = "main") : ext::ui::sample(global.workspace / path),
        zzz(global)
    {
        if(!dialog_id.empty()){
            dialog_ = ui.cast_id<ext::ui::dialog*>("main");
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
    ext::ui::dialog* dialog_ = nullptr;


public:
    /*
     * dialog
    */
    ext::ui::dialog* dialog()
    {
        return dialog_;
    }

};


}

#endif
