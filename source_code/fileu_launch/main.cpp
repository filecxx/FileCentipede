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


int extract_dir(char* directory)
{
    char path[1024] = {0};

#ifdef EXT_OS_LINUX
    char str[1024];
    snprintf(str,sizeof(str),"/proc/self/exe");
    readlink(str,path,sizeof(str));
#elif EXT_OS_WINDOWS
    GetModuleFileName(nullptr,path,sizeof(path));
#endif
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

#ifdef EXT_OS_WINDOWS
    strcat(path,"\\fileu.exe");
    argv[0] = path;
    _execv(path,argv);

#else
    strcat(path,"/fileu");
    char  libc[]    = "libc.so";
    char* argv2[16] = {libc,path,nullptr};

    for(int i=1;i<argc + 1;++i){
        argv2[i + 1] = argv[i];
    }
    execv("libc.so",argv2);
#endif

    return 0;
}