cmake_minimum_required(VERSION 2.8...3.23)
project(AezeselFileIOLib)
include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.10.5
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
  GIT_TAG        v5.2.3
)
FetchContent_MakeAvailable(assimp)

set(GLI_TEST_ENABLE OFF CACHE INTERNAL "")
FetchContent_Declare(
  gli
  GIT_REPOSITORY https://github.com/g-truc/gli.git
  GIT_TAG        0.8.2.0
)
FetchContent_MakeAvailable(gli)

FetchContent_Declare(
  libnyquist
  GIT_REPOSITORY https://github.com/ddiakopoulos/libnyquist.git
  GIT_TAG        d389ac419dae89a95f83f202a956e3f4846313c3
)
FetchContent_MakeAvailable(libnyquist)

FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG        5601b8272a6850b7c5d693dd0c0e16da50be8d8d
)
FetchContent_MakeAvailable(lodepng)

FetchContent_Declare(
  zipper
  GIT_REPOSITORY https://github.com/sebastiandev/zipper.git
  GIT_TAG        v1.0.0
)
FetchContent_MakeAvailable(zipper)

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

set(lib__lodepng
    "${lodepng_SOURCE_DIR}/lodepng.cpp"
    "${lodepng_SOURCE_DIR}/lodepng.h"
    "${lodepng_SOURCE_DIR}/lodepng_util.cpp"
    "${lodepng_SOURCE_DIR}/lodepng_util.h"
)
source_group("lib\\lodepng" FILES ${lib__lodepng})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__MagickaVox}
    ${Header_Files__Sound}
    ${Header_Files__SupremeCommander}
    ${Source_Files}
    ${Source_Files__MagickaVox}
    ${Source_Files__Sound}
    ${Source_Files__SupremeCommander}
    ${lib__lodepng}
)


############################################################################
############################################################################
############################################################################

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/zipper)

add_library(AezeselFileIOLib ${ALL_FILES})
set_property(TARGET AezeselFileIOLib PROPERTY CXX_STANDARD 20)

target_link_libraries(AezeselFileIOLib 
IyathuumCoreLib 
gli 
assimp 
zipper
libnyquist
)

target_include_directories(AezeselFileIOLib PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/Source/AezeselFileIOLib
${CMAKE_CURRENT_SOURCE_DIR}/lib
"${IyathuumCoreLib_SOURCE_DIR}/Source"
${json_SOURCE_DIR}/include
${assimp_SOURCE_DIR}/include
${assimp_SOURCE_DIR}/..
${glm_SOURCE_DIR} 
${gli_SOURCE_DIR} 
${zipper_SOURCE_DIR} 
${zipper_SOURCE_DIR}/include
)

add_dependencies(IyathuumCoreLib glm)