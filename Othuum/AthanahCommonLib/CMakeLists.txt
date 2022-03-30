set(PROJECT_NAME AthanahCommonLib)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "SkyBox.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Map
    "Map/Map.h"
    "Map/MapFactory.h"
    "Map/MapRenderer.h"
    "Map/Scenario.h"
)
source_group("Header Files\\Map" FILES ${Header_Files__Map})

set(Header_Files__Physic
    "Physic/BoxVisualization.h"
    "Physic/BulletDebugDrawer.h"
    "Physic/NavigationMeshDebugDrawer.h"
)
source_group("Header Files\\Physic" FILES ${Header_Files__Physic})

set(Header_Files__SupCom
    "Model3DRenderer.h"
    "SupCom/SupComEnums.h"
    "SupCom/SupComMeshLoader.h"
    "SupCom/SupComMeshRenderer.h"
    "SupCom/SupComMeshRendererDef.h"
    "SupCom/SupComModel.h"
    "SupCom/SupComVertex.h"
)
source_group("Header Files\\SupCom" FILES ${Header_Files__SupCom})

set(Header_Files__SupCom__Blueprint
    "SupCom/Blueprint/Blueprint.h"
    "SupCom/Blueprint/BlueprintBase.h"
    "SupCom/Blueprint/BlueprintCommandCaps.h"
    "SupCom/Blueprint/BlueprintDisplay.h"
    "SupCom/Blueprint/BlueprintGeneral.h"
    "SupCom/Blueprint/BlueprintPhysic.h"
)
source_group("Header Files\\SupCom\\Blueprint" FILES ${Header_Files__SupCom__Blueprint})

set(Header_Files__SupCom__Gamedata
    "SupCom/Gamedata/BlueprintFactory.h"
    "SupCom/Gamedata/Gamedata.h"
    "SupCom/Gamedata/SkyboxFactory.h"
    "SupCom/Gamedata/SupComModelFactory.h"
    "SupCom/Gamedata/UiTextureFactory.h"
)
source_group("Header Files\\SupCom\\Gamedata" FILES ${Header_Files__SupCom__Gamedata})

set(Source_Files
    "Model3DRenderer.cpp"
    "SkyBox.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Map
    "Map/Map.cpp"
    "Map/MapFactory.cpp"
    "Map/MapRenderer.cpp"
    "Map/Scenario.cpp"
)
source_group("Source Files\\Map" FILES ${Source_Files__Map})

set(Source_Files__Physic
    "Physic/BoxVisualization.cpp"
    "Physic/BulletDebugDrawer.cpp"
    "Physic/NavigationMeshDebugDrawer.cpp"
)
source_group("Source Files\\Physic" FILES ${Source_Files__Physic})

set(Source_Files__SupCom
    "SupCom/SupComMeshLoader.cpp"
    "SupCom/SupComMeshRenderer.cpp"
    "SupCom/SupComMeshRendererDef.cpp"
    "SupCom/SupComModel.cpp"
    "SupCom/SupComVertex.cpp"
)
source_group("Source Files\\SupCom" FILES ${Source_Files__SupCom})

set(Source_Files__SupCom__Blueprint
    "SupCom/Blueprint/Blueprint.cpp"
    "SupCom/Blueprint/BlueprintCommandCaps.cpp"
    "SupCom/Blueprint/BlueprintDisplay.cpp"
    "SupCom/Blueprint/BlueprintGeneral.cpp"
    "SupCom/Blueprint/BlueprintPhysic.cpp"
)
source_group("Source Files\\SupCom\\Blueprint" FILES ${Source_Files__SupCom__Blueprint})

set(Source_Files__SupCom__Gamedata
    "SupCom/Gamedata/BlueprintFactory.cpp"
    "SupCom/Gamedata/Gamedata.cpp"
    "SupCom/Gamedata/SkyboxFactory.cpp"
    "SupCom/Gamedata/SupComModelFactory.cpp"
    "SupCom/Gamedata/UITextureFactory.cpp"
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

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE AthanahCommonLib)

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
    AezeselFileIOLib
    AhwassaGraphicsLib
    HaasScriptingLib
    IyathuumCoreLib
    SuthanusPhysicsLib
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$(SolutionDir)x64/$(ConfigurationName)/VishalaNetworkLib;"
        "$(SolutionDir)x64/$(ConfigurationName)/SuthanusPhysicsLib;"
        "$(SolutionDir)x64/$(ConfigurationName)/HaasScriptingLib;"
        "$(SolutionDir)x64/$(ConfigurationName)/IyathuumCoreLib;"
        "$(SolutionDir)x64/$(ConfigurationName)/AhwassaGraphicsLib"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

