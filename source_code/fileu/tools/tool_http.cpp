#include "tool_http.h"

namespace pro::tools
{

http::http(pro::global& global) : pro::dialog_sample<pro::global>(global,"ui/tools/http.sml")
{
    form_response_ = ext::ui::form(ui("#response_headers_widget"));
    empty_values_  = form_response_.values();

    dialog_->on_close([this](auto e){
        if(abort();--refcount_ == 0){
            delete this;
        }
    });
    ui.set_value("#request_headers","Accept: */*\r\nAccept-Encoding: gzip, deflate\r\nUser-Agent: " + ext::text(ext::http::Default_User_Agent));
    init_events();
}


///--------------------------
void http::init_events()
{
    ui.on_click("#btn_request",[this](auto){
        request();
    });
    ui.on_click("#btn_abort",[this](auto){
        abort();
    });
    ui.on_click("#search_btn",[this](auto){
        search();
    });
}

///===================================
void http::on_response(ext::http::client::response& response)
{
    response_values_["response_code"] = response.code;

    ext::text headers;
    ext::text cookies;

    for(auto iter : response.headers)
    {
        headers.append(iter.first.string_view());
        headers.append(": ");
        headers.append(iter.second.string_view());
        headers.append("\r\n");
    }
    for(auto iter : response.cookies){
        cookies.append(iter.string_view());
        cookies.append("\r\n");
    }
    response_values_["response_headers"] = std::move(headers);
    response_values_["response_cookies"] = std::move(cookies);
}

void http::on_done(const std::error_code& error)
{
    response_values_["response_status"] = error.message();
    form_response_.values(response_values_);

    QByteArray bytes(QByteArray::fromStdString(response_data_));
    ui.cast_id<ext::ui::text_edit*>("response_data")->setPlainText(QTextCodec::codecForHtml(bytes)->toUnicode(bytes));
    ui("#btn_request")->object.enable(true);

    response_values_.clear();

    if(--refcount_ == 0){
        delete this;
    }
}


///===================================
void http::load_request_values(request_values_t& request)
{
    request.method       = ui.query_value("#request_method").text();
    request.url          = format_url(ui.query_value("#request_url").text());
    request.headers      = ui.query_value("#request_headers").text();
    request.content_type = ui.query_value("#request_content_type").text();
    request.data         = ui.query_value("#request_data").text();
    request.tpl_name     = ui.query_value("#tpl_name").text();
    request.tpl_prefix   = ui.query_value("#tpl_prefix").text();
    request.tpl_text     = ui.query_value("#tpl_text").text();

    if(!request.tpl_name.empty()){
        request.tpl_text = ext::convert::uri::encode(request.tpl_prefix + request.tpl_text);
        boost::replace_all(request.url,request.tpl_name,request.tpl_text);
        boost::replace_all(request.data,request.tpl_name,request.tpl_text);
    }
    request.headers = format_request_string(request.headers);
}


///===================================
ext::text http::format_request_string(const ext::text& headers)
{
    ext::text result = boost::trim_copy(headers);

    while(!result.empty())
    {
        char c = result.back();

        if(c != '\r' && c != '\n'){
            break;
        }
        result.pop_back();
    }
    if(!result.empty()){
        return result + "\r\n";
    }
    return result;
}

ext::text http::format_url(const ext::text& url)
{
    ext::text result = url;

    if((url.size() >= 7 && boost::to_lower_copy(url.substr(0,7)) != "http://") && (url.size() >= 8 && boost::to_lower_copy(url.substr(0,8)) != "https://")){
        result = ext::text("http://") + url;
        ui.set_value("#request_url",result);
    }
    return result;
}


///--------------------------
void http::search()
{
    auto edit    = ui.cast<ext::ui::text_edit*>("#response_data");
    auto keyword = ext::ui::string(ui.query_value("#search_keyword").text());

    QList<QTextEdit::ExtraSelection> extraSelections;
    QColor color = QColor(Qt::gray).lighter(130);

    if(!keyword.isEmpty())
    {
        edit->moveCursor(QTextCursor::Start);

        while(edit->find(keyword))
        {
            QTextEdit::ExtraSelection extra;
            extra.format.setBackground(color);

            extra.cursor = edit->textCursor();
            extraSelections.append(extra);
        }
        ui.set_value("#search_found","found: " + std::to_string(extraSelections.size()));
    }
    edit->setExtraSelections(extraSelections);
}

void http::request()
{
    request_values_t values;
    load_request_values(values);

    response_data_.clear();
    form_response_.values(empty_values_);
    ui.set_value("#response_data","");
    ui("#btn_request")->object.enable(false);
    refcount_++;

    connection_ = ext::http::connect(*zzz.tcp_connector(),values.url,[this,values](auto error,auto connection)
    {
        if(error){
            return ext::ui::post([this,error]{
                on_done(error);
            });
        }
        auto request = connection->new_request(values.method,values.url);
        request->keep_alive                  = false;
        request->use_default_accept          = false;
        request->use_default_accept_encoding = false;
        request->use_default_user_agent      = false;
        request->on_response([this](auto& response){
            on_response(response);
            return std::error_code();
        });
        request->add_header(values.headers);
        request->on_data([this](uint8_t* data,uint32_t length,uint64_t received){
            if(received > 4_MB){
                return ext::errc::No_Space;
            }
            response_data_.append((const char*)data,length);
            return ext::errc::OK;
        });
        connection->on_close([this](auto& error){
            ext::ui::post([this,error]{
                on_done(error);
            });
        });
        connection->request(request,values.data,values.content_type);
    },10000);
}

void http::abort()
{
    if(connection_){
        connection_->close();
    }
}


///--------------------------
void http::exec()
{
    dialog_->show();
}


}