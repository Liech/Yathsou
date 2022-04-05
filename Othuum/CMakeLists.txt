cmake_minimum_required(VERSION 3.23)
project(Othuum)

add_subdirectory(IyathuumCoreLib)
add_subdirectory(SelenNavigationLib)
add_subdirectory(SuthanusPhysicsLib)
add_subdirectory(AhwassaGraphicsLib)
add_subdirectory(HaasScriptingLib)
add_subdirectory(TestExe)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT TestExe)