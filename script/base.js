(function()
{
    var decode_email = function()
    {
        //var arr     = [110,112,100,47,102,100,111,102,103,109,106,98,110,65,122,118,104,117,106,116,116,102,109,102,110,98,111];
        var arr = [110, 112, 100, 47, 121, 121, 100, 102, 109, 106, 103, 65, 98];
        var element = document.getElementById("contact_email");

        for(var i=0;i<arr.length;++i){
            arr[i] = String.fromCharCode(arr[i] - 1);
        }
        var text = arr.reverse().join('');

        element.setAttribute("href","mailto:" + text);
        element.innerHTML = text;
    }
    decode_email();
})();

function web_centipede(address)
{
    var connections     = [];
    var segments        = [];
    var max_connections = 16;
    var segment_length  = 1024 * 256;
    var downloaded_size = 0;
    var aborted         = false;
    var file_size       = 0;
    var file_data       = [];
    var ui              = {};
    var locker          = Std.ui("locker",{
        renderTo:"body",
        background:"white",
        visible:true,
        cursor:"wait"
    });
    var create_ui = function()
    {
        Std.css({
            ".downloader_main":{
                left:0,
                top:0,
                position:"fixed",
                padding:"16px",
                border:"1px solid #30a3e1",
                boxShadow:"0 0 6px #2888bf",
                width:"320px",
                height:"65px",
                background:"#eeeff0",
                zIndex:999,
                textAlign: "center"
            },
            ".downloader_progress":{
                position: "relative",
                background: "#F4FAFF",
                width: "315px",
                height: "30px",
                border:"1px solid #216f9c",
                borderRadius:"2px",
                boxShadow:"0 0 4px #31a4eb",
            },
            ".downloader_progress_location":{
                position: "absolute",
                background:"#30a0e6",
                left:0,
                top:0,
                width:0,
                height:"30px",
                zIndex: 1
            },
            ".downloader_progress_text":{
                position: "relative",
                lineHeight:"30px",
                color:"#393d3f",
                zIndex: 2,
                textShadow:"0 1px 0 #acacac"
            },
            ".downloader_text":{
                fontSize:"18px",
                marginTop:"8px",
                color:"#393d3f",
                textShadow:"0 1px 0 white",
                background:"url('../style/images/download.png') 5px 3px no-repeat"
            }
        });
        ui.main = newDiv("downloader_main").appendTo("body");
        ui.progress = newDiv("downloader_progress").appendTo(ui.main);
        ui.progress_location = newDiv("downloader_progress_location").appendTo(ui.progress);
        ui.progress_text = newDiv("downloader_progress_text").appendTo(ui.progress);
        ui.text = newDiv("downloader_text").appendTo(ui.main);

        var left = (Std.dom(window).width()  - ui.main.outerWidth())  / 2;
        var top  = (Std.dom(window).height() - ui.main.outerHeight()) / 2;

        ui.progress_text.html("0%");
        ui.main.css({left:left < 0 ? 0 : left,top :top < 0 ? 0 : top});
        ui.text.html("...")
    }
    var update_progress = function()
    {
        var percent = Std.convert.percent(downloaded_size,file_size);

        ui.progress_location.width(ui.progress.width() * (percent / 100));
        ui.progress_text.html(percent.toFixed(2) + "%");
        ui.text.html((downloaded_size / 1024 / 1024).toFixed(2) + "MB / " + (file_size / 1024 / 1024).toFixed(2) + " MB");
    }
    var extract_file_name = function(text)
    {
        let filename = text;
        let index    = filename.lastIndexOf('/');

        if(index === -1){
            index = filename.lastIndexOf('\\');
        }
        if(index !== -1){
            filename = filename.substr(index + 1);
        }
        return filename;
    }
    var get_file_size   = function(on_success)
    {
        Std.ajax({
            type:"HEAD",
            url:address,
            error:download_failed,
            success:on_success
        })
    }
    var download_completed = function()
    {
        if(aborted){
            return;
        }
        var blob     = new Blob(file_data,{type: "application/octet-binary"});
        var filename = extract_file_name(address);

        Std.dom("body").removeStyle("cursor");
        locker.remove();
        ui.main.remove();

        if(window.navigator.msSaveOrOpenBlob){
            window.navigator.msSaveOrOpenBlob(blob,filename);
        }else{
            var url = window.URL.createObjectURL(blob);
            var a   = newDom("a").attr({href:url,download:extract_file_name(address)}).appendTo("body");

            a.dom.dispatchEvent(new MouseEvent('click',{
                view: window,
                bubbles: true,
                cancelable: true
            }));
            window.URL.revokeObjectURL(url);
            a.remove();
        }
    }
    var download_failed = function()
    {
        Std.dom("body").removeStyle("cursor");
        locker.remove();
        ui.main.remove();
        alert("download error");
        connections = [];
        segments    = [];
        file_data   = [];
    }
    var download_segment = function(segment,on_success,retried)
    {
        var ajax = Std.ajax({
            url:address,
            format:"arraybuffer",
            requestHeader:{
                Range:"bytes=" + segment.begin + "-" + (segment.end - 1)
            },
            error:function(){
                connections.remove(connections.indexOf(ajax));

                if(retried + 1 < 5){
                    download_segment(segment,on_success,retried + 1);
                }else{
                    for(var i=0;i<connections.length;++i){
                        connections[i].abort();
                    }
                    if(!aborted){
                        download_failed();
                        aborted = true;
                    }
                }
            },
            success:function(){
                connections.remove(connections.indexOf(ajax));
                on_success(segment,ajax.http.response);
            },
            beforeSend:function(){
                this.http.responseType = "arraybuffer";
            }
        })
        connections.push(ajax);
    }
    var download_file = function()
    {
        if(connections.length === 0 && segments.length === 0){
            return download_completed();
        }
        for(var i=connections.length;i<max_connections;++i)
        {
            if(segments.length === 0){
                return;
            }
            var segment = segments[segments.length - 1];
            segments.pop();

            download_segment(segment,function(segment,data){
                file_data[segment.i] = data;
                downloaded_size += data.byteLength;

                update_progress();
                download_file();
            });
        }
    }

    Std.ajax.hook("success",function(ajax){
        if(ajax.http.responseType === "arraybuffer"){
            ajax.emit("success",ajax);
            return false;
        }
        return true;
    });
    create_ui();
    get_file_size(function(e)
    {
        var length  = this.responseHeader("content-length");

        if(!isNumeric(length) || length <= 0){
            return;
        }
        file_size = parseInt(length);

        for(var i=0;i<Math.ceil(file_size / segment_length);i++){
            var begin = i * segment_length;
            var end   = Math.min((i + 1) * segment_length,file_size);

            segments.push({i:i,begin:begin,end:end});
        }
        update_progress();
        download_file();
    });
}

function download_file(type)
{
    if(typeof(XMLHttpRequest) === "undefined" || typeof(ArrayBuffer) === "undefined"){
        document.location = document.getElementById(type).getAttribute("href");
        return false;
    }
    var element = document.createElement("script");

    element.setAttribute("src","../script/std.min.js");
    element.setAttribute("async","false");
    element.setAttribute("defer","true");
    element.onload = function(){
        web_centipede(Std.dom("#" + type).attr("href"));
    };
    document.body.style = "cursor: wait;"
    document.head.appendChild(element);

    return false;
}
