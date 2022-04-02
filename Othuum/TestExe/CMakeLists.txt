cmake_minimum_required(VERSION 3.23)
project(TestExe)
add_executable(TestExe main.cpp)
set_property(TARGET TestExe PROPERTY CXX_STANDARD 20)

target_link_libraries(TestExe 
IyathuumCoreLib 
SelenNavigationLib
SuthanusPhysicLib
)

target_include_directories(TestExe PRIVATE 
"${IyathuumCoreLib_SOURCE_DIR}/Source"
"${SelenNavigationLib_SOURCE_DIR}/Source"
"${SuthanusPhysicLib_SOURCE_DIR}/Source"
)

add_dependencies(TestExe 
IyathuumCoreLib 
SelenNavigationLib
SuthanusPhysicLib
)