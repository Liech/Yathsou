cmake_minimum_required(VERSION 2.8...3.23)
project(HaasScriptingLib)

find_package(nlohmann_json REQUIRED)
find_package(lua REQUIRED)

############################################################################
############################################################################
############################################################################
set(Header_Files
    "Source/HaasScriptingLib/ScriptEngine.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Source/HaasScriptingLib/ScriptEngine.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
    ${lib}
)


############################################################################
############################################################################
############################################################################

add_library(HaasScriptingLib ${ALL_FILES})
set_property(TARGET HaasScriptingLib PROPERTY CXX_STANDARD 20)

target_link_libraries(HaasScriptingLib nlohmann_json::nlohmann_json lua)
target_include_directories(HaasScriptingLib PRIVATE 
)