cmake_minimum_required(VERSION 2.8...3.23)
project(HaasScriptingLib)

find_package(nlohmann_json REQUIRED)
find_package(lua REQUIRED)

############################################################################
############################################################################
############################################################################
set(Header_FilesLua
    "Source/HaasScriptingLib/Lua/LuaEngine.h"
    "Source/HaasScriptingLib/Lua/Conversion.h"
    "Source/HaasScriptingLib/Lua/FunctionRelay.h"
)
source_group("Header Files/Lua" FILES ${Header_FilesLua})

set(Source_FilesLua
    "Source/HaasScriptingLib/Lua/LuaEngine.cpp"
    "Source/HaasScriptingLib/Lua/Conversion.cpp"
    "Source/HaasScriptingLib/Lua/FunctionRelay.cpp"
)
source_group("Source Files/Lua" FILES ${Source_FilesLua})

set(Header_FilesPy
    "Source/HaasScriptingLib/Python/PythonEngine.h"
    "Source/HaasScriptingLib/Python/FunctionRelay.h"
    "Source/HaasScriptingLib/Python/Conversion.h"
)
source_group("Header Files/Python" FILES ${Header_FilesPy})

set(Source_FilesPy
    "Source/HaasScriptingLib/Python/PythonEngine.cpp"
    "Source/HaasScriptingLib/Python/FunctionRelay.cpp"
    "Source/HaasScriptingLib/Python/Conversion.cpp"
)
source_group("Source Files/Python" FILES ${Source_FilesPy})


set(ALL_FILES
    ${Header_FilesPy}
    ${Source_FilesPy}
    ${Header_FilesLua}
    ${Source_FilesLua}
    ${lib}
)

############################################################################
############################################################################
############################################################################


add_library(HaasScriptingLib ${ALL_FILES})
set_property(TARGET HaasScriptingLib PROPERTY CXX_STANDARD 20)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

find_library(pythonlibrary
    NAMES python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}
    HINTS "${CMAKE_PREFIX_PATH}/lib"
    REQUIRED
)

find_library(pythonlibraryDebug
    NAMES python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}_d
    HINTS "${CMAKE_PREFIX_PATH}/lib"
    REQUIRED
)
target_include_directories(HaasScriptingLib SYSTEM PRIVATE 
${Python3_INCLUDE_DIRS}
"${IyathuumCoreLib_SOURCE_DIR}/Source"
)

target_link_libraries(HaasScriptingLib PRIVATE
debug ${pythonlibraryDebug}
optimized ${pythonlibrary}
)

find_package(pybind11 CONFIG REQUIRED)

target_link_libraries(HaasScriptingLib PRIVATE
nlohmann_json::nlohmann_json 
lua
pybind11::headers
)




set_target_properties(HaasScriptingLib PROPERTIES FOLDER "Yathsou")