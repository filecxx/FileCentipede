#ifndef PRO_HELP_TRANSLATOR_H
#define PRO_HELP_TRANSLATOR_H

#include "help_translate_files.h"

namespace pro::help
{

class translator : public pro::dialog_sample
{
    constexpr static auto Auto_Grow_Row = 2;


public:
    translator(pro::global& global);


protected:
    /*
     * default title
    */
    ext::text title_;
    /*
     * file path
    */
    ext::text file_path_;
    /*
     * dialog languages
    */
    ext::ui::dialog* dialog_languages_ = nullptr;
    /*
     * languages list
    */
    ext::ui::table* languages_list_ = nullptr;
    /*
     * default language
    */
    ext::ui::combobox* language_default_ = nullptr;
    /*
     * data list
    */
    ext::ui::table* data_list_ = nullptr;


protected:
    /*
     * exists locales
    */
    std::unordered_set<ext::text> exists_locales_;


protected:
    /*
     * init actions
    */
    void init_actions();
    /*
     * init filter
    */
    void init_filter();
    /*
     * init languages list
    */
    void init_languages_list();
    /*
     * init data list
    */
    void init_data_list();


protected:
    /*
     * load json file
    */
    bool load_json_file(const ext::fs::path& path,const std::unordered_set<ext::text>& keys);
    /*
     * load lang file
    */
    bool load_lang_file(const ext::fs::path& path,const std::unordered_set<ext::text>& keys);
    /*
     * load file
    */
    bool load_file(const ext::fs::path& path,const std::unordered_set<ext::text>& keys = {});
    /*
     * load default lang
    */
    bool load_default_lang(const ext::text& name);


protected:
    /*
     * save lang
    */
    void save_lang(const ext::fs::path& path);
    /*
     * save json
    */
    void save_json(const ext::fs::path& path);
    /*
     * save file
    */
    void save_file(const ext::fs::path& path);
    /*
     * save file
    */
    void save_file(const ext::fs::path& path,ext::text&& text);


protected:
    /*
     * shrink rows
    */
    void shrink_rows();
    /*
     * grow rows
    */
    void grow_rows();
    /*
     * copy selected cells
    */
    void copy_selected_cells();
    /*
     * append row
    */
    void append_row(ext::text_view key = {},ext::text_view text = {});
    /*
     * set title
    */
    void title(ext::text_view text);
    /*
     * select language
    */
    void select_language();
    /*
     * open file
    */
    void open_file();
    /*
     * save
    */
    void save();
    /*
     * save as
    */
    void save_as();
    /*
     * import
    */
    void import_file(ext::text_view path);
    /*
     * import
    */
    void import_file();


public:
    /*
     * exec
    */
    void exec();
};

}

#endif
