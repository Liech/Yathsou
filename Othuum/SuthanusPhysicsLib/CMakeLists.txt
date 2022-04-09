cmake_minimum_required(VERSION 2.8...3.23)
project(SuthanusPhysicLib)
include(FetchContent)

FetchContent_Declare(
  bullet
  GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
  GIT_TAG        3.22b
)
FetchContent_MakeAvailable(bullet)

############################################################################
############################################################################
############################################################################

set(Headerdateien
    "Source/SuthanusPhysicsLib/ArtilleryAim.h"
    "Source/SuthanusPhysicsLib/PhysicEngine.h"
    "Source/SuthanusPhysicsLib/PhysicNavigationMesh.h"
    "Source/SuthanusPhysicsLib/VehicleDriver.h"
)
source_group("Headerdateien" FILES ${Headerdateien})

set(Headerdateien__Objects
    "Source/SuthanusPhysicsLib/Objects/Box.h"
    "Source/SuthanusPhysicsLib/Objects/BoxBullet.h"
    "Source/SuthanusPhysicsLib/Objects/BulletCore.h"
    "Source/SuthanusPhysicsLib/Objects/HeightMap.cpp"
    "Source/SuthanusPhysicsLib/Objects/HeightMap.h"
    "Source/SuthanusPhysicsLib/Objects/HeightMapBullet.h"
    "Source/SuthanusPhysicsLib/Objects/PhysicObject.h"
    "Source/SuthanusPhysicsLib/Objects/Sphere.h"
    "Source/SuthanusPhysicsLib/Objects/SphereBullet.h"
    "Source/SuthanusPhysicsLib/Objects/Vehicle.cpp"
    "Source/SuthanusPhysicsLib/Objects/Vehicle.h"
    "Source/SuthanusPhysicsLib/Objects/VehicleBulletRaycast.h"
)
source_group("Headerdateien\\Objects" FILES ${Headerdateien__Objects})

set(Quelldateien
    "Source/SuthanusPhysicsLib/ArtilleryAim.cpp"
    "Source/SuthanusPhysicsLib/PhysicEngine.cpp"
    "Source/SuthanusPhysicsLib/PhysicNavigationMesh.cpp"
    "Source/SuthanusPhysicsLib/VehicleDriver.cpp"
)
source_group("Quelldateien" FILES ${Quelldateien})

set(Quelldateien__Objects
    "Source/SuthanusPhysicsLib/Objects/Box.cpp"
    "Source/SuthanusPhysicsLib/Objects/BoxBullet.cpp"
    "Source/SuthanusPhysicsLib/Objects/BulletCore.cpp"
    "Source/SuthanusPhysicsLib/Objects/HeightMapBullet.cpp"
    "Source/SuthanusPhysicsLib/Objects/PhysicObject.cpp"
    "Source/SuthanusPhysicsLib/Objects/Sphere.cpp"
    "Source/SuthanusPhysicsLib/Objects/SphereBullet.cpp"
    "Source/SuthanusPhysicsLib/Objects/VehicleBulletRaycast.cpp"
)
source_group("Quelldateien\\Objects" FILES ${Quelldateien__Objects})

set(ALL_FILES
    ${Headerdateien}
    ${Headerdateien__Objects}
    ${Quelldateien}
    ${Quelldateien__Objects}
)

############################################################################
############################################################################
############################################################################

add_library(SuthanusPhysicLib ${ALL_FILES})
set_property(TARGET SuthanusPhysicLib PROPERTY CXX_STANDARD 20)

target_link_libraries(SuthanusPhysicLib
glm
IyathuumCoreLib
LinearMath
Bullet3Common
BulletCollision
BulletDynamics
)

target_include_directories(SuthanusPhysicLib PRIVATE 
"${SuthanusPhysicLib_SOURCE_DIR}/Source/SuthanusPhysicsLib"
"${IyathuumCoreLib_SOURCE_DIR}/Source"
"${bullet_SOURCE_DIR}/src"
)

include_directories(ThirdParty/bullet/src)

add_dependencies(SuthanusPhysicLib glm)
add_dependencies(SuthanusPhysicLib IyathuumCoreLib)