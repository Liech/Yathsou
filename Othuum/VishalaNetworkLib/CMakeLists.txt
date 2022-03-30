set(PROJECT_NAME VishalaNetworkLib)

################################################################################
# Source groups
################################################################################
set(Header_Files__Core
    "Core/BinaryPackage.h"
    "Core/Command.h"
    "Core/Connection.h"
    "Core/ConnectionMultiplexer.h"
    "Core/NetworkMemory.h"
    "Core/Serialization.h"
)
source_group("Header Files\\Core" FILES ${Header_Files__Core})

set(Header_Files__Protocoll
    "Protocoll/AuthoritarianGameClient.h"
    "Protocoll/AuthoritarianGameServer.h"
    "Protocoll/LiberalGameClient.h"
    "Protocoll/LiberalGameServer.h"
    "Protocoll/LiberalMessage.h"
)
source_group("Header Files\\Protocoll" FILES ${Header_Files__Protocoll})

set(Header_Files__Protocoll__Client
    "Protocoll/Client/LobbyClient.h"
    "Protocoll/Client/LobbyConnector.h"
)
source_group("Header Files\\Protocoll\\Client" FILES ${Header_Files__Protocoll__Client})

set(Header_Files__Protocoll__Server
    "Protocoll/Server/GameLobby.h"
    "Protocoll/Server/Lobby.h"
    "Protocoll/Server/LobbyPlayer.h"
)
source_group("Header Files\\Protocoll\\Server" FILES ${Header_Files__Protocoll__Server})

set(Header_Files__Serializable
    "Serializable/Acknowledgement.h"
    "Serializable/Client2LobbyMessage.h"
    "Serializable/CreateGameRequest.h"
    "Serializable/GameLobbyPlayer.h"
    "Serializable/GameLobbyStateUpdate.h"
    "Serializable/JoinGameRequest.h"
    "Serializable/Lobby2ClientMessage.h"
    "Serializable/LobbyBriefing.h"
    "Serializable/LobbyStateUpdate.h"
    "Serializable/LoginInstructions.h"
    "Serializable/Message.h"
    "Serializable/SelfBriefing.h"
    "Serializable/ServerConfiguration.h"
)
source_group("Header Files\\Serializable" FILES ${Header_Files__Serializable})

set(Header_Files__Serializable__Lobby
    "Serializable/Lobby/LobbyGame.h"
    "Serializable/Lobby/LobbyModel.h"
    "Serializable/Lobby/LobbyPlayerModel.h"
    "Serializable/Lobby/OpenLobbyRequest.h"
)
source_group("Header Files\\Serializable\\Lobby" FILES ${Header_Files__Serializable__Lobby})

set(Source_Files__Core
    "Core/BinaryPackage.cpp"
    "Core/Connection.cpp"
    "Core/ConnectionMultiplexer.cpp"
    "Core/NetworkMemory.cpp"
    "Core/Serialization.cpp"
)
source_group("Source Files\\Core" FILES ${Source_Files__Core})

set(Source_Files__Protocoll
    "Protocoll/AuthoritarianGameClient.cpp"
    "Protocoll/AuthoritarianGameServer.cpp"
    "Protocoll/LiberalGameClient.cpp"
    "Protocoll/LiberalGameServer.cpp"
    "Protocoll/LiberalMessage.cpp"
)
source_group("Source Files\\Protocoll" FILES ${Source_Files__Protocoll})

set(Source_Files__Protocoll__Client
    "Protocoll/Client/LobbyClient.cpp"
    "Protocoll/Client/LobbyConnector.cpp"
)
source_group("Source Files\\Protocoll\\Client" FILES ${Source_Files__Protocoll__Client})

set(Source_Files__Protocoll__Server
    "Protocoll/Server/GameLobby.cpp"
    "Protocoll/Server/Lobby.cpp"
    "Protocoll/Server/LobbyPlayer.cpp"
)
source_group("Source Files\\Protocoll\\Server" FILES ${Source_Files__Protocoll__Server})

