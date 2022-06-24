#ifndef PRO_SAMPLE_H
#define PRO_SAMPLE_H

#include "pro_global.h"

namespace pro
{

template<typename global_type = pro::global>
class sample : public ext::ui::sample
{
public:
    sample(global_type& global,const ext::fs::path& path) : ext::ui::sample(global->workspace / path),
        zzz(global)
    {

    }


protected:
    /*
     * global
    */
    global_type& zzz;

};

template<typename global_type,typename dialog_type=ext::ui::dialog>
class dialog_sample : public ext::ui::sample
{
public:
    dialog_sample(global_type& global,const ext::fs::path& path,ext::text_view dialog_id = "main") : ext::ui::sample(global->workspace / path),
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
    global_type& zzz;
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
