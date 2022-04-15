cmake_minimum_required(VERSION 2.8...3.23)
project(VishalaNetworkLib)

find_package(nlohmann_json REQUIRED)
find_package(glm REQUIRED)
find_package(snappy REQUIRED)
find_package(unofficial-enet REQUIRED)
find_package(unofficial-concurrentqueue REQUIRED)

############################################################################
############################################################################
############################################################################

set(Header_Files__Core
    "Source/VishalaNetworkLib/Core/BinaryPackage.h"
    "Source/VishalaNetworkLib/Core/Command.h"
    "Source/VishalaNetworkLib/Core/Connection.h"
    "Source/VishalaNetworkLib/Core/ConnectionMultiplexer.h"
    "Source/VishalaNetworkLib/Core/NetworkMemory.h"
    "Source/VishalaNetworkLib/Core/Serialization.h"
)
source_group("Header Files\\Core" FILES ${Header_Files__Core})

set(Header_Files__Protocoll
    "Source/VishalaNetworkLib/Protocoll/AuthoritarianGameClient.h"
    "Source/VishalaNetworkLib/Protocoll/AuthoritarianGameServer.h"
    "Source/VishalaNetworkLib/Protocoll/LiberalGameClient.h"
    "Source/VishalaNetworkLib/Protocoll/LiberalGameServer.h"
    "Source/VishalaNetworkLib/Protocoll/LiberalMessage.h"
)
source_group("Header Files\\Protocoll" FILES ${Header_Files__Protocoll})

set(Header_Files__Protocoll__Client
    "Source/VishalaNetworkLib/Protocoll/Client/LobbyClient.h"
    "Source/VishalaNetworkLib/Protocoll/Client/LobbyConnector.h"
)
source_group("Header Files\\Protocoll\\Client" FILES ${Header_Files__Protocoll__Client})

set(Header_Files__Protocoll__Server
    "Source/VishalaNetworkLib/Protocoll/Server/GameLobby.h"
    "Source/VishalaNetworkLib/Protocoll/Server/Lobby.h"
    "Source/VishalaNetworkLib/Protocoll/Server/LobbyPlayer.h"
)
source_group("Header Files\\Protocoll\\Server" FILES ${Header_Files__Protocoll__Server})

set(Header_Files__Serializable
    "Source/VishalaNetworkLib/Serializable/Acknowledgement.h"
    "Source/VishalaNetworkLib/Serializable/Client2LobbyMessage.h"
    "Source/VishalaNetworkLib/Serializable/CreateGameRequest.h"
    "Source/VishalaNetworkLib/Serializable/GameLobbyPlayer.h"
    "Source/VishalaNetworkLib/Serializable/GameLobbyStateUpdate.h"
    "Source/VishalaNetworkLib/Serializable/JoinGameRequest.h"
    "Source/VishalaNetworkLib/Serializable/Lobby2ClientMessage.h"
    "Source/VishalaNetworkLib/Serializable/LobbyBriefing.h"
    "Source/VishalaNetworkLib/Serializable/LobbyStateUpdate.h"
    "Source/VishalaNetworkLib/Serializable/LoginInstructions.h"
    "Source/VishalaNetworkLib/Serializable/Message.h"
    "Source/VishalaNetworkLib/Serializable/SelfBriefing.h"
    "Source/VishalaNetworkLib/Serializable/ServerConfiguration.h"
)
source_group("Header Files\\Serializable" FILES ${Header_Files__Serializable})

set(Header_Files__Serializable__Lobby
    "Source/VishalaNetworkLib/Serializable/Lobby/LobbyGame.h"
    "Source/VishalaNetworkLib/Serializable/Lobby/LobbyModel.h"
    "Source/VishalaNetworkLib/Serializable/Lobby/LobbyPlayerModel.h"
    "Source/VishalaNetworkLib/Serializable/Lobby/OpenLobbyRequest.h"
)
source_group("Header Files\\Serializable\\Lobby" FILES ${Header_Files__Serializable__Lobby})

set(Source_Files__Core
    "Source/VishalaNetworkLib/Core/BinaryPackage.cpp"
    "Source/VishalaNetworkLib/Core/Connection.cpp"
    "Source/VishalaNetworkLib/Core/ConnectionMultiplexer.cpp"
    "Source/VishalaNetworkLib/Core/NetworkMemory.cpp"
    "Source/VishalaNetworkLib/Core/Serialization.cpp"
)
source_group("Source Files\\Core" FILES ${Source_Files__Core})

