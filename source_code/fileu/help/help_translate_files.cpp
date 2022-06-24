#include "help_translate_files.h"

namespace pro::help
{

translate_files::translate_files(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/help/translate_files.sml")
{
    dialog_->on_close([this](auto){
        delete this;
    });
    init_actions();
}


///--------------------------
void translate_files::init_actions()
{
    ui.on_click("#translate",[this](auto)
    {
        auto tab    = ui.cast<ext::ui::tab*>("#tab");
        auto index  = tab->currentIndex();
        auto result = false;

        if(index == 0){
            result = translate_file();
        }else if(index == 1){
            result = translate_directory();
        }else if(index == 2){
            result = translate_auto_directory();
        }
        if(result){
            ext::ui::alert("info","OK","file_translated"_lang).exec();
        }
    });
}


///--------------------------
void translate_files::translate_buffer(ext::ui::language& lang,std::string_view source,std::string& desc)
{
    auto index = size_t(0);

    while(index < source.size())
    {
        size_t pos    = 0;
        size_t endpos = 0;

        if((pos = source.find("${",index)) == std::string::npos || (endpos = source.find('}',pos)) == std::string::npos){
            desc.append(source.data() + index,source.size() - index);
            break;
        }
        if(index != pos){
            desc.append(source.data() + index,pos - index);
        }
        auto key  = std::string_view(source.data() + pos + 2,endpos - pos - 2);
        auto text = lang.get(key);

        if(text.empty()){
            desc.append(key.data(),key.size());
        }else{
            desc.append(text.data(),text.size());
        }
        index = endpos + 1;
    }
}

bool translate_files::translate_file(ext::ui::language& lang,const ext::fs::path& path,const ext::fs::path& save_path)
{
    std::string file_buffer;
    std::string file_buffer_desc;

    if(ext::cfile::read(path,file_buffer).value() != 0){
        ext::ui::alert("error","error","read_file_error"_lang).exec();
        return false;
    }
    translate_buffer(lang,file_buffer,file_buffer_desc);

    if(ext::cfile::write(save_path,"wb+",file_buffer_desc).value() != 0){
        ext::ui::alert("error","error","read_file_error"_lang).exec();
        return false;
    }
    return true;
}

bool translate_files::translate_directory(ext::ui::language& lang,const ext::fs::path& dir,const ext::fs::path& dir_save)
{
    for(auto& current : ext::fs::recursive_directory_iterator(dir,error_))
    {
        if(!current.is_regular_file(error_)){
            continue;
        }
        auto target = dir_save / ext::fs::relative(current.path(),dir,error_);

        if(!ext::fs::exists(target.parent_path(),error_) && !ext::fs::create_directories(target.parent_path(),error_)){
            ext::ui::alert("error","error"_lang,"create_directory_error"_lang).exec();
            return false;
        }
        if(!translate_file(lang,current.path(),target)){
            return false;
        }
    }
    return true;
}

bool translate_files::translate_file()
{
    auto form      = ext::ui::form(ui("#file_widget"));
    auto values    = form.values();
    auto language  = values["language"].text();
    auto path      = values["path"].text();
    auto save_path = values["save_path"].text();

    if(language.empty() || path.empty() || save_path.empty() || !ext::fs::exists(language,error_) || !ext::fs::exists(path,error_)){
        ext::ui::alert("error","error","file_path_error"_lang).exec();
        return true;
    }
    ext::ui::language lang;

    if(!lang.load_file(language)){
        ext::ui::alert("error","error","open_file_error"_lang).exec();
        return false;
    }
    return translate_file(lang,path,save_path);
}

bool translate_files::translate_directory()
{
    auto form      = ext::ui::form(ui("#directory_widget"));
    auto values    = form.values();
    auto language  = values["language"].text();
    auto path      = values["path"].text();
    auto save_path = values["save_path"].text();

    if(language.empty() || path.empty() || save_path.empty() || !ext::fs::exists(language,error_) || !ext::fs::is_directory(path,error_)){
        ext::ui::alert("error","error","file_path_error"_lang).exec();
        return false;
    }
    if(!ext::fs::is_directory(save_path,error_) && !ext::fs::create_directories(save_path,error_)){
        ext::ui::alert("error","error","invalid_directory"_lang).exec();
        return false;
    }
    ext::ui::language lang;
    std::string       file_buffer;
    std::string       file_buffer_desc;

    if(!lang.load_file(language)){
        ext::ui::alert("error","error","open_file_error"_lang).exec();
        return false;
    }
    return translate_directory(lang,path,save_path);
}

bool translate_files::translate_auto_directory()
{
    auto form      = ext::ui::form(ui("#auto_directory_widget"));
    auto values    = form.values();
    auto languages = values["languages"].text();
    auto path      = values["path"].text();

    if(languages.empty() || path.empty() || !ext::fs::exists(languages,error_) || !ext::fs::is_directory(path,error_)){
        ext::ui::alert("error","error","file_path_error"_lang).exec();
        return false;
    }
    for(auto& iter_lang : ext::fs::recursive_directory_iterator(ext::fs::path(languages),error_))
    {
        auto& path_lang = iter_lang.path();

        if(!iter_lang.is_regular_file(error_) || path_lang.extension().string() != ".lang"){
            continue;
        }
        ext::fs::path     dir_save = ext::fs::path(path).parent_path() / path_lang.filename().replace_extension();
        ext::ui::language lang;
        std::string       file_buffer;

        if(!lang.load_file(path_lang)){
            ext::ui::alert("error","error","open_file_error"_lang).exec();
            return false;
        }else if(ext::fs::exists(dir_save,error_)){
            if(!ext::fs::is_directory(dir_save,error_)){
                create_directory_error:
                ext::ui::alert("error","error","create_directory_error"_lang).exec();
                return false;
            }
        }else if(!ext::fs::create_directories(dir_save,error_)){
            goto create_directory_error;
        }
        if(!translate_directory(lang,path,dir_save)){
            return false;
        }
    }
    return true;
}


///--------------------------
void translate_files::exec()
{
    dialog_->show_active();
}

}