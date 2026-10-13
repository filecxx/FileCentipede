Action#act_tasks_add_catalog
{
    text:"+"
}

///--------------------
Action#act_open
{
    icon:"icons/24/add_file.svg"
    text:"${open}"
    shortcut:"Ctrl+O"
}

Action#act_export_data
{
    icon:"icons/16/export.svg" 
    text:"${export_data}"
}

Action#act_import_data
{
    icon:"icons/16/import.svg" 
    text:"${import_data}"
}

Action#act_force_restart
{
    icon:"icons/16/refresh.svg"
    text:"${force_restart}"
}

Action#act_fully_shutdown
{
    icon:"icons/16/shutdown.svg"
    text:"${fully_shutdown}"
    trigger:$fully_shutdown()
}

Action#act_exit
{
    icon:"icons/16/exit.svg"
    text:"${exit}"
    shortcut:"Alt+F4"
    trigger:$exit()
}

Action#act_theme_toggle
{
    icon:"icons/16/theme.svg"
    text:"Theme"
    trigger:$open-local-url("${__workspace__}theme_switch.bat")
}


//-------------------
Action#act_task_add
{
    icon:"icons/24/add.svg"
    text:"${add}"
    shortcut:"Ctrl+N"
}

Action#act_task_add_directory
{
    icon:"icons/24/add.svg"
    text:"${add_directory}"
    shortcut:"Ctrl+D"
}

Action#act_task_add_stream
{
    icon:"icons/16/stream.svg"
    text:"${add_stream}"
    shortcut:"Ctrl+M"
}
/*
Action#act_task_upload
{
    icon:"icons/24/add.svg"
    text:"${upload}"
    shortcut:"Ctrl+U"
}
*/
Action#act_task_start
{
    icon:"icons/24/start.svg"
    text:"${start}"
}

Action#act_task_start_all
{
    icon:"icons/24/start.svg"
    text:"${start_all}"
    shortcut:"Ctrl+1"
}

Action#act_task_stop
{
    icon:"icons/24/stop.svg"
    text:"${stop}"
}

Action#act_task_stop_all
{
    icon:"icons/24/stop.svg",
    text:"${stop_all}"
    shortcut:"Ctrl+2"
}
    
Action#act_task_delete
{
    icon:"icons/16/delete.svg"
    text:"${delete}"
    shortcut:"Delete"
}

Action#act_task_delete_all
{
    icon:"icons/16/delete_all.svg"
    text:"${delete_all}"
}

Action#act_task_rename
{
    icon:"icons/16/rename.svg"
    text:"${rename}"
    shortcut:"F2"
}

Action#act_task_move
{
    icon:"icons/16/move.svg"
    text:"${move_to}..."
}
    
Action#act_task_open_file
{
    icon:"icons/16/run.svg"
    text:"${open_file}"
    shortcut:"Return"
}

Action#act_task_open_with
{
    icon:"icons/16/run.svg"
    text:"${open_with}..."
}

Action#act_task_open_directory
{
    icon:"icons/16/directory.svg"
    text:"${open_directory}"
}

Action#act_task_redownload
{
    icon:"icons/16/download.svg"
    text:"${redownload}"
}

Action#act_task_refresh_address
{
    icon:"icons/16/refresh.svg"
    text:"${refresh_address}"
}


Action#act_task_edit
{
    icon:"icons/16/edit.svg"
    text:"${edit_config}"
    shortcut:"ctrl+e"
}

Action#act_task_copy_name
{
    icon:"icons/16/copy.svg"
    text:"${copy_name}"
    shortcut:"ctrl+c"
}

Action#act_task_copy_address
{
    icon:"icons/16/copy.svg"
    text:"${copy_address}"
    shortcut:"ctrl+x"
}

Action#act_task_copy_page_url
{
    icon:"icons/16/copy.svg"
    text:"${copy_page_url}"
}

Action#act_task_copy_hash
{
    icon:"icons/16/copy.svg"
    text:"HASH"
}

Action#act_task_export_torrent
{
    icon:"icons/16/save_as.svg"
    text:"${export_torrent} / ${metadata}"
}

Action#act_task_calc_checksum
{
    icon:"icons/16/file.svg"
    text:"${checksum}"
}


//-------------------
Action#act_view_statusbar
{
    checkable:true
    checked:true
    text:"${statusbar}"
}

Action#act_view_nav
{
    checkable:true
    checked:true
    text:"${navigation}"
    //trigger:$visible{#tasks_nav}(...)
}

Action#act_view_catalogs
{
    checkable:true
    checked:true
    text:"${catalogs}"
    //trigger:$visible{#tasks_nav_catalogs_widget}(...)
}

