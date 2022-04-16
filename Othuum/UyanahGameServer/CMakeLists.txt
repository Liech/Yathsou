cmake_minimum_required(VERSION 2.8...3.23)
project(UyanahGameServer)

find_package(nlohmann_json REQUIRED)
find_package(glm REQUIRED)

############################################################################
############################################################################
############################################################################

set(Headerdateien
    "Source/UyanahGameServer/Client.h"
    "Source/UyanahGameServer/ClientConfiguration.h"
    "Source/UyanahGameServer/Component.h"
    "Source/UyanahGameServer/DedicatedServer.h"
    "Source/UyanahGameServer/DedicatedServerConfiguration.h"
    "Source/UyanahGameServer/Entity.h"
    "Source/UyanahGameServer/Scene.h"
)
source_group("Headerdateien" FILES ${Headerdateien})

set(Headerdateien__Commands
    "Source/UyanahGameServer/Commands/Command.h"
    "Source/UyanahGameServer/Commands/Initialize.h"
    "Source/UyanahGameServer/Commands/Key.h"
    "Source/UyanahGameServer/Commands/UpdateScene.h"
)
source_group("Headerdateien\\Commands" FILES ${Headerdateien__Commands})

set(Headerdateien__Components
    "Source/UyanahGameServer/Components/Dot.h"
    "Source/UyanahGameServer/Components/Transform2D.h"
)
source_group("Headerdateien\\Components" FILES ${Headerdateien__Components})

set(Quelldateien
    "Source/UyanahGameServer/Client.cpp"
    "Source/UyanahGameServer/ClientConfiguration.cpp"
    "Source/UyanahGameServer/Component.cpp"
    "Source/UyanahGameServer/DedicatedServer.cpp"
    "Source/UyanahGameServer/DedicatedServerConfiguration.cpp"
    "Source/UyanahGameServer/Entity.cpp"
    "Source/UyanahGameServer/Scene.cpp"
)
source_group("Quelldateien" FILES ${Quelldateien})

set(Quelldateien__Commands
    "Source/UyanahGameServer/Commands/Command.cpp"
    "Source/UyanahGameServer/Commands/Initialize.cpp"
    "Source/UyanahGameServer/Commands/Key.cpp"
    "Source/UyanahGameServer/Commands/UpdateScene.cpp"
)
source_group("Quelldateien\\Commands" FILES ${Quelldateien__Commands})

set(Quelldateien__Components
    "Source/UyanahGameServer/Components/Dot.cpp"
    "Source/UyanahGameServer/Components/Transform2D.cpp"
)
source_group("Quelldateien\\Components" FILES ${Quelldateien__Components})

set(ALL_FILES
    ${Headerdateien}
    ${Headerdateien__Commands}
    ${Headerdateien__Components}
    ${Quelldateien}
    ${Quelldateien__Commands}
    ${Quelldateien__Components}
)


############################################################################
############################################################################
############################################################################

add_library(UyanahGameServer ${ALL_FILES})
set_property(TARGET UyanahGameServer PROPERTY CXX_STANDARD 20)

target_link_libraries(UyanahGameServer PRIVATE
glm::glm
IyathuumCoreLib
nlohmann_json::nlohmann_json
VishalaNetworkLib
)

target_include_directories(UyanahGameServer PRIVATE 
"${UyanahGameServer_SOURCE_DIR}/Source/UyanahGameServer"
"${UyanahGameServer_SOURCE_DIR}/Source"
"${VishalaNetworkLib_SOURCE_DIR}/Source"
"${VishalaNetworkLib_SOURCE_DIR}/lib"
"${IyathuumCoreLib_SOURCE_DIR}/Source"
)

add_dependencies(UyanahGameServer 
IyathuumCoreLib 
VishalaNetworkLib
)