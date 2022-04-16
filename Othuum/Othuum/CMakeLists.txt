cmake_minimum_required(VERSION 2.8...3.23)
project(OthuumExe)

find_package(nlohmann_json REQUIRED)
find_package(glm REQUIRED)

############################################################################
############################################################################
############################################################################

set(Header_Files
    "Source/Othuum/BulletDebugDrawer.h"
    "Source/Othuum/ClientConfiguration.h"
    "Source/Othuum/ClientControl.h"
    "Source/Othuum/ClientState.h"
    "Source/Othuum/DrawCubes.h"
    "Source/Othuum/InitializeCmd.h"
    "Source/Othuum/MainMenuLogic.h"
    "Source/Othuum/MainMenuLogicResult.h"
    "Source/Othuum/OthuumGame.h"
    "Source/Othuum/PhysicalModel.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__ClientVisualization
    "Source/Othuum/ClientVisualization/ClientVisualization.h"
)
source_group("Header Files\\ClientVisualization" FILES ${Header_Files__ClientVisualization})

set(Header_Files__MainMenuPages
    "Source/Othuum/MainMenuPages/DialogPage.h"
    "Source/Othuum/MainMenuPages/ErrorPage.h"
    "Source/Othuum/MainMenuPages/GameLobbyPage.h"
    "Source/Othuum/MainMenuPages/HostGamePage.h"
    "Source/Othuum/MainMenuPages/HostLoadingPage.h"
    "Source/Othuum/MainMenuPages/JoinLoadingPage.h"
    "Source/Othuum/MainMenuPages/JoinLobbyPage.h"
    "Source/Othuum/MainMenuPages/LobbyLoadingPage.h"
    "Source/Othuum/MainMenuPages/LobbyPage.h"
    "Source/Othuum/MainMenuPages/MainMenuPage.h"
    "Source/Othuum/MainMenuPages/OptionsPage.h"
    "Source/Othuum/MainMenuPages/StartGameLoadingPage.h"
)
source_group("Header Files\\MainMenuPages" FILES ${Header_Files__MainMenuPages})

set(Header_Files__SideProject
    "Source/Othuum/SideProject/SideProjectMain.h"
)
source_group("Header Files\\SideProject" FILES ${Header_Files__SideProject})

set(Source_Files
    "Source/Othuum/BulletDebugDrawer.cpp"
    "Source/Othuum/ClientConfiguration.cpp"
    "Source/Othuum/ClientControl.cpp"
    "Source/Othuum/ClientState.cpp"
    "Source/Othuum/DrawCubes.cpp"
    "Source/Othuum/InitializeCmd.cpp"
    "Source/Othuum/main.cpp"
    "Source/Othuum/MainMenuLogic.cpp"
    "Source/Othuum/MainMenuLogicResult.cpp"
    "Source/Othuum/OthuumGame.cpp"
    "Source/Othuum/PhysicalModel.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__ClientVisualization
    "Source/Othuum/ClientVisualization/ClientVisualization.cpp"
)
source_group("Source Files\\ClientVisualization" FILES ${Source_Files__ClientVisualization})

set(Source_Files__MainMenuPages
    "Source/Othuum/MainMenuPages/DialogPage.cpp"
    "Source/Othuum/MainMenuPages/ErrorPage.cpp"
    "Source/Othuum/MainMenuPages/GameLobbyPage.cpp"
    "Source/Othuum/MainMenuPages/HostGamePage.cpp"
    "Source/Othuum/MainMenuPages/HostLoadingPage.cpp"
    "Source/Othuum/MainMenuPages/JoinLoadingPage.cpp"
    "Source/Othuum/MainMenuPages/JoinLobbyPage.cpp"
    "Source/Othuum/MainMenuPages/LobbyLoadingPage.cpp"
    "Source/Othuum/MainMenuPages/LobbyPage.cpp"
    "Source/Othuum/MainMenuPages/MainMenuPage.cpp"
    "Source/Othuum/MainMenuPages/OptionsPage.cpp"
    "Source/Othuum/MainMenuPages/StartGameLoadingPage.cpp"
)
source_group("Source Files\\MainMenuPages" FILES ${Source_Files__MainMenuPages})

set(Source_Files__SideProject
    "Source/Othuum/SideProject/SideProjectMain.cpp"
)
source_group("Source Files\\SideProject" FILES ${Source_Files__SideProject})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__ClientVisualization}
    ${Header_Files__MainMenuPages}
    ${Header_Files__SideProject}
    ${Source_Files}
    ${Source_Files__ClientVisualization}
    ${Source_Files__MainMenuPages}
    ${Source_Files__SideProject}
)


############################################################################
############################################################################
############################################################################

add_executable(OthuumExe ${ALL_FILES})
set_property(TARGET OthuumExe PROPERTY CXX_STANDARD 20)

target_link_libraries(OthuumExe 
IyathuumCoreLib 
SelenNavigationLib
SuthanusPhysicLib
AhwassaGraphicsLib
HaasScriptingLib
AezeselFileIOLib
VishalaNetworkLib
AthanahCommonLib
UyanahGameServer
glm::glm
)

target_include_directories(OthuumExe PRIVATE 
"${OthuumExe_SOURCE_DIR}/Source/Othuum"
"${OthuumExe_SOURCE_DIR}/Source"
"${IyathuumCoreLib_SOURCE_DIR}/Source"
"${SelenNavigationLib_SOURCE_DIR}/Source"
"${SuthanusPhysicLib_SOURCE_DIR}/Source"
"${AhwassaGraphicsLib_SOURCE_DIR}/Source"
"${AhwassaGraphicsLib_SOURCE_DIR}/lib"
"${HaasScriptingLib_SOURCE_DIR}/Source"
"${AezeselFileIOLib_SOURCE_DIR}/Source"
"${VishalaNetworkLib_SOURCE_DIR}/Source"
"${AthanahCommonLib_SOURCE_DIR}/Source"
"${UyanahGameServer_SOURCE_DIR}/Source"
)

add_dependencies(OthuumExe 
IyathuumCoreLib 
SelenNavigationLib
SuthanusPhysicLib
AhwassaGraphicsLib
HaasScriptingLib
AezeselFileIOLib
VishalaNetworkLib
AthanahCommonLib
UyanahGameServer
)

add_custom_command(TARGET OthuumExe POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               "${AhwassaGraphicsLib_SOURCE_DIR}/Data/Fonts/arial.ttf"              
                $<TARGET_FILE_DIR:OthuumExe>/Data/Fonts/arial.ttf)
