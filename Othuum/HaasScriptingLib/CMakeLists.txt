set(PROJECT_NAME HaasScriptingLib)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "ScriptEngine.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "ScriptEngine.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(lib
    "lib/json.hpp"
    "lib/json_fwd.hpp"
)
source_group("lib" FILES ${lib})

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

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE HaasScriptingLib)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE        "TRUE"
        INTERPROCEDURAL_OPTIMIZATION_RELEASEWITHDBG "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE        "TRUE"
        INTERPROCEDURAL_OPTIMIZATION_RELEASEWITHDBG "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/lua"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "$<$<CONFIG:ReleaseWithDbg>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "$<$<CONFIG:ReleaseWithDbg>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /MP;
                /Oi;
                /Gy;
                /openmp
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /MP;
                /Oi;
                /Gy;
                /openmp
            >
            /permissive-;
            /std:c++latest;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /OPT:REF;
                /OPT:ICF
            >
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    IyathuumCoreLib
)

