cmake_minimum_required(VERSION 2.8...3.20)
project(AezeselFileIOLib)
include(FetchContent)

find_package(nlohmann_json REQUIRED)
find_package(assimp REQUIRED)
find_package(gli REQUIRED)
find_package(lodepng REQUIRED)

############################################################################
############################################################################
############################################################################

set(Header_Files
    "Source/AezeselFileIOLib/AssimpUtil.h"
    "Source/AezeselFileIOLib/ImageIO.h"
    "Source/AezeselFileIOLib/IO.h"
    "Source/AezeselFileIOLib/Model3D.h"
    "Source/AezeselFileIOLib/STLWriter.h"
    "Source/AezeselFileIOLib/ZIP.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__MagickaVox
    "Source/AezeselFileIOLib/MagicaVox/Chunk.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunkFactory.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunkLAYR.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunkMAIN.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunkMATL.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunknGRP.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunknSHP.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunknTRN.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunkPACK.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunkRGBA.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunkrOBJ.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunkSIZE.h"
    "Source/AezeselFileIOLib/MagicaVox/ChunkXYZI.h"
    "Source/AezeselFileIOLib/MagicaVox/Import.h"
    "Source/AezeselFileIOLib/MagicaVox/Reader.h"
    "Source/AezeselFileIOLib/MagicaVox/typeDICT.h"
    "Source/AezeselFileIOLib/MagicaVox/typeROTATION.h"
    "Source/AezeselFileIOLib/MagicaVox/VoxFile.h"
)
source_group("Header Files\\MagickaVox" FILES ${Header_Files__MagickaVox})

set(Header_Files__Sound
    "Source/AezeselFileIOLib/Sound/SoundFactory.h"
    "Source/AezeselFileIOLib/Sound/SoundIO.h"
    "Source/AezeselFileIOLib/Sound/XSB.h"
    "Source/AezeselFileIOLib/Sound/XWB.h"
)
source_group("Header Files\\Sound" FILES ${Header_Files__Sound})

set(Header_Files__SupremeCommander
    "Source/AezeselFileIOLib/SupremeCommander/SCA.h"
    "Source/AezeselFileIOLib/SupremeCommander/SCD.h"
    "Source/AezeselFileIOLib/SupremeCommander/SCM.h"
    "Source/AezeselFileIOLib/SupremeCommander/SCMAP.h"
    "Source/AezeselFileIOLib/SupremeCommander/SupremeCommanderAnimator.h"
)
source_group("Header Files\\SupremeCommander" FILES ${Header_Files__SupremeCommander})

set(Source_Files
    "Source/AezeselFileIOLib/AssimpUtil.cpp"
    "Source/AezeselFileIOLib/ImageIO.cpp"
    "Source/AezeselFileIOLib/IO.cpp"
    "Source/AezeselFileIOLib/Model3D.cpp"
    "Source/AezeselFileIOLib/STLWriter.cpp"
    "Source/AezeselFileIOLib/ZIP.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__MagickaVox
    "Source/AezeselFileIOLib/MagicaVox/Chunk.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunkFactory.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunkLAYR.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunkMAIN.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunkMATL.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunknGRP.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunknSHP.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunknTRN.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunkPACK.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunkRGBA.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunkrOBJ.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunkSIZE.cpp"
    "Source/AezeselFileIOLib/MagicaVox/ChunkXYZI.cpp"
    "Source/AezeselFileIOLib/MagicaVox/Import.cpp"
    "Source/AezeselFileIOLib/MagicaVox/Reader.cpp"
    "Source/AezeselFileIOLib/MagicaVox/typeDICT.cpp"
    "Source/AezeselFileIOLib/MagicaVox/typeROTATION.cpp"
    "Source/AezeselFileIOLib/MagicaVox/VoxFile.cpp"
)
source_group("Source Files\\MagickaVox" FILES ${Source_Files__MagickaVox})

set(Source_Files__Sound
    "Source/AezeselFileIOLib/Sound/SoundFactory.cpp"
    "Source/AezeselFileIOLib/Sound/SoundIO.cpp"
    "Source/AezeselFileIOLib/Sound/XSB.cpp"
    "Source/AezeselFileIOLib/Sound/XWB.cpp"
)
source_group("Source Files\\Sound" FILES ${Source_Files__Sound})

set(Source_Files__SupremeCommander
    "Source/AezeselFileIOLib/SupremeCommander/SCA.cpp"
    "Source/AezeselFileIOLib/SupremeCommander/SCD.cpp"
    "Source/AezeselFileIOLib/SupremeCommander/SCM.cpp"
    "Source/AezeselFileIOLib/SupremeCommander/SCMAP.cpp"
    "Source/AezeselFileIOLib/SupremeCommander/SupremeCommanderAnimator.cpp"
)
source_group("Source Files\\SupremeCommander" FILES ${Source_Files__SupremeCommander})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__MagickaVox}
    ${Header_Files__Sound}
    ${Header_Files__SupremeCommander}
    ${Source_Files}
    ${Source_Files__MagickaVox}
    ${Source_Files__Sound}
    ${Source_Files__SupremeCommander}
)


############################################################################
############################################################################
############################################################################

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/zipper)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/libnyquist)

add_library(AezeselFileIOLib ${ALL_FILES})
set_property(TARGET AezeselFileIOLib PROPERTY CXX_STANDARD 20)

target_link_libraries(AezeselFileIOLib 
IyathuumCoreLib 
gli 
${ASSIMP_LIBRARIES} 
staticZipper
libnyquist
nlohmann_json::nlohmann_json
)

target_include_directories(AezeselFileIOLib PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/Source/AezeselFileIOLib
${CMAKE_CURRENT_SOURCE_DIR}/lib
"${IyathuumCoreLib_SOURCE_DIR}/Source"
${assimp_SOURCE_DIR}/include
${assimp_SOURCE_DIR}/..
${glm_SOURCE_DIR} 
${gli_SOURCE_DIR} 
${zipper_SOURCE_DIR} 
${zipper_SOURCE_DIR}/include
"${lodepng_SOURCE_DIR}"
${libnyquist_SOURCE_DIR}
)