cmake_minimum_required(VERSION 2.8...3.23)
project(SelenNavigationLib)

find_package(glm REQUIRED)

############################################################################
############################################################################
############################################################################

set(Header_Files
    "Source/SelenNavigationLib/AgentGroup.h"
    "Source/SelenNavigationLib/AgentMovementInterface.h"
    "Source/SelenNavigationLib/DirectTargetMovement.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Maps
    "Source/SelenNavigationLib/Maps/AligmentMap.h"
    "Source/SelenNavigationLib/Maps/ComfortMap.h"
    "Source/SelenNavigationLib/Maps/DijkstraMap.h"
    "Source/SelenNavigationLib/Maps/DirectDistanceMap.h"
    "Source/SelenNavigationLib/Maps/DiscomfortMap.h"
    "Source/SelenNavigationLib/Maps/GradientGridMap.h"
    "Source/SelenNavigationLib/Maps/InfectiousArrivalMapGroup.h"
    "Source/SelenNavigationLib/Maps/MapGroup.h"
    "Source/SelenNavigationLib/Maps/NavigationAgent.h"
    "Source/SelenNavigationLib/Maps/NavigationAgentManager.h"
    "Source/SelenNavigationLib/Maps/NavigationMap.h"
    "Source/SelenNavigationLib/Maps/PersonalSpaceMap.h"
)
source_group("Header Files\\Maps" FILES ${Header_Files__Maps})

set(Source_Files
    "Source/SelenNavigationLib/AgentGroup.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Maps
    "Source/SelenNavigationLib/Maps/DijkstraMap.cpp"
    "Source/SelenNavigationLib/Maps/DirectDistanceMap.cpp"
    "Source/SelenNavigationLib/Maps/GradientGridMap.cpp"
    "Source/SelenNavigationLib/Maps/MapGroup.cpp"
    "Source/SelenNavigationLib/Maps/NavigationAgent.cpp"
    "Source/SelenNavigationLib/Maps/NavigationMap.cpp"
    "Source/SelenNavigationLib/Maps/PersonalSpaceMap.cpp"
)
source_group("Source Files\\Maps" FILES ${Source_Files__Maps})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__Maps}
    ${Source_Files}
    ${Source_Files__Maps}
)


############################################################################
############################################################################
############################################################################

add_library(SelenNavigationLib ${ALL_FILES})
set_property(TARGET SelenNavigationLib PROPERTY CXX_STANDARD 20)

target_link_libraries(SelenNavigationLib PRIVATE
IyathuumCoreLib
glm::glm
)

target_include_directories(SelenNavigationLib PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/Source/SelenNavigationLib
"${IyathuumCoreLib_SOURCE_DIR}/Source"
)