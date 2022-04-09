cmake_minimum_required(VERSION 2.8...3.23)
project(HaasScriptingLib)


include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.10.5
  EXCLUDE_FROM_ALL    TRUE
)
FetchContent_MakeAvailable(json)

############################################################################
############################################################################
############################################################################
set(Header_Files
    "Source/HaasScriptingLib/ScriptEngine.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Source/HaasScriptingLib/ScriptEngine.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(lib__lua
    "lib/lua/lapi.c"
    "lib/lua/lapi.h"
    "lib/lua/lauxlib.c"
    "lib/lua/lauxlib.h"
    "lib/lua/lbaselib.c"
    "lib/lua/lcode.c"
    "lib/lua/lcode.h"
    "lib/lua/lcorolib.c"
    "lib/lua/lctype.c"
    "lib/lua/lctype.h"
    "lib/lua/ldblib.c"
    "lib/lua/ldebug.c"
    "lib/lua/ldebug.h"
    "lib/lua/ldo.c"
    "lib/lua/ldo.h"
    "lib/lua/ldump.c"
    "lib/lua/lfunc.c"
    "lib/lua/lfunc.h"
    "lib/lua/lgc.c"
    "lib/lua/lgc.h"
    "lib/lua/linit.c"
    "lib/lua/liolib.c"
    "lib/lua/ljumptab.h"
    "lib/lua/llex.c"
    "lib/lua/llex.h"
    "lib/lua/llimits.h"
    "lib/lua/lmathlib.c"
    "lib/lua/lmem.c"
    "lib/lua/lmem.h"
    "lib/lua/loadlib.c"
    "lib/lua/lobject.c"
    "lib/lua/lobject.h"
    "lib/lua/lopcodes.c"
    "lib/lua/lopcodes.h"
    "lib/lua/lopnames.h"
    "lib/lua/loslib.c"
    "lib/lua/lparser.c"
    "lib/lua/lparser.h"
    "lib/lua/lprefix.h"
    "lib/lua/lstate.c"
    "lib/lua/lstate.h"
    "lib/lua/lstring.c"
    "lib/lua/lstring.h"
    "lib/lua/lstrlib.c"
    "lib/lua/ltable.c"
    "lib/lua/ltable.h"
    "lib/lua/ltablib.c"
    "lib/lua/ltm.c"
    "lib/lua/ltm.h"
    "lib/lua/lua.c"
    "lib/lua/lua.h"
    "lib/lua/lua.hpp"
    "lib/lua/luac.c"
    "lib/lua/luaconf.h"
    "lib/lua/lualib.h"
    "lib/lua/lundump.c"
    "lib/lua/lundump.h"
    "lib/lua/lutf8lib.c"
    "lib/lua/lvm.c"
    "lib/lua/lvm.h"
    "lib/lua/lzio.c"
    "lib/lua/lzio.h"
)
source_group("lib\\lua" FILES ${lib__lua})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
    ${lib}
    ${lib__lua}
)


############################################################################
############################################################################
############################################################################

add_library(HaasScriptingLib ${ALL_FILES})
set_property(TARGET HaasScriptingLib PROPERTY CXX_STANDARD 20)

target_link_libraries(HaasScriptingLib)
target_include_directories(HaasScriptingLib PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/Source/HaasScriptingLib
${CMAKE_CURRENT_SOURCE_DIR}/lib
${json_SOURCE_DIR}/include
)