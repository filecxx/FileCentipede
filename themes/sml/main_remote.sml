/*
 * sml is an experimental language, grammars are not yet set in stone, some of grammars may change in the future.
*/

@import "actions.sml"


///--------------------
.vboxlayout
{
    type:VBoxLayout
    margin:1
}

.vboxlayout2
{
    type:VBoxLayout
    margin:1
    spacing:0
}


///--------------------
Menu#tasks_context_menu
{
    ${#act_task_start}
    ${#act_task_stop}
    ---
    ${#act_task_rename}
    ${#act_task_delete}
    
    ---
    ${#act_task_redownload}
    ${#act_task_edit}

    ---
    Menu#task_set_catalog
    {
        icon:"icons/16/directory.svg"
        text:"${catalog}"
 
    }
    {
        text:"${copy}"
        icon:"icons/16/copy.svg"
        
        ${#act_task_copy_name}
        ${#act_task_copy_address}
        //${#act_task_copy_page_url}
        ${#act_task_copy_hash}
    }
    
}

Widget#nav
{
    layout:${.vboxlayout}
  
    Widget#nav_tasks_status_panel
    {
        layout:${.vboxlayout}
        HBoxLayout
        {
            Label{
                class:list_title
                text:"${all_groups}"
            }
        }
        List#nav_tasks_list
        {
            class:flat
            item-height:36
            icon-size:24
            selected:0
            item-type:ListItem
            item-style:extend
            size-adjust:content
            {
                data:"all"
                icon:"icons/24/all.svg"
                text:"${all}"
            }
            {
                data:"transferring"
                text:"${transferring}"
                icon:"icons/24/download.svg"
            }
            {
                data:"stopped"
                text:"${stopped}"
                icon:"icons/24/stop.svg"
            }
            {
                data:"completed"
                text:"${completed}"
                icon:"icons/24/success.svg"
            }
            {
                data:"seeding"
                text:"${seeding}"
                icon:"icons/24/seeding.svg"
            }
            {
                data:"failed"
                text:"${failed}"
                icon:"icons/24/failed.svg"
            }
            {
                data:"queuing"
                text:"${queuing}"
                icon:"icons/24/queuing.svg"
            }
            {
                data:"delay"
                icon:"icons/24/delay.svg"
                text:"${download_later}"
            }
        }
    }
    Widget#nav_tasks_catalogs_panel
    {
        layout:${.vboxlayout}
        HBoxLayout
        {
            Label{
                class:list_title
                text:"${catalogs}"
            }
            ToolButton{
                action:${#act_tasks_add_catalog}
            }
        }
        List#nav_tasks_catalogs
        {
            class:flat
            item-height:28
            icon-size:24
            selected:0
            selection:rows
            {
                text:"${all}"
                icon:"icons/24/all.svg"
            }
        }
    }
}


FileSystem#tasks_list
{
    sortable:true
    stripe:true
    editable:false
    wordwrap:false
    checkable:child
    checked:-1
    selection:rows
    icon-size:24
    columns-height:26
    columns:{
        {name:file_name,text:"${name}",width:320}
        {name:file_size,text:"${size}",width:70,align:right,format:bytes}
        {
            name:progress
            width:100
            text:"${progress}"
            cell:Progress
            align:center
            attr:{class:lite,min:0,max:100}
        }
        {
            name:state
            text:"${state}"
            width:120
        }
        {
            name:download_speed
            text:"${download_speed}"
            width:110
            align:right
            format:"bytes/s"
        }
        {
            name:upload_speed,
            text:"${upload_speed}",
            width:110,
            align:right,
            format:"bytes/s"
        }
        {
            name:peers
            text:"${peers}"
            width:60
            align:right
        }
        {
            name:seeds
            text:"${seeds}"
            width:60
            align:right
        }
        {
            name:time_left
            text:"${time_left}"
            width:80
            align:right
            format:"duration=d"
        }
        {
            name:time_create
            text:"${time_create}"
            align:right
            width:130
            format:datetime
            sort:desc
        }
        {
            name:catalog
            text:"${catalog}"
        }
    }
    context-menu:${#tasks_context_menu}
}

ToolBar#tasks_toolbar
{
    icon-size:24
    button-style:TextBesideIcon

    {
        button-style:TextBesideIcon
        action:${#act_task_add} 
        
        ${#act_task_add}
        ${#act_task_add_directory}
        ${#act_task_add_stream}
        //${#act_task_upload}
    }
    ${#act_open}

    ---
    {
        button-style:TextBesideIcon
        action:${#act_task_start} 

        ${#act_task_start} 
        ${#act_task_start_all}
    }
    {
        button-style:TextBesideIcon
        action:${#act_task_stop}
        
        ${#act_task_stop}
        ${#act_task_stop_all}
    }
    {
        button-style:TextBesideIcon
        action:${#act_task_delete}
        
        ${#act_task_delete}
        ${#act_task_delete_all}
    }
    {
        button-style:TextBesideIcon
        popup-mode:instant
        icon:"icons/24/all.svg"
  
        ${#act_task_rename}
        
        ---
        ${#act_task_redownload}
        ${#act_task_edit}
    }
 
}
    
    
ComboBox#tasks_filter{
    placeholder:"${tasks_filter}"
    editable:true
}



///--------------------
#tasks
{
    text:"${file_transfer}"
    icon:"icons/16/file.svg"
    layout:${.vboxlayout2}
    
    HBoxLayout
    {
        ${#tasks_toolbar}
        ${#tasks_filter}
    }
    
    Splitter#tasks_splitter
    {
        type:vertical
        stretch-factor:"1,0"
        
        ${#tasks_list}
        
        Widget#tasks_details
        {
            layout:{
                type:VBoxLayout
                margin:0
            }
        }
    }
}


///--------------------
Window#main
{
    title:"${software_name_} ${__version__}"
    icon:"icons/icon.png"
    layout:VBoxLayout
    w:1024
    h:768
    droppable:true
    menubar:
    {
        icon-size:24
        {
            text:"${file_s}"
            
            ${#act_open}
            ---
            ${#act_task_add}
            ${#act_task_add_directory}
            ${#act_task_add_stream}
            //${#act_task_upload}
            ---
            ${#act_exit}
        }
        {
            text:"${view_s}"
            
            ${#act_view_statusbar}
            ${#act_view_nav}
            ${#act_view_catalogs}
            ---

            ${#act_view_statistics}
        }
        {
            text:"${settings_s}"
            
            ${#act_setting_tracker}
            ${#act_setting_filter}
            ${#act_setting_proxy}
            ${#act_setting_site_rules}
            //${#act_setting_torrent_query}
            ---
            ${#act_settings}
        }
        {
            text:"${help_s}"
            
            ${#act_help_update}
            ${#act_help_activation}
            
            ---
            ${#act_help_troubleshooting}
            ${#act_help_about}
        }
    }
    statusbar:
    {
        message-timeout:5000
        
        Label{"Ping: "} 
        NetworkSignal#rpc_signal{
            value:-1
        }
        Label#rpc_ping{
            class:separated_label
            selectable:true
            text:"${unknown}"
        }
        
        
        Label{"P2P ${connections}:"} Label#p2p_conns{
            class:separated_label
            selectable:true
            text:0
        }
   
        Img#torrent_DHT_warning{
            visible:false
            fixed-width:16
            fixed-height:16
        }
        Label{"BT DHT:"} 
        Label#torrent_DHT_peers{
            class:separated_label
            selectable:true
            text:0
        }
   
        
        ToolButton#global_speed_download{
            min-width:120
            button-style:TextBesideIcon
            icon:"icons/16/download.svg"
            text:" 0.00 B/s"
            css:"color:#56b8ec"
        }
        ToolButton#global_speed_upload{
            min-width:120
            button-style:TextBesideIcon
            icon:"icons/16/upload.svg"
            text:" 0.00 B/s"
            css:"color:#ef8a8a"
        }
    }
    Splitter#main_splitter
    {
        type:horizontal
        stretch-factor:"0,1"
        sizes:"170,1000"
        
        ${#nav}
       
        Tab#main_tab
        {
            icon-size:16
            
            ${#tasks}
        }
    }
  
}
