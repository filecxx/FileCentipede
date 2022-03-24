#ifndef PRO_TOOL_HTTP_H
#define PRO_TOOL_HTTP_H

#include <extcpp/net>
#include "../pro_sample.h"

namespace pro::tools
{

class http : public pro::dialog_sample<>
{
    struct request_values_t
    {
        ext::text method;
        ext::text url;
        ext::text headers;
        ext::text content_type;
        ext::text data;
        ext::text tpl_name;
        ext::text tpl_prefix;
        ext::text tpl_text;
    };


public:
    http(pro::global& global);


protected:
    /*
     * response form
    */
    ext::ui::form form_response_;
    /*
     * empty values
    */
    ext::value empty_values_;
    /*
     * response values
    */
    ext::value response_values_;
    /*
     * response data
    */
    ext::text response_data_;
    /*
     * connection
    */
    std::shared_ptr<ext::http::client::connection> connection_;
    /*
     * refcount
    */
    std::atomic_uint32_t refcount_ = 1;


protected:
    /*
     * init events
    */
    void init_events();


protected:
    /*
     * on response
    */
    void on_response(ext::http::client::response& response);
    /*
     * on done
    */
    void on_done(const std::error_code& error);


protected:
    /*
     * load request values
    */
    void load_request_values(request_values_t& request_values);


protected:
    /*
     * format request string
    */
    ext::text format_request_string(const ext::text& headers);
    /*
     * format request string
    */
    ext::text format_url(const ext::text& url);


protected:
    /*
     * search
    */
    void search();
    /*
     * request
    */
    void request();
    /*
     * abort
    */
    void abort();


public:
    /*
     * exec
    */
    void exec();

};

}

#endif
