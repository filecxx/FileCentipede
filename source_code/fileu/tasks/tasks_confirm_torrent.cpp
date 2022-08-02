#include "tasks_confirm_torrent.h"

namespace pro::tasks
{

confirm_torrent::confirm_torrent(pro::global& global,ext::value& json,ext::func<void(int64_t,bool)>&& callback) :
    pro::dialog_sample<pro::global>(global,"ui/tasks/confirm_torrent.sml"),
    callback_(std::move(callback))
{
    ui.cast(loader_,"#loading");
    ui.cast(filter_,"#filter");
    ui.cast(filter_size_type_,"#filter_size_type");
    ui.cast(filter_size_,"#filter_size");
    ui.cast(filter_size_unit_,"#filter_size_unit");
    ui.cast(files_,"#files");

    files_->on_context_menu([this](auto){
        files_->show_context_menu();
    });
    dialog_->on_close([this](auto)
    {
        if(!destroying_)
        {
            if(!confirmed_){
                zzz->send({{"@",protocol::Message_Task_Remove},{"type",protocol::Task_Torrent},{"id",id_},{"delete_file",true}});
            }
            callback_(id_,confirmed_);
        }
        delete this;
    });
    files_->icons(&zzz->icons_mime);

    init_actions();
}


///--------------------------
void confirm_torrent::init_actions()
{
    ui.on_action("#act_check_on",[this]
    {
        for(auto node : files_->selected_files()){
            files_->checked(2,node,true);
        }
    });
    ui.on_action("#act_uncheck_off",[this]{
        for(auto node : files_->selected_files()){
            files_->checked(0,node,true);
        }
    });
    ui.on_action("#act_check_all",[this]{
        files_->each([&](auto node){
            files_->checked(2,node,true);
            return false;
        },true);
    });
    ui.on_action("#act_uncheck_all",[this]{
        files_->each([&](auto node){
            files_->checked(0,node,true);
            return false;
        },true);
    });
}


///--------------------------
void confirm_torrent::on_ok()
{
    auto values = ext::value({{"@",protocol::Message_Task_Confirm},{"type",protocol::Task_Torrent},{"id",id_}});

    values.merge(form_attributes_.values());
    values.merge(form_information_.values());

    confirmed_ = true;
    zzz->send(values);

    dialog_->close();
}

void confirm_torrent::on_checked(ext::ui::filesystem::node_type* node)
{
    if(node->value.type == ext::fs::file_type::directory || node->value.checked == 1){
        return;
    }
    zzz->send({
        {"@",protocol::Message_Task_Files_Enable},
        {"type",protocol::Task_Torrent},
        {"id",id_},
        {"idx",node->value("idx").int32()},
        {"enable",node->value.checked == 2}
    });
}

void confirm_torrent::on_filter()
{
    std::vector<std::regex> rules;
    ext::parser::split_lines(filter_->value().text_view(),[&](auto text,auto index){
        try{
            rules.emplace_back(std::string(text),std::regex_constants::ECMAScript | std::regex_constants::optimize | std::regex_constants::icase);
        }catch(...){}

        return false;
    });
    files_->each([&](auto node)
    {
        if(rules.empty()){
            files_->checked(2,node,true);
            return false;
        }else if(node->value.type == ext::fs::file_type::directory){
            return false;
        }
        for(auto& rule : rules){
            try{
                files_->checked(std::regex_match(node->name.begin(),node->name.end(),rule) ? 0 : 2,node,true);
            }catch(...){}
        }
        return false;
    },true);
}

void confirm_torrent::on_filter_size(uint16_t type,size_t size)
{
    std::int64_t                    current_size = 0;
    ext::ui::filesystem::node_type* current_node = nullptr;

    for(auto i=0;i<filter_size_unit_->currentIndex();++i){
        size *= 1024;
    }
    files_->each([&](auto node)
    {
        if(node->value.type == ext::fs::file_type::directory){
            return false;
        }
        if(auto file_size = node->value("file_size").int64();type == 1){
            if(file_size >= current_size){
                if(current_node){
                    files_->checked(0,current_node,true);
                }
                current_size = file_size;
                current_node = node;
            }else{
                files_->checked(0,node,true);
            }
        }else if(type == 2){
            if(file_size < current_size || current_size == 0){
                if(current_node){
                    files_->checked(0,current_node,true);
                }
                current_size = file_size;
                current_node = node;
            }else{
                files_->checked(0,node,true);
            }
        }else if(type == 3){
            files_->checked(file_size > size ? 2 : 0,node,true);
        }else if(type == 4){
            files_->checked(file_size < size ? 2 : 0,node,true);
        }
        return false;
    },true);

    if(current_node){
        files_->checked(2,current_node,true);
    }
}


///--------------------------
void confirm_torrent::load_catalogs()
{
    Ext_Return_If(!zzz->catalogs.is_map());

    auto combobox = ui.cast_id<ext::ui::combobox*>("catalog");

    for(auto& iter : *zzz->catalogs.cast_map()){
        combobox->append(iter.first.text(),iter.first.text());
    }
    combobox->on_index_change([this,combobox](auto index)
    {
        ext::text path;

        if(index == 0){
            path = zzz->configs["general"].text_view("default_save_path");
        }else if(auto name = combobox->item_text(index);zzz->catalogs.contains(name)){
            path = zzz->catalogs[name].text_view("path");
        }
        ui.set_value("#save_path",path);
    });
}

void confirm_torrent::load_filters()
{
    auto& torrent_files = zzz->configs["filters"]["torrent_files"];

    if(torrent_files.is_array())
    {
        for(auto& item : *torrent_files.cast_array()){
            filter_->append(item.text_view("name"),item.text_view("rule"));
        }
    }
    filter_size_type_->setEnabled(true);
}


///--------------------------
void confirm_torrent::exec(ext::value& json,uint16_t state)
{
    id_               = json.int64("id");
    form_attributes_  = ext::ui::form(ui("#attrbutes"));
    form_information_ = ext::ui::form(ui("#information"));

    filter_->on_change([this](auto str){
        on_filter();
    });
    files_->on_checked([this](auto node){
        on_checked(node);
    });
    auto filter_size_change = [this](auto){
        auto size_type = filter_size_type_->currentIndex();
        filter_size_->setEnabled(size_type >= 3);
        on_filter_size(size_type,filter_size_->value());
    };
    filter_size_type_->on_index_change(filter_size_change);
    filter_size_->on_change(filter_size_change);
    filter_size_unit_->on_change(filter_size_change);
    files_->on_insert([this](auto node,auto auto_created)
    {
        if(auto_created){
            node->value.type = ext::fs::file_type::directory;
        }
    });
    ui.on_click("#without_confirm",[this](auto val){
        auto& config = zzz->configs["torrent_task"];
        config["without_confirm"] = val;
        zzz->send({{"@",protocol::Message_Config_Update},{"name","torrent_task"},{"config",config}});
    });
    ui.on_click("#ok",[this](auto){
        on_ok();
    });
    dialog_->show_active();
    load_catalogs();
    update(json,state);
}

void confirm_torrent::update(ext::value& json,uint16_t state)
{
    Ext_Return_If(meta_loaded_);

    auto name_edit = form_attributes_["file_name"]->object.cast<ext::ui::line_edit*>();

    if(name_edit->text().empty()){
        name_edit->text(json.text_view("file_name"));
    }
    if(!attr_loaded_){
        form_attributes_.values(json);
        attr_loaded_ = true;
    }
    if(json.get("torrent_ready") == true)
    {
        if(state > protocol::State_Downloading_Metadata)
        {
            loader_->hide();

            if(json.uint32("files") == 0)
            {
                auto name = json.text("torrent_name");
                files_->checkable(false);
                files_->add_file({{"file_name",name},{"file_size",json.get("file_size")}},name);
            }
            meta_loaded_ = true;
        }
        form_information_.values(json);
    }
}

void confirm_torrent::update_files(ext::value& json,uint32_t total,uint32_t offset,uint32_t size)
{
    auto& files = json["items"];

    if(files.empty() || !files.is_array() || files_loaded_){
        return;
    }
    for(auto& item : *files.cast_array())
    {
        auto priority = item.uint16("priority");
        auto node     = files_->update_file(std::move(item),item.text_view("file_name"),item.text_view("path"),true);

        files_->type(ext::fs::file_type::regular,node);
        files_->checked(priority != 0 ? 2 : 0,node);
    }
    if(offset + size == total)
    {
        files_->recurse<task_directory_t>([](auto node,auto& dir){
            dir.checked[node->value.checked]++;
        },[this](auto node,auto& dir){
            files_->checked(files_->parent_check_state(dir.checked),node);
        });
        files_loaded_ = true;
        load_filters();
    }
}

void confirm_torrent::destroy()
{
    destroying_ = true;
    dialog_->close();
}

}