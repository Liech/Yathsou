set(PROJECT_NAME SuperbCommander)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "Config.h"
    "DriveInterface.h"
    "NavigationUI.h"
    "PhysicsDebugView.h"
    "Spheres.h"
    "UnitsOld.h"
    "UnitsVisualization.h"
    "World.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Formation
    "Formation/FormationDialog.h"
    "Formation/FormationWidget.h"
    "Formation/Selector.h"
)
source_group("Header Files\\Formation" FILES ${Header_Files__Formation})

set(Header_Files__Formation__Shapes
    "Formation/Shapes/CircleShape.h"
    "Formation/Shapes/FormationShape.h"
    "Formation/Shapes/RectangleShape.h"
    "Formation/Shapes/TriangleShape.h"
)
source_group("Header Files\\Formation\\Shapes" FILES ${Header_Files__Formation__Shapes})

set(Header_Files__Game
    "Game/Control.h"
    "Game/Database.h"
    "Game/Game.h"
    "Game/NonGame.h"
    "Game/Overlay.h"
    "Game/Physic.h"
    "Game/Terrain.h"
    "Game/Units.h"
    "Game/Visualization.h"
)
source_group("Header Files\\Game" FILES ${Header_Files__Game})

set(Header_Files__Unit
    "Unit/Unit.h"
    "Unit/UnitAgentInterface.h"
    "Unit/UnitConstructor.h"
    "Unit/WheeledSteeringAgent.h"
)
source_group("Header Files\\Unit" FILES ${Header_Files__Unit})

set(Source_Files
    "Config.cpp"
    "DriveInterface.cpp"
    "main.cpp"
    "NavigationUI.cpp"
    "PhysicsDebugView.cpp"
    "Spheres.cpp"
    "UnitsOld.cpp"
    "UnitsVisualization.cpp"
    "World.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Formation
    "Formation/FormationDialog.cpp"
    "Formation/FormationWidget.cpp"
    "Formation/Selector.cpp"
)
source_group("Source Files\\Formation" FILES ${Source_Files__Formation})

set(Source_Files__Formation__Shapes
    "Formation/Shapes/CircleShape.cpp"
    "Formation/Shapes/FormationShape.cpp"
    "Formation/Shapes/RectangleShape.cpp"
    "Formation/Shapes/TriangleShape.cpp"
)
source_group("Source Files\\Formation\\Shapes" FILES ${Source_Files__Formation__Shapes})

set(Source_Files__Game
    "Game/Control.cpp"
    "Game/Database.cpp"
    "Game/Game.cpp"
    "Game/NonGame.cpp"
    "Game/Overlay.cpp"
    "Game/Physic.cpp"
    "Game/Terrain.cpp"
    "Game/Units.cpp"
    "Game/Visualization.cpp"
)
source_group("Source Files\\Game" FILES ${Source_Files__Game})

set(Source_Files__Unit
    "Unit/Unit.cpp"
    "Unit/UnitConstructor.cpp"
    "Unit/WheeledSteeringAgent.cpp"
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

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "exe")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE SuperbCommander)

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
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
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
    AezeselFileIOLib
    AhwassaGraphicsLib
    AthanahCommonLib
    IyathuumCoreLib
    SelenNavigationLib
    SuthanusPhysicsLib
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$(TargetDir)AhwassaGraphicsLib;"
        "$(TargetDir)VishalaNetworkLib;"
        "$(TargetDir)IyathuumCoreLib;"
        "$(TargetDir)AezeselFileIOLib;"
        "$(TargetDir)SuthanusPhysicsLib;"
        "$(TargetDir)AthanahCommonLib;"
        "$(TargetDir)SelenNavigationLib"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

