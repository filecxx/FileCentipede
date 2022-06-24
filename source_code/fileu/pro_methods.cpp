#include "pro_methods.h"

namespace pro
{

static pro::methods* self;

methods::methods(pro::global& global,ext::ui::model& instance) : zzz(global),ui(instance)
{
    self = this;
}


///--------------------------
uint16_t methods::message_type(ext::text_view type)
{
    static std::unordered_map<ext::text_view,uint16_t> message_types;

    if(message_types.empty()){
        message_types = protocol::to_mapped_task_types();
    }
    if(auto iter = message_types.find(type);iter != message_types.end()){
        return iter->second;
    }
    return protocol::Message_Types_Size;
}


///--------------------------
void methods::filec_version(ext::ui::arguments& arguments)
{
    arguments << pro::Version;
}

void methods::filec_lang(ext::ui::arguments& arguments)
{
    if(arguments.argc == 1 && arguments[0].is_string()){
        arguments << ext::ui::lang(arguments[0].text_view());
    }else{
        arguments << ext::text_view();
    }
}

void methods::filec_interval(ext::ui::arguments& arguments)
{
    Ext_Return_If(arguments.argc != 2);

    if(arguments[0].is_string() && ext::ui::callable(arguments[1])){
        self->interval_handlers_.emplace(arguments[0].text(),arguments[1]);
    }
}

void methods::filec_submit(ext::ui::arguments& arguments)
{
    Ext_Return_If(arguments.argc < 2 || !arguments[0].is_string() || !arguments[1].is_reference());

    if(auto type = message_type(arguments[0].text_view());type != protocol::Message_Types_Size)
    {
        auto form   = ext::ui::form(arguments.node(1));
        auto values = form.values(); //windows bug
        values = form.values();

        if(arguments.argc >= 3 && arguments[2].is_pointer()){
            ext::value extra;
            ext::ui::methods::to_value(arguments.node(2),extra);
            values.merge(std::move(extra));
        }
        values["@"] = type;

        self->zzz.send(values);
    }
}

void methods::filec_form(ext::ui::arguments& arguments)
{
    ext::ui::form form(arguments.stack.scope);

    if(form && arguments.argc > 0 && arguments[0].is_map()){
        form.values(arguments[0]);
    }
}

void methods::filec_send(ext::ui::arguments& arguments)
{
    Ext_Return_If(arguments.argc == 0 || !arguments[0].is_string());

    if(auto at = message_type(arguments[0].text_view());at == protocol::Message_Types_Size){
        ext::debug <<= "filec_send error parameter";
    }else if(arguments.argc == 1){
        self->zzz.send({{"@",at}});
    }else if(arguments.argc == 2 && arguments[1].is_caller())
    {
        if(ext::ui::methods::call(arguments.caller(1));arguments.result().is_map()){
            ext::value json(std::move(arguments.result()));
            json["@"] = at;
            self->zzz.send(std::move(json));
        }
    }else if(arguments.argc == 2 && arguments[1].is_pointer()){
        ext::value json({{"@",at}});
        ext::ui::methods::to_value(arguments.node(1),json);

        self->zzz.send(std::move(json));
    }
}

void methods::filec_on(ext::ui::arguments& arguments)
{
    if(arguments.argc == 1 && arguments[0].is_pointer())
    {
        for(auto& pair : arguments.node(0)->pairs)
        {
            auto type = message_type(pair.first);

            if(ext::ui::callable(pair.second) && type < protocol::Message_Types_Size){
                self->zzz.ipc_handlers_[type] = pair.second;
            }
        }
    }else if(arguments.argc == 2 && arguments[0].is_string() && ext::ui::callable(arguments[1]))
    {
        if(auto type = message_type(arguments[0].text_view());type < protocol::Message_Types_Size){
            self->zzz.ipc_handlers_[type] = arguments[1];
        }
    }
}

void methods::filec_launch(ext::ui::arguments& arguments)
{
    self->launch_filec();
}

void methods::filec_user_agents(ext::ui::arguments& arguments)
{
    arguments << self->zzz.configs["http_user_agents"]["text"].text_view();
}

void methods::filec_paths(ext::ui::arguments& arguments)
{
    ext::text text;

    if(self->zzz.paths.is_array())
    {
        for(auto& iter : *self->zzz.paths.cast_array()){
            text += iter.text("path") + "\r\n";
        }
    }
    arguments << text;
}

void methods::filter_rules(ext::ui::arguments& arguments)
{

}

void methods::exit(ext::ui::arguments& arguments)
{
    if(self->tray_initialized_){
        self->ui.cast_id<ext::ui::tray*>("tray")->hide();
    }
    self->zzz.shutdown();
    std::exit(1);
}


///--------------------------
void methods::launch_filec()
{
    bool elevatable = false;

    doom::privilege::launch(pro::service_path(zzz.workspace),{"__elevating__"},elevatable,true);

    if(!elevatable){
        ext::ui::alert("info","error","launch_filec_error1_"_lang).exec();
    }
}

void methods::init()
{
    ext::ui::methods::bind(
    {
        {"filec-version",&filec_version},
        {"filec-lang",&filec_lang},
        {"filec-interval",&filec_interval},
        {"filec-submit",&filec_submit},
        {"filec-form",&filec_form},
        {"filec-send",&filec_send},
        {"filec-on",&filec_on},
        {"filec-launch",&filec_launch},
        {"filec-user-agents",&filec_user_agents},
        {"filec-paths",&filec_paths},
        {"filec-filter-rules",&filter_rules},
        {"exit",&exit}
    });
}


}