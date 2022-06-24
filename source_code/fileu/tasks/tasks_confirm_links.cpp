#include "tasks_confirm_links.h"

namespace pro::tasks
{

confirm_links::confirm_links(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/tasks/confirm_links.sml")
{
    init_actions();
    init_form();
    init_events();

    dialog_->on_close([this](auto){
        delete this;
    });
}


///---------------------------
bool confirm_links::matches_filter(ext::text_view text)
{
    std::vector<std::regex> rules;
    ext::parser::split_lines(filter_rule_->value().text_view(),[&](auto str,auto index){
        try{
            rules.emplace_back(std::string(str),std::regex_constants::ECMAScript | std::regex_constants::optimize);
        }catch(...){}

        return false;
    });
    for(auto& rule : rules)
    {
        try{
            if(std::regex_match(text.begin(),text.end(),rule)){
                return true;
            }
        }catch(...){}
    }
    auto filter_text = boost::to_lower_copy(filter_text_->text());

    return !filter_text.empty() && text.find(filter_text) == std::string::npos;
}


///---------------------------
void confirm_links::init_actions()
{
    ui.on_action("#act_delete_selected",[this]{
        table_->remove_selected_rows();
    });
    ui.on_action("#act_check_on",[this]
    {
        for(auto row : table_->selected_rows()){
            table_->item(row)->checked(2);
        }
    });
    ui.on_action("#act_uncheck_off",[this]{
        for(auto row : table_->selected_rows()){
            table_->item(row)->checked(0);
        }
    });
    ui.on_action("#act_check_all",[this]{
        table_->each([&](auto index){
            table_->item(index)->checked(2);
            return false;
        });
    });
    ui.on_action("#act_uncheck_all",[this]{
        table_->each([&](auto index){
            table_->item(index)->checked(0);
            return false;
        });
    });
}

void confirm_links::init_form()
{
    form_ = ext::ui::form(ui.root());
    ui.cast(table_,"#table");
    ui.cast(filter_rule_,"#filter");
    ui.cast(filter_field_,"#filter_field");
    ui.cast(filter_text_,"#filter_text");
    ui.cast(proxy_combobox_,"#proxy");
}

void confirm_links::init_events()
{
    ui.on_click("#download_later",[this](auto){
        on_download(false);
    });
    ui.on_click("#download_now",[this](auto){
        on_download(true);
    });
    table_->on_context_menu([this](auto){
        table_->show_context_menu();
    });
}


///---------------------------
void confirm_links::on_filter()
{
    table_->each([&](auto index)
    {
        ext::text    text;
        std::int32_t field = filter_field_->value().int32();

        switch(field)
        {
        case 0:
            text = table_->item(index)->text();
            break;
        case 1:
            text = table_->sibling_text(index,"file_name");
            break;
        }
        table_->row_visible(index,!matches_filter(boost::to_lower_copy(text)));
        return false;
    });
}

void confirm_links::on_download(bool immediately)
{
    ext::value config = form_.values();

    table_->each([&](auto index)
    {
        auto item = table_->item(index);

        if(!table_->row_visible(index) || item->checked() != 2){
            return false;
        }
        ext::value value;
        value["@"]               = protocol::Message_Task_Add;
        value["without_confirm"] = true;
        value["file_name"]       = table_->sibling_text(index,"file_name");
        value["uri"]             = table_->sibling_text(index,"url");

        if(!immediately){
            value["later"] = true;
        }
        zzz->send(ext::value::merge(ext::value(config),std::move(value)).stringify());
        return false;
    });
    dialog_->close();
}


///---------------------------
void confirm_links::load_catalogs()
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

void confirm_links::load_filters()
{
    auto& files = zzz->configs["filters"]["torrent_files"];

    if(files.is_array())
    {
        for(auto& item : *files.cast_array()){
            filter_rule_->append(item.text_view("name"),item.text_view("rule"));
        }
    }
    filter_rule_->on_change([this](auto str){
        on_filter();
    });
    filter_field_->on_change([this](auto str){
        on_filter();
    });
    filter_text_->on_change([this](auto text){
        on_filter();
    });
}

void confirm_links::load_proxies()
{
    if(zzz->proxies.is_map() && proxy_combobox_)
    {
        auto current = zzz->configs["network"].text("proxy");

        for(auto& iter : *zzz->proxies.cast_map())
        {
            proxy_combobox_->append(iter.first.text(),iter.first.text());

            if(iter.first.text() == current){
                proxy_combobox_->setCurrentIndex(proxy_combobox_->count() - 1);
            }
        }
    }
}


///---------------------------
void confirm_links::add(ext::value& value)
{
    auto name = value["name"].text();
    auto url  = value["url"].text();
    auto addr = ext::uri::address();

    if(urls_.contains(url) || !ext::uri::parse(url,addr)){
        return;
    }
    auto filename = ext::text(addr.path().name());

    if(filename.empty())
    {
        if((filename = name).empty()){
            filename = "index";
        }
        filename += ".html";
    }
    value["file_name"] = (filename = ext::fs::optimize_file_name(filename));

    auto row  = table_->create_row(value);
    auto item = (ext::ui::standard_item*)row[0];

    item->icon(zzz->icons_mime.mime(filename,24));
    item->checkable(true);
    item->checked(2);
    table_->append_row(row);
    urls_.emplace(url);
}


///---------------------------
void confirm_links::exec(ext::value& values)
{
    auto page_url = values["page_url"].text();

    for(auto& iter : *values["links"].cast_array()){
        add(iter);
    }
    form_.values(ext::value::merge(zzz->task_config(protocol::Task_HTTP),ext::value(values)));

    load_catalogs();
    load_filters();
    load_proxies();

    dialog_->show_active();
}

}