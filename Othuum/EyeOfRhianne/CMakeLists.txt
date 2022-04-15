cmake_minimum_required(VERSION 2.8...3.20)
project(EyeOfRhianne)

find_package(glm REQUIRED)

############################################################################
############################################################################
############################################################################

set(Header_Files
    "Source/EyeOfRhianne/AnimationSelection.h"
    "Source/EyeOfRhianne/AssetSelection.h"
    "Source/EyeOfRhianne/EyeOfRhianneConfiguration.h"
    "Source/EyeOfRhianne/Graphic.h"
    "Source/EyeOfRhianne/GraphicOptions.h"
    "Source/EyeOfRhianne/MapSelection.h"
    "Source/EyeOfRhianne/RendererSelection.h"
    "Source/EyeOfRhianne/ScriptSelection.h"
    "Source/EyeOfRhianne/SkyBoxSelection.h"
    "Source/EyeOfRhianne/SoundSelection.h"
    "Source/EyeOfRhianne/UnitModelSelection.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Source/EyeOfRhianne/AnimationSelection.cpp"
    "Source/EyeOfRhianne/AssetSelection.cpp"
    "Source/EyeOfRhianne/EyeOfRhianneConfiguration.cpp"
    "Source/EyeOfRhianne/Graphic.cpp"
    "Source/EyeOfRhianne/GraphicOptions.cpp"
    "Source/EyeOfRhianne/ListSelection.cpp"
    "Source/EyeOfRhianne/main.cpp"
    "Source/EyeOfRhianne/MapSelection.cpp"
    "Source/EyeOfRhianne/RendererSelection.cpp"
    "Source/EyeOfRhianne/ScriptSelection.cpp"
    "Source/EyeOfRhianne/SkyBoxSelection.cpp"
    "Source/EyeOfRhianne/SoundSelection.cpp"
    "Source/EyeOfRhianne/UnitModelSelection.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

############################################################################
############################################################################
############################################################################

add_executable(EyeOfRhianne ${ALL_FILES})
set_property(TARGET EyeOfRhianne PROPERTY CXX_STANDARD 20)


target_link_libraries(EyeOfRhianne 
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

target_include_directories(EyeOfRhianne PRIVATE 
"${IyathuumCoreLib_SOURCE_DIR}/Source"
"${SelenNavigationLib_SOURCE_DIR}/Source"
"${SuthanusPhysicLib_SOURCE_DIR}/Source"
"${AhwassaGraphicsLib_SOURCE_DIR}/Source"
"${HaasScriptingLib_SOURCE_DIR}/Source"
"${AezeselFileIOLib_SOURCE_DIR}/Source"
"${VishalaNetworkLib_SOURCE_DIR}/Source"
"${AthanahCommonLib_SOURCE_DIR}/Source"

)

add_dependencies(EyeOfRhianne 
IyathuumCoreLib 
SelenNavigationLib
SuthanusPhysicLib
AhwassaGraphicsLib
HaasScriptingLib
AezeselFileIOLib
VishalaNetworkLib
AthanahCommonLib
)

add_custom_command(TARGET EyeOfRhianne POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               "${EyeOfRhianne_SOURCE_DIR}/Scripts"              
                $<TARGET_FILE_DIR:EyeOfRhianne>/Data/Scripts)
				
add_custom_command(TARGET EyeOfRhianne POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               "${AhwassaGraphicsLib_SOURCE_DIR}/Data/Fonts/arial.ttf"              
                $<TARGET_FILE_DIR:EyeOfRhianne>/Data/Fonts/arial.ttf)
