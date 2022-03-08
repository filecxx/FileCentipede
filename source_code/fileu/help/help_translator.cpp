#include "help_translator.h"

namespace pro::help
{

translator::translator(pro::global& global) : pro::dialog_sample(global,"ui/help/translator.sml")
{
    ui.cast(dialog_languages_,"#dialog_languages");
    ui.cast(languages_list_,"#languages_list");
    ui.cast(language_default_,"#languages_default");
    ui.cast(data_list_,"#data_list");

    title_ = ext::ui::text(dialog_->windowTitle());
    dialog_->on_close([this](auto){
        delete this;
    });
    init_actions();
    init_filter();
    init_languages_list();
    init_data_list();
}


///--------------------------
void translator::init_actions()
{
    ui.on_action("#act_select",[this](auto){
        select_language();
    });
    ui.on_action("#act_open",[this](auto){
        open_file();
    });
    ui.on_action("#act_save",[this](auto){
        save();
    });
    ui.on_action("#act_save_as",[this](auto){
        save_as();
    });
    ui.on_action("#act_import",[this](auto){
        import_file();
    });

    ui.on_action("#act_add",[this](auto){
        append_row();
    });
    ui.on_action("#act_remove",[this](auto){
        data_list_->remove_selected_rows();
    });
    ui.on_action("#act_copy",[this](auto){
        copy_selected_cells();
    });
    ui.on_action("#act_paste",[this](auto){

    });
    ui.on_action("#translate_files",[this](auto){
        (new pro::help::translate_files(zzz))->exec();
    });
}

void translator::init_filter()
{
    auto languages_filter = ui.cast<ext::ui::line_edit*>("#languages_filter");
    auto data_filter      = ui.cast<ext::ui::line_edit*>("#data_filter");
    auto data_filter_type = ui.cast<ext::ui::combobox*>("#data_filter_type");

    languages_filter->on_change([this](auto text){
        languages_list_->filter(ext::ui::text(text));
    });
    data_filter->on_change([this,data_filter_type](auto text){
        data_list_->filter(data_filter_type->currentIndex(),ext::ui::text(text));
    });
}

void translator::init_languages_list()
{
    languages_list_->on_double_click([this](auto)
    {
        Ext_Return_If(!languages_list_->has_selection());

        auto name         = languages_list_->current_text("name").text();
        auto default_lang = language_default_->value().text();

        data_list_->clear_rows();
        dialog_languages_->close();
        data_list_->clear_rows();
        file_path_ = (zzz.workspace / "lang" / (name + ".lang")).u8string();

        if(ext::fs::exists(file_path_)){
            load_file(file_path_);
        }
        if(!default_lang.empty()){
            load_default_lang(default_lang);
        }
        title(file_path_);
        grow_rows();
    });
}

void translator::init_data_list()
{
    grow_rows();

    data_list_->on_key_press([this](auto e)
    {
        if(e->matches(QKeySequence::Copy)){
            copy_selected_cells();
            return true;
        }else if(e->matches(QKeySequence::Delete)){
            data_list_->remove_selected_rows();
            return true;
        }
        return false;
    });
    data_list_->on_context_menu([this](auto)
    {
        Ext_Return_If(!data_list_->has_selection());
        data_list_->show_context_menu();
    });
    data_list_->on_edit([this](auto index,auto text)
    {
        if(index.row() < data_list_->row_count() - Auto_Grow_Row){
            return;
        }
        for(int i=0;i<Auto_Grow_Row - (data_list_->row_count() - (index.row() + 1));++i){
            append_row();
        }
    });
}


///--------------------------
bool translator::load_json_file(const ext::fs::path& path,const std::unordered_set<ext::text>& keys)
{
    ext::stream<> stream;
    std::error_code error = ext::cfile::read(path,stream);

    if(error){
        ext::ui::alert("error","error",error.message()).exec();
        return false;
    }
    ext::value values = ext::json::parse(stream.data(),stream.size());

    if(values.is_map())
    {
        shrink_rows();

        for(auto& iter : *values.cast_map())
        {
            auto key = iter.first.text();

            if(iter.second.is_map() && !keys.contains(key)){
                data_list_->append_row({key,iter.second.string_view("message")});
            }
        }
    }
    return true;
}

bool translator::load_lang_file(const ext::fs::path& path,const std::unordered_set<ext::text>& keys)
{
    ext::ui::language lang;

    if(!lang.load_file(path)){
        ext::ui::alert("error","error",ext::ui::lang("open_file_error")).exec();
        return false;
    }
    shrink_rows();

    lang.each([&](auto key,auto text)
    {
        if(!keys.contains(key)){
            append_row(key,text);
        }
        return false;
    });
    return true;
}

bool translator::load_file(const ext::fs::path& path,const std::unordered_set<ext::text>& keys)
{
    if(path.extension().u8string() == u8".json"){
        if(!load_json_file(path,keys)){
            return false;
        }
    }else if(!load_lang_file(path,keys)){
        return false;
    }
    grow_rows();

    return true;
}

bool translator::load_default_lang(const ext::text& name)
{
    auto file_path = zzz.workspace / "lang" / (name + ".lang");
    auto error     = std::error_code();

    if(ext::fs::exists(file_path,error)){
        import_file(ext::text(file_path.u8string()));
        return false;
    }
    return true;
}


///--------------------------
void translator::save_lang(const ext::fs::path& path)
{
    ext::text buffer;
    std::unordered_map<ext::text,ext::text> mapped;

    data_list_->each([&](auto index)
    {
        auto key  = boost::trim_copy(data_list_->text(index.row(),0));
        auto text = data_list_->text(index.row(),1);
        auto raw  = true;

        for(auto c : text)
        {
            if(c == '\r' || c == '\n' || c == '"'){
                raw = false;
                break;
            }
        }
        if(key.empty()){
            return false;
        }
        if(raw && !text.empty()){
            mapped[key] = text;
        }else{
            mapped[key] = ext::value_view(text).stringify();
        }
        return false;
    });
    for(auto& iter : mapped){
        buffer += iter.first + "=";
        buffer += iter.second + "\r\n";
    }
    save_file(path,std::move(buffer));
}

void translator::save_json(const ext::fs::path& path)
{
    ext::value values = ext::value::pairs_type();

    data_list_->each([&](auto index)
    {
        auto key  = boost::trim_copy(data_list_->text(index.row(),0));
        auto text = data_list_->text(index.row(),1);

        if(!key.empty()){
            values[key] = {
                {"message",text}
            };
        }
        return false;
    });
    save_file(path,values.stringify());
}

void translator::save_file(const ext::fs::path& path)
{
    auto type = path.extension().string();

    if(boost::to_lower_copy(path.extension().string()) == ".json"){
        save_json(path);
    }else{
        save_lang(path);
    }
}

void translator::save_file(const ext::fs::path& path,ext::text&& text)
{
    Ext_Return_If(text.empty());
    auto error = ext::cfile::write(path,"wb",text);

    if(error){
        ext::ui::alert("error","error",error.message()).exec();
    }
}


///--------------------------
void translator::shrink_rows()
{
    auto row_count = (int)data_list_->row_count();

    for(int i=row_count - 1;i>=row_count - Auto_Grow_Row;--i)
    {
        if(i < 0){
            continue;
        }
        auto empty = 0;

        for(int y=0;y<data_list_->column_count();++y){
            if(data_list_->text(i,y).empty()){
                empty++;
            }
        }
        if(empty == data_list_->column_count()){
            data_list_->remove_row(i);
        }
    }
}

void translator::grow_rows()
{
    auto blanks    = 0;
    auto row_count = (int)data_list_->row_count();

    for(int i=row_count - 1;i>=row_count - Auto_Grow_Row;--i)
    {
        if(i < 0){
            continue;
        }
        auto empty = 0;

        for(int y=0;y<data_list_->column_count();++y){
            if(data_list_->text(i,y).empty()){
                empty++;
            }
        }
        if(empty == data_list_->column_count()){
            blanks++;
        }
    }
    for(int i=blanks;i<Auto_Grow_Row;++i){
        append_row();
    }
}

void translator::copy_selected_cells()
{
    ext::text    content;
    std::int32_t column = -1;

    for(auto index : data_list_->selected_indexes())
    {
        auto text = data_list_->text(index);

        if(column == index.column()){
            content += "\r\n";
        }else if(index.column() > column){
            if(column != -1){
                content += "\t";
            }
        }else if(!content.empty()){
            content += "\r\n";
        }
        content += text;
        column = index.column();
    }
    ext::ui::clipboard::text(content);
}

void translator::append_row(ext::text_view key,ext::text_view text)
{
    auto row = data_list_->create_row(std::vector<ext::value_view>{key,text});
    data_list_->append_row(row);
}

void translator::title(ext::text_view text)
{
    dialog_->window_title(title_ + " " + text);
}

void translator::select_language()
{
    auto error     = std::error_code();
    auto languages = std::unordered_map<ext::text,ext::text>();

    exists_locales_.clear();
    languages_list_->clear_rows();
    language_default_->clear();
    language_default_->append("");

    for(auto& iter: std::filesystem::directory_iterator("lang/",error))
    {
        auto& path = iter.path();

        if(iter.is_regular_file() && path.extension() == ".lang"){
            exists_locales_.emplace(path.stem().u8string());
        }
    }
    ext::ui::language::locales([&](const auto& locale,const auto& language,const auto& country)
    {
        auto row = languages_list_->create_row({
            {"name",locale},
            {"language",language},
            {"country",country}
        });
        languages_list_->append_row(row);
        language_default_->append(locale);
        return false;
    });
    language_default_->value("en_US");
    dialog_languages_->exec();
}

void translator::open_file()
{
    auto text = ext::ui::file_dialog::open_file(ext::ui::lang("open_file"),"","*.lang *.json");

    if(!text.empty()){
        data_list_->clear_rows();
        load_file(file_path_ = text);
        title(text);
    }
}

void translator::save()
{
    if(file_path_.empty()){
        return save_as();
    }
    save_file(file_path_);
}

void translator::save_as()
{
    auto dir  = ext::text();
    auto name = ext::text();
    auto path = ext::fs::path(file_path_);

    if(!file_path_.empty()){
        name = path.filename().u8string();
        dir  = path.remove_filename().u8string();
    }
    auto text = ext::ui::file_dialog::save_file(ext::ui::lang("save_as"),name,"*.lang;;*.json");

    if(!text.empty()){
        save_file(text);
    }
}

void translator::import_file(ext::text_view path)
{
    std::unordered_set<ext::text> keys;

    data_list_->each([&](auto index)
    {
        auto text = boost::trim_copy(data_list_->text(index));

        if(!text.empty()){
            keys.emplace(text);
        }
        return false;
    });
    load_file(path,keys);
}

void translator::import_file()
{
    auto text = ext::ui::file_dialog::open_file(ext::ui::lang("import"),"","*.lang *.json");

    if(!text.empty()){
        import_file(text);
    }
}


///--------------------------
void translator::exec()
{
    dialog_->show_active();
}


}