Action#act_view_desktop_shortcuts
{
    icon:"icons/16/none.svg" 
    text:"${desktop_shortcuts}"
}

Action#act_view_statistics
{
    icon:"icons/16/statistics.svg" 
    text:"${statistics}"
    shortcut:"Ctrl+I"
}
/*
Action#act_view_speed_monitor
{
    icon:"icons/16/speed_monitor.svg" 
    text:"${speed_monitor}"
}
*/

//-------------------
Action#act_tool_http
{
    icon:"icons/16/web.svg" 
    text:"${http_tool}"
    shortcut:"Shift+H"
}
  
Action#act_tool_uri
{
    icon:"icons/16/none.svg"
    text:"${uri_tool}"
    shortcut:"Shift+U"
}

Action#act_tool_base64
{
    icon:"icons/16/none.svg"
    text:"Base64"
    shortcut:"Shift+B"
    trigger:$open-window("ui/tools/base64.sml","#main")
}

Action#act_tool_regex
{
    icon:"icons/16/none.svg"
    text:"${regex}"
    trigger:$open-window("ui/tools/regex.sml","#main")
}

Action#act_tool_create_address
{
    icon:"icons/16/none.svg"
    text:"${create_address}"
}

Action#act_tool_create_torrent
{
    icon:"icons/16/none.svg"
    text:"${create_torrent}"
    shortcut:"Shift+C"
} 

Action#act_tool_torrent2magnet
{
    icon:"icons/16/magnet.svg" 
    text:"${torrent_to_magnet}"
    trigger:$open-window("ui/tools/torrent2magnet.sml","#main",true)
}
   
Action#act_tool_magnet2torrent
{
    icon:"icons/16/torrent.svg" 
    text:"${magnet_to_torrent}"
    trigger:$open-window("ui/tools/magnet2torrent.sml","#main",true)
}
/*
Action#act_tool_subtitles_search
{
    icon:"icons/16/subtitles.svg"
    text:"${subtitles_search}"
}
*/
Action#act_tool_browsers
{
    icon:"icons/24/web.svg"
    text:"${browsers}"
    trigger:$open-window("ui/tools/browsers.sml","#main")
}

Action#act_tool_file_merge
{
    icon:"icons/16/file.svg"
    text:"${file_merge}"
    shortcut:"Shift+M"
}

Action#act_tool_checksum
{
    icon:"icons/16/file.svg"
    text:"${checksum}"
}

/*
Action#act_tool_file_erase
{
    text:"${erase_file}"
}

Action#act_tool_file_cleaner
{
    icon:"icons/16/clean.svg"
    text:"${file_cleaner}"
}
*/


//-------------------
Action#act_setting_shortcuts
{
    icon:"icons/16/file.svg"
    text:"${language}"
}

Action#act_settings
{
    icon:"icons/16/setting.svg" 
    text:"${settings}"
    shortcut:"Ctrl+Shift+S"
}

Action#act_setting_torrent_query
{
    icon:"icons/16/torrent.svg" 
    text:"${torrent_query}"
}

Action#act_setting_tracker
{
    icon:"icons/16/tracker.svg" 
    text:"BT ${tracker}"
}

Action#act_setting_filter
{
    icon:"icons/16/filter.svg" 
    text:"${filter}"
}

Action#act_setting_proxy
{
    icon:"icons/16/proxy.svg" 
    text:"${proxy}"
    shortcut:"Ctrl+Shift+P"
}

Action#act_setting_site_rules
{
    icon:"icons/16/favorites.svg" 
    text:"${site_rules}"
}


//-----------------
Action#act_remote_add
{
    icon:"icons/24/add.svg"
    text:"${add_host}"
    trigger:$open-window("ui/remote/edit_host.sml","#main")
}

Action#act_remote_manage
{
    icon:"icons/16/all.svg"
    text:"${manage_hosts}"
}


//-----------------
Action#act_help_update
{
    icon:"icons/16/update.svg" 
    text:"${update}"
    shortcut:"Ctrl+Alt+U"
}

Action#act_help_install
{
    icon:"icons/16/home.svg" 
    text:"${install}"
}

Action#act_help_uninstall
{
    icon:"icons/16/delete_all.svg" 
    text:"${uninstall}"
}

Action#act_help_troubleshooting
{
    icon:"icons/16/troubleshooting.svg"
    text:"${troubleshooting}"
}

Action#act_help_translate
{
    icon:"icons/24/translate.svg" 
    text:"${translate}"
    shortcut:"Ctrl+T"
}

Action#act_help_about
{
    icon:"icons/16/about.svg" 
    text:"${about}"
    trigger:$open-window("ui/help/about.sml","#main")
}

Action#act_help_activation
{
    icon:"icons/16/paste.svg"
    text:"${activation_code}"
}