set(Source_Files__Serializable
    "Serializable/Acknowledgement.cpp"
    "Serializable/Client2LobbyMessage.cpp"
    "Serializable/CreateGameRequest.cpp"
    "Serializable/GameLobbyPlayer.cpp"
    "Serializable/GameLobbyStateUpdate.cpp"
    "Serializable/JoinGameRequest.cpp"
    "Serializable/Lobby2ClientMessage.cpp"
    "Serializable/LobbyBriefing.cpp"
    "Serializable/LobbyStateUpdate.cpp"
    "Serializable/LoginInstructions.cpp"
    "Serializable/Message.cpp"
    "Serializable/SelfBriefing.cpp"
    "Serializable/ServerConfiguration.cpp"
)
source_group("Source Files\\Serializable" FILES ${Source_Files__Serializable})

set(Source_Files__Serializable__Lobby
    "Serializable/Lobby/LobbyGame.cpp"
    "Serializable/Lobby/LobbyModel.cpp"
    "Serializable/Lobby/LobbyPlayerModel.cpp"
    "Serializable/Lobby/OpenLobbyRequest.cpp"
)
source_group("Source Files\\Serializable\\Lobby" FILES ${Source_Files__Serializable__Lobby})

set(lib
    "lib/atomicops.h"
    "lib/concurrentqueue.h"
    "lib/json.hpp"
    "lib/json_fwd.hpp"
    "lib/readerwriterqueue.h"
)
source_group("lib" FILES ${lib})

set(lib__enet
    "lib/enet/callbacks.h"
    "lib/enet/list.h"
    "lib/enet/protocol.h"
    "lib/enet/time.h"
    "lib/enet/types.h"
    "lib/enet/unix.h"
    "lib/enet/utility.h"
    "lib/enet/win32.h"
)
source_group("lib\\enet" FILES ${lib__enet})

set(lib__snappy
    "lib/snappy/snappy-c.cc"
    "lib/snappy/snappy-c.h"
    "lib/snappy/snappy-internal.h"
    "lib/snappy/snappy-sinksource.cc"
    "lib/snappy/snappy-sinksource.h"
    "lib/snappy/snappy-stubs-internal.cc"
    "lib/snappy/snappy-stubs-internal.h"
    "lib/snappy/snappy-stubs-public.h"
    "lib/snappy/snappy.cc"
    "lib/snappy/snappy.h"
    "lib/snappy/snappy_compress_fuzzer.cc"
    "lib/snappy/snappy_uncompress_fuzzer.cc"
)
source_group("lib\\snappy" FILES ${lib__snappy})

set(lib__xdelta3
    "lib/xdelta3/xdelta3-blkcache.h"
    "lib/xdelta3/xdelta3-cfgs.h"
    "lib/xdelta3/xdelta3-decode.h"
    "lib/xdelta3/xdelta3-djw.h"
    "lib/xdelta3/xdelta3-fgk.h"
    "lib/xdelta3/xdelta3-hash.h"
    "lib/xdelta3/xdelta3-internal.h"
    "lib/xdelta3/xdelta3-list.h"
    "lib/xdelta3/xdelta3-lzma.h"
    "lib/xdelta3/xdelta3-main.h"
    "lib/xdelta3/xdelta3-merge.h"
    "lib/xdelta3/xdelta3-second.h"
    "lib/xdelta3/xdelta3.c"
    "lib/xdelta3/xdelta3.h"
)
source_group("lib\\xdelta3" FILES ${lib__xdelta3})

set(ALL_FILES
    ${Header_Files__Core}
    ${Header_Files__Protocoll}
    ${Header_Files__Protocoll__Client}
    ${Header_Files__Protocoll__Server}
    ${Header_Files__Serializable}
    ${Header_Files__Serializable__Lobby}
    ${Source_Files__Core}
    ${Source_Files__Protocoll}
    ${Source_Files__Protocoll__Client}
    ${Source_Files__Protocoll__Server}
    ${Source_Files__Serializable}
    ${Source_Files__Serializable__Lobby}
    ${lib}
    ${lib__enet}
    ${lib__snappy}
    ${lib__xdelta3}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE VishalaNetworkLib)

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
        "${CMAKE_CURRENT_SOURCE_DIR}/."
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

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$(ProjectDir)lib/enet/enet64;"
        "$(WindowsSdkDir)Lib\10.0.18362.0\um\x64\Ws2_32;"
        "$(WindowsSdkDir)Lib\10.0.18362.0\um\x64\Winmm"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

