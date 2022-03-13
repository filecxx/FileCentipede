function create_fileu_address(options)
{
    var base64_reference = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=';
    var base64_encode    = function(data)
    {
        if(typeof data != "string"){
            return null;
        }
        var i    = 0;
        var ac   = 0;
        var temp = [];
        var o1,o2,o3,h1,h2,h3,h4,bits;

        do{
            o1 = data.charCodeAt(i++);
            o2 = data.charCodeAt(i++);
            o3 = data.charCodeAt(i++);

            bits = o1 << 16 | o2 << 8 | o3;

            h1 = bits >> 18 & 0x3f;
            h2 = bits >> 12 & 0x3f;
            h3 = bits >> 6 & 0x3f;
            h4 = bits & 0x3f;

            temp[ac++] = base64_reference.charAt(h1) + base64_reference.charAt(h2) + base64_reference.charAt(h3) + base64_reference.charAt(h4);
        }while(i < data.length);

        var r   = data.length % 3;
        var enc = temp.join('');

        return (r ? enc.slice(0,r-3) : enc) + '==='.slice(r || 3);
    };
    var obj = {"@":"task_add"};

    if(typeof(options) == "string"){
        options = {uri:options};
    }
    if(typeof(options) != "object"){
        return null;
    }
    for(var name in options) {
        obj[name] = options[name];
    }
    if(typeof(obj.file_name) == "string"){
        obj.file_name = encodeURIComponent(decodeURIComponent(obj.file_name));
    }
    return "fileu:0" + base64_encode(JSON.stringify(obj));
}