set(Source_Files__Protocoll
    "Source/VishalaNetworkLib/Protocoll/AuthoritarianGameClient.cpp"
    "Source/VishalaNetworkLib/Protocoll/AuthoritarianGameServer.cpp"
    "Source/VishalaNetworkLib/Protocoll/LiberalGameClient.cpp"
    "Source/VishalaNetworkLib/Protocoll/LiberalGameServer.cpp"
    "Source/VishalaNetworkLib/Protocoll/LiberalMessage.cpp"
)
source_group("Source Files\\Protocoll" FILES ${Source_Files__Protocoll})

set(Source_Files__Protocoll__Client
    "Source/VishalaNetworkLib/Protocoll/Client/LobbyClient.cpp"
    "Source/VishalaNetworkLib/Protocoll/Client/LobbyConnector.cpp"
)
source_group("Source Files\\Protocoll\\Client" FILES ${Source_Files__Protocoll__Client})

set(Source_Files__Protocoll__Server
    "Source/VishalaNetworkLib/Protocoll/Server/GameLobby.cpp"
    "Source/VishalaNetworkLib/Protocoll/Server/Lobby.cpp"
    "Source/VishalaNetworkLib/Protocoll/Server/LobbyPlayer.cpp"
)
source_group("Source Files\\Protocoll\\Server" FILES ${Source_Files__Protocoll__Server})

set(Source_Files__Serializable
    "Source/VishalaNetworkLib/Serializable/Acknowledgement.cpp"
    "Source/VishalaNetworkLib/Serializable/Client2LobbyMessage.cpp"
    "Source/VishalaNetworkLib/Serializable/CreateGameRequest.cpp"
    "Source/VishalaNetworkLib/Serializable/GameLobbyPlayer.cpp"
    "Source/VishalaNetworkLib/Serializable/GameLobbyStateUpdate.cpp"
    "Source/VishalaNetworkLib/Serializable/JoinGameRequest.cpp"
    "Source/VishalaNetworkLib/Serializable/Lobby2ClientMessage.cpp"
    "Source/VishalaNetworkLib/Serializable/LobbyBriefing.cpp"
    "Source/VishalaNetworkLib/Serializable/LobbyStateUpdate.cpp"
    "Source/VishalaNetworkLib/Serializable/LoginInstructions.cpp"
    "Source/VishalaNetworkLib/Serializable/Message.cpp"
    "Source/VishalaNetworkLib/Serializable/SelfBriefing.cpp"
    "Source/VishalaNetworkLib/Serializable/ServerConfiguration.cpp"
)
source_group("Source Files\\Serializable" FILES ${Source_Files__Serializable})

set(Source_Files__Serializable__Lobby
    "Source/VishalaNetworkLib/Serializable/Lobby/LobbyGame.cpp"
    "Source/VishalaNetworkLib/Serializable/Lobby/LobbyModel.cpp"
    "Source/VishalaNetworkLib/Serializable/Lobby/LobbyPlayerModel.cpp"
    "Source/VishalaNetworkLib/Serializable/Lobby/OpenLobbyRequest.cpp"
)
source_group("Source Files\\Serializable\\Lobby" FILES ${Source_Files__Serializable__Lobby})

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
    ${lib__xdelta3}
)


############################################################################
############################################################################
############################################################################

add_library(VishalaNetworkLib ${ALL_FILES})
set_property(TARGET VishalaNetworkLib PROPERTY CXX_STANDARD 20)

target_link_libraries(VishalaNetworkLib PRIVATE
glm::glm
IyathuumCoreLib
Snappy::snappy
unofficial::enet::enet
unofficial::concurrentqueue::concurrentqueue
nlohmann_json::nlohmann_json
)

target_include_directories(VishalaNetworkLib PRIVATE 
"${VishalaNetworkLib_SOURCE_DIR}/Source/VishalaNetworkLib"
"${VishalaNetworkLib_SOURCE_DIR}/Source"
"${VishalaNetworkLib_SOURCE_DIR}/lib"
"${IyathuumCoreLib_SOURCE_DIR}/Source"
)

add_dependencies(VishalaNetworkLib IyathuumCoreLib)