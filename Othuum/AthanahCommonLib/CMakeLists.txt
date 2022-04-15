cmake_minimum_required(VERSION 2.8...3.23)
project(AthanahCommonLib)


############################################################################
############################################################################
############################################################################

set(Header_Files
    "SkyBox.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Map
    "Source/AthanahCommonLib/Map/Map.h"
    "Source/AthanahCommonLib/Map/MapFactory.h"
    "Source/AthanahCommonLib/Map/MapRenderer.h"
    "Source/AthanahCommonLib/Map/Scenario.h"
)
source_group("Header Files\\Map" FILES ${Header_Files__Map})

set(Header_Files__Physic
    "Source/AthanahCommonLib/Physic/BoxVisualization.h"
    "Source/AthanahCommonLib/Physic/BulletDebugDrawer.h"
    "Source/AthanahCommonLib/Physic/NavigationMeshDebugDrawer.h"
)
source_group("Header Files\\Physic" FILES ${Header_Files__Physic})

set(Header_Files__SupCom
    "Source/AthanahCommonLib/Model3DRenderer.h"
    "Source/AthanahCommonLib/SupCom/SupComEnums.h"
    "Source/AthanahCommonLib/SupCom/SupComMeshLoader.h"
    "Source/AthanahCommonLib/SupCom/SupComMeshRenderer.h"
    "Source/AthanahCommonLib/SupCom/SupComMeshRendererDef.h"
    "Source/AthanahCommonLib/SupCom/SupComModel.h"
    "Source/AthanahCommonLib/SupCom/SupComVertex.h"
)
source_group("Header Files\\SupCom" FILES ${Header_Files__SupCom})

set(Header_Files__SupCom__Blueprint
    "Source/AthanahCommonLib/SupCom/Blueprint/Blueprint.h"
    "Source/AthanahCommonLib/SupCom/Blueprint/BlueprintBase.h"
    "Source/AthanahCommonLib/SupCom/Blueprint/BlueprintCommandCaps.h"
    "Source/AthanahCommonLib/SupCom/Blueprint/BlueprintDisplay.h"
    "Source/AthanahCommonLib/SupCom/Blueprint/BlueprintGeneral.h"
    "Source/AthanahCommonLib/SupCom/Blueprint/BlueprintPhysic.h"
)
source_group("Header Files\\SupCom\\Blueprint" FILES ${Header_Files__SupCom__Blueprint})

set(Header_Files__SupCom__Gamedata
    "Source/AthanahCommonLib/SupCom/Gamedata/BlueprintFactory.h"
    "Source/AthanahCommonLib/SupCom/Gamedata/Gamedata.h"
    "Source/AthanahCommonLib/SupCom/Gamedata/SkyboxFactory.h"
    "Source/AthanahCommonLib/SupCom/Gamedata/SupComModelFactory.h"
    "Source/AthanahCommonLib/SupCom/Gamedata/UiTextureFactory.h"
)
source_group("Header Files\\SupCom\\Gamedata" FILES ${Header_Files__SupCom__Gamedata})

set(Source_Files
    "Source/AthanahCommonLib/Model3DRenderer.cpp"
    "Source/AthanahCommonLib/SkyBox.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Map
    "Source/AthanahCommonLib/Map/Map.cpp"
    "Source/AthanahCommonLib/Map/MapFactory.cpp"
    "Source/AthanahCommonLib/Map/MapRenderer.cpp"
    "Source/AthanahCommonLib/Map/Scenario.cpp"
)
source_group("Source Files\\Map" FILES ${Source_Files__Map})

set(Source_Files__Physic
    "Source/AthanahCommonLib/Physic/BoxVisualization.cpp"
    "Source/AthanahCommonLib/Physic/BulletDebugDrawer.cpp"
    "Source/AthanahCommonLib/Physic/NavigationMeshDebugDrawer.cpp"
)
source_group("Source Files\\Physic" FILES ${Source_Files__Physic})

set(Source_Files__SupCom
    "Source/AthanahCommonLib/SupCom/SupComMeshLoader.cpp"
    "Source/AthanahCommonLib/SupCom/SupComMeshRenderer.cpp"
    "Source/AthanahCommonLib/SupCom/SupComMeshRendererDef.cpp"
    "Source/AthanahCommonLib/SupCom/SupComModel.cpp"
    "Source/AthanahCommonLib/SupCom/SupComVertex.cpp"
)
source_group("Source Files\\SupCom" FILES ${Source_Files__SupCom})

set(Source_Files__SupCom__Blueprint
    "Source/AthanahCommonLib/SupCom/Blueprint/Blueprint.cpp"
    "Source/AthanahCommonLib/SupCom/Blueprint/BlueprintCommandCaps.cpp"
    "Source/AthanahCommonLib/SupCom/Blueprint/BlueprintDisplay.cpp"
    "Source/AthanahCommonLib/SupCom/Blueprint/BlueprintGeneral.cpp"
    "Source/AthanahCommonLib/SupCom/Blueprint/BlueprintPhysic.cpp"
)
source_group("Source Files\\SupCom\\Blueprint" FILES ${Source_Files__SupCom__Blueprint})

set(Source_Files__SupCom__Gamedata
    "Source/AthanahCommonLib/SupCom/Gamedata/BlueprintFactory.cpp"
    "Source/AthanahCommonLib/SupCom/Gamedata/Gamedata.cpp"
    "Source/AthanahCommonLib/SupCom/Gamedata/SkyboxFactory.cpp"
    "Source/AthanahCommonLib/SupCom/Gamedata/SupComModelFactory.cpp"
    "Source/AthanahCommonLib/SupCom/Gamedata/UITextureFactory.cpp"
)
source_group("Source Files\\SupCom\\Gamedata" FILES ${Source_Files__SupCom__Gamedata})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__Map}
    ${Header_Files__Physic}
    ${Header_Files__SupCom}
    ${Header_Files__SupCom__Blueprint}
    ${Header_Files__SupCom__Gamedata}
    ${Source_Files}
    ${Source_Files__Map}
    ${Source_Files__Physic}
    ${Source_Files__SupCom}
    ${Source_Files__SupCom__Blueprint}
    ${Source_Files__SupCom__Gamedata}
)


############################################################################
############################################################################
############################################################################

add_library(AthanahCommonLib ${ALL_FILES})
set_property(TARGET AthanahCommonLib PROPERTY CXX_STANDARD 20)

target_link_libraries(AthanahCommonLib
glm::glm
IyathuumCoreLib
AhwassaGraphicsLib
HaasScriptingLib
SelenNavigationLib
SuthanusPhysicsLib
VishalaNetworkLib
)

target_include_directories(AthanahCommonLib PRIVATE 
"${AthanahCommonLib_SOURCE_DIR}/Source/AthanahCommonLib"
"${IyathuumCoreLib_SOURCE_DIR}/Source"
)

add_dependencies(AthanahCommonLib IyathuumCoreLib)