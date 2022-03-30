set(PROJECT_NAME Othuum)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "BulletDebugDrawer.h"
    "ClientConfiguration.h"
    "ClientControl.h"
    "ClientState.h"
    "DrawCubes.h"
    "InitializeCmd.h"
    "MainMenuLogic.h"
    "MainMenuLogicResult.h"
    "OthuumGame.h"
    "PhysicalModel.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__ClientVisualization
    "ClientVisualization/ClientVisualization.h"
)
source_group("Header Files\\ClientVisualization" FILES ${Header_Files__ClientVisualization})

set(Header_Files__MainMenuPages
    "MainMenuPages/DialogPage.h"
    "MainMenuPages/ErrorPage.h"
    "MainMenuPages/GameLobbyPage.h"
    "MainMenuPages/HostGamePage.h"
    "MainMenuPages/HostLoadingPage.h"
    "MainMenuPages/JoinLoadingPage.h"
    "MainMenuPages/JoinLobbyPage.h"
    "MainMenuPages/LobbyLoadingPage.h"
    "MainMenuPages/LobbyPage.h"
    "MainMenuPages/MainMenuPage.h"
    "MainMenuPages/OptionsPage.h"
    "MainMenuPages/StartGameLoadingPage.h"
)
source_group("Header Files\\MainMenuPages" FILES ${Header_Files__MainMenuPages})

set(Header_Files__SideProject
    "SideProject/SideProjectMain.h"
)
source_group("Header Files\\SideProject" FILES ${Header_Files__SideProject})

set(Source_Files
    "BulletDebugDrawer.cpp"
    "ClientConfiguration.cpp"
    "ClientControl.cpp"
    "ClientState.cpp"
    "DrawCubes.cpp"
    "InitializeCmd.cpp"
    "main.cpp"
    "MainMenuLogic.cpp"
    "MainMenuLogicResult.cpp"
    "OthuumGame.cpp"
    "PhysicalModel.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__ClientVisualization
    "ClientVisualization/ClientVisualization.cpp"
)
source_group("Source Files\\ClientVisualization" FILES ${Source_Files__ClientVisualization})

set(Source_Files__MainMenuPages
    "MainMenuPages/DialogPage.cpp"
    "MainMenuPages/ErrorPage.cpp"
    "MainMenuPages/GameLobbyPage.cpp"
    "MainMenuPages/HostGamePage.cpp"
    "MainMenuPages/HostLoadingPage.cpp"
    "MainMenuPages/JoinLoadingPage.cpp"
    "MainMenuPages/JoinLobbyPage.cpp"
    "MainMenuPages/LobbyLoadingPage.cpp"
    "MainMenuPages/LobbyPage.cpp"
    "MainMenuPages/MainMenuPage.cpp"
    "MainMenuPages/OptionsPage.cpp"
    "MainMenuPages/StartGameLoadingPage.cpp"
)
source_group("Source Files\\MainMenuPages" FILES ${Source_Files__MainMenuPages})

set(Source_Files__SideProject
    "SideProject/SideProjectMain.cpp"
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

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "exe")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Othuum)

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
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../YolonaOss/Lib/glad/include"
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
                /Oi;
                /Gy
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /Oi;
                /Gy
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
            $<$<CONFIG:Debug>:
                /DEBUG:FASTLINK;
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /DEBUG;
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /DEBUG;
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
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
    AhwassaGraphicsLib
    HaasScriptingLib
    IyathuumCoreLib
    SelenNavigationLib
    SuthanusPhysicsLib
    UyanahGameServer
    VishalaNetworkLib
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "$(SolutionDir)x64/$(ConfigurationName)/AhwassaGraphicsLib"
        ">"
        "$<$<CONFIG:Release>:"
            "$(SolutionDir)x64/$(ConfigurationName)/AhwassaGraphicsLib"
        ">"
        "$<$<CONFIG:ReleaseWithDbg>:"
            "$(SolutionDir)x64/$(ConfigurationName)/YolonaOss"
        ">"
        "$(SolutionDir)x64/$(ConfigurationName)/VishalaNetworkLib;"
        "$(SolutionDir)x64/$(ConfigurationName)/SuthanusPhysicsLib;"
        "$(SolutionDir)x64/$(ConfigurationName)/HaasScriptingLib;"
        "$(SolutionDir)x64/$(ConfigurationName)/IyathuumCoreLib;"
        "$(SolutionDir)x64/$(ConfigurationName)/UyanahGameServer"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

