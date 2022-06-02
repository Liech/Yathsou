#include "dotnet.h"

#include <nethost.h>
#include <hostfxr.h>

//https://docs.microsoft.com/en-us/dotnet/core/tutorials/netcore-hosting

#ifdef _WINDOWS
#include <Windows.h>

#define STR(s) L ## s
#define CH(c) L ## c
#define DIR_SEPARATOR L'\\'
#define MAX_PATH 255

#else
#include <dlfcn.h>
#include <limits.h>

#define STR(s) s
#define CH(c) c
#define DIR_SEPARATOR '/'
#define MAX_PATH PATH_MAX

#endif

namespace Haas {
  dotnet::dotnet() {

  }
}