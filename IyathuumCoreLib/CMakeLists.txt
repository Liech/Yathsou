cmake_minimum_required(VERSION 2.8...3.20)

project(IyathuumCoreLib)

find_package(glm REQUIRED)

############################################################################
############################################################################
############################################################################

set(Header_Files
    "Source/IyathuumCoreLib/View2D.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Source/IyathuumCoreLib/View2D.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Header_Files__BaseTypes
    "Source/IyathuumCoreLib/BaseTypes/AABB.h"
    "Source/IyathuumCoreLib/BaseTypes/Color.h"
    "Source/IyathuumCoreLib/BaseTypes/Command.h"
    "Source/IyathuumCoreLib/BaseTypes/glmAABB.h"
    "Source/IyathuumCoreLib/BaseTypes/Keys.h"
    "Source/IyathuumCoreLib/BaseTypes/Line.h"
    "Source/IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
    "Source/IyathuumCoreLib/BaseTypes/Polygon.h"
    "Source/IyathuumCoreLib/BaseTypes/PolygonNet.h"
    "Source/IyathuumCoreLib/BaseTypes/Sound.h"
    "Source/IyathuumCoreLib/BaseTypes/Model3D.h"
)
source_group("Header Files\\BaseTypes" FILES ${Header_Files__BaseTypes})

set(Header_Files__API
    "Source/IyathuumCoreLib/API/API.h"
    "Source/IyathuumCoreLib/API/APIFunction.h"
    "Source/IyathuumCoreLib/API/FunctionRelay.h"
)
source_group("Header Files\\API" FILES ${Header_Files__API})

set(Header_Files__Mesh
    "Source/IyathuumCoreLib/Mesh/MarchingConvexPolygon.h"
    "Source/IyathuumCoreLib/Mesh/MarchingConvexPolygonNet.h"
)
source_group("Header Files\\Mesh" FILES ${Header_Files__Mesh})

set(Header_Files__Singleton
    "Source/IyathuumCoreLib/Singleton/Database.h"
    "Source/IyathuumCoreLib/Singleton/Factory.h"
)
source_group("Header Files\\Singleton" FILES ${Header_Files__Singleton})

set(Header_Files__Tree
    "Source/IyathuumCoreLib/Tree/Dijkstra.h"
    "Source/IyathuumCoreLib/Tree/glmOctree.h"
    "Source/IyathuumCoreLib/Tree/NMTree.h"
    "Source/IyathuumCoreLib/Tree/NMTreeDijkstra.h"
    "Source/IyathuumCoreLib/Tree/NMTreeNeighbourIndex.h"
    "Source/IyathuumCoreLib/Tree/NMTreeSpatialHash.h"
    "Source/IyathuumCoreLib/Tree/SpatialHash.h"
)
source_group("Header Files\\Tree" FILES ${Header_Files__Tree})

set(Header_Files__Util
    "Source/IyathuumCoreLib/Util/ConstExprHash.h"
    "Source/IyathuumCoreLib/Util/ContentLoader.h"
    "Source/IyathuumCoreLib/Util/Geometry.h"
    "Source/IyathuumCoreLib/Util/ImageSubsetUtil.h"
    "Source/IyathuumCoreLib/Util/ImageUtil.h"
    "Source/IyathuumCoreLib/Util/lambdaCapture2functionPointer.h"
    "Source/IyathuumCoreLib/Util/Scheduler.h"
    "Source/IyathuumCoreLib/Util/UpdateTimer.h"
    "Source/IyathuumCoreLib/Util/StateMachine.h"
    "Source/IyathuumCoreLib/Util/State.h"
    "Source/IyathuumCoreLib/Util/StateTransition.h"
)
source_group("Header Files\\Util" FILES ${Header_Files__Util})

set(Source_Files__BaseTypes
    "Source/IyathuumCoreLib/BaseTypes/AABB.cpp"
    "Source/IyathuumCoreLib/BaseTypes/Color.cpp"
    "Source/IyathuumCoreLib/BaseTypes/Key.cpp"
    "Source/IyathuumCoreLib/BaseTypes/Sound.cpp"
    "Source/IyathuumCoreLib/BaseTypes/Model3D.cpp"
)
source_group("Source Files\\BaseTypes" FILES ${Source_Files__BaseTypes})

set(Source_Files__API
    "Source/IyathuumCoreLib/API/API.cpp"
    "Source/IyathuumCoreLib/API/APIFunction.cpp"
    "Source/IyathuumCoreLib/API/FunctionRelay.h"
)
source_group("Source Files\\API" FILES ${Source_Files__API})


set(Source_Files__Tree
    "Source/IyathuumCoreLib/Tree/glmOctree.cpp"
)
source_group("Source Files\\Tree" FILES ${Source_Files__Tree})

set(Source_Files__Util
    "Source/IyathuumCoreLib/Util/ConstExprHash.cpp"
    "Source/IyathuumCoreLib/Util/ContentLoader.cpp"
    "Source/IyathuumCoreLib/Util/ImageSubsetUtil.cpp"
    "Source/IyathuumCoreLib/Util/ImageUtil.cpp"
    "Source/IyathuumCoreLib/Util/Scheduler.cpp"
    "Source/IyathuumCoreLib/Util/UpdateTimer.cpp"
    "Source/IyathuumCoreLib/Util/StateMachine.cpp"
    "Source/IyathuumCoreLib/Util/State.cpp"
    "Source/IyathuumCoreLib/Util/StateTransition.cpp"
)
source_group("Source Files\\Util" FILES ${Source_Files__Util})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__BaseTypes}
    ${Header_Files__Mesh}
    ${Header_Files__Singleton}
    ${Header_Files__Tree}
    ${Header_Files__Util}
    ${Source_Files}
    ${Source_Files__BaseTypes}
    ${Source_Files__Tree}
    ${Source_Files__Util}
    ${Header_Files__API}
    ${Source_Files__API}
)

############################################################################
############################################################################
############################################################################

add_library(IyathuumCoreLib ${ALL_FILES})
set_property(TARGET IyathuumCoreLib PROPERTY CXX_STANDARD 20)

target_link_libraries(IyathuumCoreLib PRIVATE
glm::glm
)

target_include_directories(IyathuumCoreLib PRIVATE
${glm_SOURCE_DIR} 
${CMAKE_CURRENT_SOURCE_DIR}/Source
)
set_target_properties(IyathuumCoreLib PROPERTIES FOLDER "Yathsou")