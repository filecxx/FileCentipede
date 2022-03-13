#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <extcpp/core>

#ifdef EXT_OS_WINDOWS
#include <windows.h>
#include <process.h>
static char sep = '\\';
#else
static char sep = '/';
#endif

#ifndef WEXITSTATUS
#define WEXITSTATUS(w) (w)
#endif



#ifdef EXT_OS_WINDOWS
int extract_dir(wchar_t* directory)
{
    wchar_t path[1024] = {0};
    GetModuleFileNameW(nullptr,path,sizeof(path));
    int length = wcslen(path);

    for(int i=length-1;i>=0;--i)
    {
        if(path[i] == '/' || path[i] == '\\'){
            ::wcsncpy(directory,path,i + 1);
            break;
        }
    }
    return 0;
}

int main(int argc,char* argv[])
{
    wchar_t path[MAX_PATH] = L"";
    extract_dir(path);
    wcscat(path,L"lib");
    _wchdir(path);

    argv[0] = "fileu.exe";

    _execv(argv[0],argv);

    return 0;
}
#else
int extract_dir(char* directory)
{
    char path[1024] = {0};
    char str[1024];
    snprintf(str,sizeof(str),"/proc/self/exe");
    readlink(str,path,sizeof(str));

    int length = strlen(path);

    for(int i=length-1;i>=0;--i)
    {
        if(path[i] == '/' || path[i] == '\\'){
            ::memcpy(directory,path,i + 1);
            break;
        }
    }
    return 0;
}

int main(int argc,char* argv[])
{
    char path[1024] = "";
    extract_dir(path);
    strcat(path,"lib");
    chdir(path);

    strcat(path,"/fileu");

    char  libc[]    = "libc.so";
    char* argv2[16] = {libc,path,nullptr};

    for(int i=1;i<argc + 1;++i){
        argv2[i + 1] = argv[i];
    }
    execv("libc.so",argv2);

    return 0;
}
#endif
