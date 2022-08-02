#include "main_window.h"

/*
 * check is upgrading
*/
void check_is_upgrading()
{
    if(ext::named_mutex(ext::os::cpu::hash(),pro::Upgrade_Mutex).locked()){
        std::exit(0);
    }
}

/*
 * forward to client
*/
int forward_to_client(const ext::value& list)
{
    ext::ipcx::send(pro::Client_Bin,pro::Version_IPC,list);
    std::exit(0);

    return 0;
}

/*
 * try launch tool
*/
void try_launch_tool(pro::main_window& window,const ext::fs::path& path)
{
    ext::text file_path = (window.zzz.workspace / path).u8string();
    std::initializer_list<ext::value_view> args{file_path,"#main"};
    ext::ui::arguments arguments(ext::ui::shared_stack,args);
    ext::ui::methods::invokers_global["open-window"](arguments);

}

/*
 * try launch plugin
*/
void try_launch_plugin(pro::main_window& window,int argc,char** argv)
{
    if(argc == 0){
        std::cerr << "error parameters" << std::endl;
        std::exit(0);
    }else{
        try_launch_tool(window,"plugins/"_text + ext::text_view(argv[0]) + "/ui/main.sml");
    }
}


/*
 * try command main
*/
void try_command_line(pro::main_window& window,ext::text_view text,int argc,char** argv)
{
    if(text == "--http_tool"){
        (new pro::tools::http(window.zzz))->exec();
    }else if(text == "--uri_tool"){
        try_launch_tool(window,"ui/tools/uri.sml");
    }else if(text == "--base64"){
        try_launch_tool(window,"ui/tools/base64.sml");
    }else if(text == "--regex"){
        try_launch_tool(window,"ui/tools/regex.sml");
    }else if(text == "--create_address"){
        (new pro::tools::create_address(window.zzz))->exec();
    }else if(text == "--create_torrent"){

    }else if(text == "--torrent_to_magnet"){

    }else if(text == "--magnet_to_torrent"){

    }else if(text == "--checksum"){
        (new pro::tools::checksum(window.zzz))->exec(argc - 2,argv + 2);
    }else if(text == "--file_merge"){
        (new pro::tools::file_merge(window.zzz))->exec();
    }else if(text == "--translate"){
        (new pro::help::translator(window.zzz))->exec();
    }else if(text == "--software_release"){
        (new pro::tools::software_release(window.zzz))->exec();
    }else if(text == "--p"){
        try_launch_plugin(window,argc - 2,argv + 2);
    }else{
        std::exit(0);
    }
}


/*
 * main
*/
int main(int argc,char *argv[])
{
    boost::nowide::args _(argc,argv);
    ext::ui::application app(argc,argv,"platforms");

    app.workspace(app.variables.workspace.remove_filename());
    app.style("fusion");
    app.load_css(app.variables.workspace / "ui/css/default.css");

    pro::main_window window(app);

    if(argc >= 2)
    {
        ext::text_view text(argv[1]);

        if(text == "__upgrading__"){
            try_launch_tool(window,"ui/upgrading.sml");
            return app.exec();
        }else if(text == "__upgrading_error__"){
            ext::ui::alert("error","error"_lang,"upgrading_error_message_"_lang).exec();
            std::exit(1);
        }else if(text.starts_with("--")){
            check_is_upgrading();
            try_command_line(window,text,argc,argv);
            return app.exec();
        }
    }
    check_is_upgrading();

    std::int32_t   error    = pro::errors::OK;
    ext::boolean_t locked   = window.zzz.named_mutex.lock();
    ext::boolean_t add_task = false;
    ext::boolean_t booting  = false;

    if(argc > 1)
    {
        ext::text text(argv[1]);

        if(text == "boot"){
            booting = true;
        }else if(text == "message" && argc == 3){
            error = std::atoi(argv[2]);
        }else if(argc == 2){
            if(!locked){
                return forward_to_client({{"@",pro::protocol::Message_UI},{"type","add_task"},{"uri",text}});
            }
            add_task = true;
        }
    }
    if(error != pro::errors::OK){
        ext::ui::alert("error","error"_lang,pro::global::error_text(error)).exec();
    }
    if(!locked){
        return forward_to_client({{"@",pro::protocol::Message_UI},{"type","active"}});
    }
    if(window.zzz.settings.uint8("installed") < 1){
        (new pro::help::install(window.zzz))->exec(true);
    }else if(window.create(booting);add_task){
        window.add_task(argv[1],true);
    }
    return app.exec();
}