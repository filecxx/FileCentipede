#ifndef PRO_HELP_TRANSLATE_FILES_H
#define PRO_HELP_TRANSLATE_FILES_H

#include "../pro_sample.h"

namespace pro::help
{

class translate_files : public pro::dialog_sample<pro::global>
{
public:
    translate_files(pro::global& global);


protected:
    /*
     * error
    */
    std::error_code error_;


protected:
    /*
     * init actions
    */
    void init_actions();


protected:
    /*
     * translate buffer
    */
    void translate_buffer(ext::ui::language& lang,std::string_view source,std::string& desc);
    /*
     * translate file
    */
    bool translate_file(ext::ui::language& lang,const ext::fs::path& path,const ext::fs::path& save_path);
    /*
     * translate directory
    */
    bool translate_directory(ext::ui::language& lang,const ext::fs::path& dir,const ext::fs::path& dir_save);
    /*
     * translate file
    */
    bool translate_file();
    /*
     * translate directory
    */
    bool translate_directory();
    /*
     * translate auto directory
    */
    bool translate_auto_directory();


public:
    /*
     * exec
    */
    void exec();
};

}

#endif
