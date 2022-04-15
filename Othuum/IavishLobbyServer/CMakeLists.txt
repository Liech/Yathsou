cmake_minimum_required(VERSION 2.8...3.20)
project(IavishLobbyServer)

find_package(glm REQUIRED)

############################################################################
############################################################################
############################################################################

set(Header_Files
    "ConnectionTest.h"
    "LobbyServer.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "ConnectionTest.cpp"
    "LobbyServer.cpp"
    "main.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)


############################################################################
############################################################################
############################################################################

add_executable(IavishLobbyServer ${ALL_FILES})
set_property(TARGET IavishLobbyServer PROPERTY CXX_STANDARD 20)


target_link_libraries(IavishLobbyServer 
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

target_include_directories(IavishLobbyServer PRIVATE 
"${IyathuumCoreLib_SOURCE_DIR}/Source"
"${SelenNavigationLib_SOURCE_DIR}/Source"
"${SuthanusPhysicLib_SOURCE_DIR}/Source"
"${AhwassaGraphicsLib_SOURCE_DIR}/Source"
"${HaasScriptingLib_SOURCE_DIR}/Source"
"${AezeselFileIOLib_SOURCE_DIR}/Source"
"${VishalaNetworkLib_SOURCE_DIR}/Source"
"${AthanahCommonLib_SOURCE_DIR}/Source"

)

add_dependencies(IavishLobbyServer 
IyathuumCoreLib 
SelenNavigationLib
SuthanusPhysicLib
AhwassaGraphicsLib
HaasScriptingLib
AezeselFileIOLib
VishalaNetworkLib
AthanahCommonLib
)

add_custom_command(TARGET IavishLobbyServer POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               "${EyeOfRhianne_SOURCE_DIR}/Scripts"              
                $<TARGET_FILE_DIR:IavishLobbyServer>/Data/Scripts)
				
add_custom_command(TARGET IavishLobbyServer POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               "${AhwassaGraphicsLib_SOURCE_DIR}/Data/Fonts/arial.ttf"              
                $<TARGET_FILE_DIR:IavishLobbyServer>/Data/Fonts/arial.ttf)
