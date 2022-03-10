(function()
{
    var decode_email = function()
    {
        var arr     = [110,112,100,47,102,100,111,102,103,109,106,98,110,65,122,118,104,117,106,116,116,102,109,102,110,98,111];
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