#include "tool_create_address.h"

namespace pro::tools
{

create_address::create_address(pro::global& global) : pro::dialog_sample<>(global,"ui/tools/create_address.sml")
{
    dialog_->on_close([this](auto e){
        dialog_result_->close();
        delete this;
    });
    form_config_ = ext::ui::form(ui("#config"));

    ui.cast(addresses_,"#addresses");
    ui.cast(tab_,"#tab");
    ui.cast(dialog_result_,"#result");

    init_actions();
}

create_address::~create_address()
{
    ext::ui::clear_timeout(timer_);
}


///--------------------------
void create_address::init_actions()
{
    addresses_->on_change([&](auto& str)
    {
        Ext_Return_If(timer_ != 0);

        timer_ = ext::ui::set_timeout([this]{
            timer_ = 0;
            analyze_addresses();
        },500ms);
    });

    ui.on_click("#copy_close",[this](auto){
        ext::ui::clipboard::text(ui.query_value("#result_text").text_view());
    });
    ui.on_click("#btn_create",[this](auto){
        create();
    });
}


///--------------------------
void create_address::analyze_addresses()
{
    auto text = addresses_->text();
    auto uri  = pro::uri();

    if(!uri.analyze(text,ext::Void) || uri.custom_protocol != pro::uri::Custom_None){
        type_ = protocol::Task_Types_Size;
    }else{
        type_ = uri.type;
    }
    if(type_ == protocol::Task_HTTP){
        tab_->setTabVisible(1,true);
        tab_->setTabVisible(2,false);
    }else if(type_ == protocol::Task_FTP){
        tab_->setTabVisible(2,true);
        tab_->setTabVisible(1,false);
    }else{
        tab_->setTabVisible(1,false);
        tab_->setTabVisible(2,false);
        type_ = protocol::Task_Types_Size;
    }
}

void create_address::create()
{
    ext::value configs;
    ext::text  text = "filec:";

    analyze_addresses();

    if(type_ == protocol::Task_HTTP){
        configs = ext::ui::form(ui("#http"),true).values();
    }else if(type_ == protocol::Task_FTP){
        configs = ext::ui::form(ui("#ftp"),true).values();
    }else{
        return;
    }
    configs.merge(form_config_.values());

    if(configs["page_url"].empty()){
        configs.erase("page_url");
    }
    if(configs["info_url"].empty()){
        configs.erase("info_url");
    }
    auto hide_origin = ui.query_value("#hide_origin_address").cast<bool>();
    auto immutable   = ui.query_value("#immutable").cast<bool>();
    auto silence     = ui.query_value("#silence_download").cast<bool>();

    if(!silence){
        text = "fileu:";
    }
    if(hide_origin || immutable)
    {
        uint8_t options = 0;

        if(hide_origin){
            options |= protocol::Encrypted_URI_Hide_Origin;
        }
        if(immutable){
            options |= protocol::Encrypted_URI_Immutable;
        }
        text += "1" + pro::uri::encode(configs.stringify(),options);
    }else{
        text += "0" + ext::crypto::base64::encode(configs.stringify());
    }
    ui.set_value("#result_text",text);
    dialog_result_->show_active();
}


///--------------------------
void create_address::exec()
{
    dialog_->show_active();
}


}