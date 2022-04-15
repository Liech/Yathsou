cmake_minimum_required(VERSION 2.8...3.23)
project(SuperbCommander)

find_package(nlohmann_json REQUIRED)
find_package(glm REQUIRED)
find_package(snappy REQUIRED)
find_package(unofficial-enet REQUIRED)
find_package(unofficial-concurrentqueue REQUIRED)

############################################################################
############################################################################
############################################################################
set(Header_Files
    "Source/SuperbCommander/Config.h"
    "Source/SuperbCommander/DriveInterface.h"
    "Source/SuperbCommander/NavigationUI.h"
    "Source/SuperbCommander/PhysicsDebugView.h"
    "Source/SuperbCommander/Spheres.h"
    "Source/SuperbCommander/UnitsOld.h"
    "Source/SuperbCommander/UnitsVisualization.h"
    "Source/SuperbCommander/World.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Formation
    "Source/SuperbCommander/Formation/FormationDialog.h"
    "Source/SuperbCommander/Formation/FormationWidget.h"
    "Source/SuperbCommander/Formation/Selector.h"
)
source_group("Header Files\\Formation" FILES ${Header_Files__Formation})

set(Header_Files__Formation__Shapes
    "Source/SuperbCommander/Formation/Shapes/CircleShape.h"
    "Source/SuperbCommander/Formation/Shapes/FormationShape.h"
    "Source/SuperbCommander/Formation/Shapes/RectangleShape.h"
    "Source/SuperbCommander/Formation/Shapes/TriangleShape.h"
)
source_group("Header Files\\Formation\\Shapes" FILES ${Header_Files__Formation__Shapes})

set(Header_Files__Game
    "Source/SuperbCommander/Game/Control.h"
    "Source/SuperbCommander/Game/Database.h"
    "Source/SuperbCommander/Game/Game.h"
    "Source/SuperbCommander/Game/NonGame.h"
    "Source/SuperbCommander/Game/Overlay.h"
    "Source/SuperbCommander/Game/Physic.h"
    "Source/SuperbCommander/Game/Terrain.h"
    "Source/SuperbCommander/Game/Units.h"
    "Source/SuperbCommander/Game/Visualization.h"
)
source_group("Header Files\\Game" FILES ${Header_Files__Game})

set(Header_Files__Unit
    "Source/SuperbCommander/Unit/Unit.h"
    "Source/SuperbCommander/Unit/UnitAgentInterface.h"
    "Source/SuperbCommander/Unit/UnitConstructor.h"
    "Source/SuperbCommander/Unit/WheeledSteeringAgent.h"
)
source_group("Header Files\\Unit" FILES ${Header_Files__Unit})

set(Source_Files
    "Source/SuperbCommander/Config.cpp"
    "Source/SuperbCommander/DriveInterface.cpp"
    "Source/SuperbCommander/main.cpp"
    "Source/SuperbCommander/NavigationUI.cpp"
    "Source/SuperbCommander/PhysicsDebugView.cpp"
    "Source/SuperbCommander/Spheres.cpp"
    "Source/SuperbCommander/UnitsOld.cpp"
    "Source/SuperbCommander/UnitsVisualization.cpp"
    "Source/SuperbCommander/World.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Formation
    "Source/SuperbCommander/Formation/FormationDialog.cpp"
    "Source/SuperbCommander/Formation/FormationWidget.cpp"
    "Source/SuperbCommander/Formation/Selector.cpp"
)
source_group("Source Files\\Formation" FILES ${Source_Files__Formation})

set(Source_Files__Formation__Shapes
    "Source/SuperbCommander/Formation/Shapes/CircleShape.cpp"
    "Source/SuperbCommander/Formation/Shapes/FormationShape.cpp"
    "Source/SuperbCommander/Formation/Shapes/RectangleShape.cpp"
    "Source/SuperbCommander/Formation/Shapes/TriangleShape.cpp"
)
source_group("Source Files\\Formation\\Shapes" FILES ${Source_Files__Formation__Shapes})

set(Source_Files__Game
    "Source/SuperbCommander/Game/Control.cpp"
    "Source/SuperbCommander/Game/Database.cpp"
    "Source/SuperbCommander/Game/Game.cpp"
    "Source/SuperbCommander/Game/NonGame.cpp"
    "Source/SuperbCommander/Game/Overlay.cpp"
    "Source/SuperbCommander/Game/Physic.cpp"
    "Source/SuperbCommander/Game/Terrain.cpp"
    "Source/SuperbCommander/Game/Units.cpp"
    "Source/SuperbCommander/Game/Visualization.cpp"
)
source_group("Source Files\\Game" FILES ${Source_Files__Game})

set(Source_Files__Unit
    "Source/SuperbCommander/Unit/Unit.cpp"
    "Source/SuperbCommander/Unit/UnitConstructor.cpp"
    "Source/SuperbCommander/Unit/WheeledSteeringAgent.cpp"
)
source_group("Source Files\\Unit" FILES ${Source_Files__Unit})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__Formation}
    ${Header_Files__Formation__Shapes}
    ${Header_Files__Game}
    ${Header_Files__Unit}
    ${Source_Files}
    ${Source_Files__Formation}
    ${Source_Files__Formation__Shapes}
    ${Source_Files__Game}
    ${Source_Files__Unit}
)


############################################################################
############################################################################
############################################################################

add_executable(SuperbCommander ${ALL_FILES})
set_property(TARGET SuperbCommander PROPERTY CXX_STANDARD 20)

target_link_libraries(SuperbCommander 
IyathuumCoreLib 
SelenNavigationLib
SuthanusPhysicLib
AhwassaGraphicsLib
HaasScriptingLib
AezeselFileIOLib
VishalaNetworkLib
AthanahCommonLib
glm::glm
)

target_include_directories(SuperbCommander PRIVATE 
"${SuperbCommander_SOURCE_DIR}/Source/SuperbCommander"
"${SuperbCommander_SOURCE_DIR}/Source"
"${IyathuumCoreLib_SOURCE_DIR}/Source"
"${SelenNavigationLib_SOURCE_DIR}/Source"
"${SuthanusPhysicLib_SOURCE_DIR}/Source"
"${AhwassaGraphicsLib_SOURCE_DIR}/Source"
"${AhwassaGraphicsLib_SOURCE_DIR}/lib"
"${HaasScriptingLib_SOURCE_DIR}/Source"
"${AezeselFileIOLib_SOURCE_DIR}/Source"
"${VishalaNetworkLib_SOURCE_DIR}/Source"
"${AthanahCommonLib_SOURCE_DIR}/Source"
)

add_dependencies(SuperbCommander 
IyathuumCoreLib 
SelenNavigationLib
SuthanusPhysicLib
AhwassaGraphicsLib
HaasScriptingLib
AezeselFileIOLib
VishalaNetworkLib
AthanahCommonLib
)

add_custom_command(TARGET SuperbCommander POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               "${AhwassaGraphicsLib_SOURCE_DIR}/Data/Fonts/arial.ttf"              
                $<TARGET_FILE_DIR:SuperbCommander>/Data/Fonts/arial.ttf)
