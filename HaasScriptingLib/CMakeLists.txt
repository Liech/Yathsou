cmake_minimum_required(VERSION 2.8...3.23)
project(HaasScriptingLib)

find_package(nlohmann_json REQUIRED)
find_package(lua REQUIRED)

############################################################################
############################################################################
############################################################################
set(Header_Files
    "Source/HaasScriptingLib/ScriptEngine.h"
    "Source/HaasScriptingLib/PythonEngine.h"
    "Source/HaasScriptingLib/PyFunctionRelay.h"
    "Source/HaasScriptingLib/PyConversion.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Source/HaasScriptingLib/ScriptEngine.cpp"
    "Source/HaasScriptingLib/PythonEngine.cpp"
    "Source/HaasScriptingLib/PyFunctionRelay.cpp"
    "Source/HaasScriptingLib/PyConversion.cpp"
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