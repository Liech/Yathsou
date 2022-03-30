set(PROJECT_NAME AezeselFileIOLib)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "AssimpUtil.h"
    "ImageIO.h"
    "IO.h"
    "Model3D.h"
    "STLWriter.h"
    "ZIP.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__MagickaVox
    "MagicaVox/Chunk.h"
    "MagicaVox/ChunkFactory.h"
    "MagicaVox/ChunkLAYR.h"
    "MagicaVox/ChunkMAIN.h"
    "MagicaVox/ChunkMATL.h"
    "MagicaVox/ChunknGRP.h"
    "MagicaVox/ChunknSHP.h"
    "MagicaVox/ChunknTRN.h"
    "MagicaVox/ChunkPACK.h"
    "MagicaVox/ChunkRGBA.h"
    "MagicaVox/ChunkrOBJ.h"
    "MagicaVox/ChunkSIZE.h"
    "MagicaVox/ChunkXYZI.h"
    "MagicaVox/Import.h"
    "MagicaVox/Reader.h"
    "MagicaVox/typeDICT.h"
    "MagicaVox/typeROTATION.h"
    "MagicaVox/VoxFile.h"
)
source_group("Header Files\\MagickaVox" FILES ${Header_Files__MagickaVox})

set(Header_Files__Sound
    "Sound/SoundFactory.h"
    "Sound/SoundIO.h"
    "Sound/XSB.h"
    "Sound/XWB.h"
)
source_group("Header Files\\Sound" FILES ${Header_Files__Sound})

set(Header_Files__SupremeCommander
    "SupremeCommander/SCA.h"
    "SupremeCommander/SCD.h"
    "SupremeCommander/SCM.h"
    "SupremeCommander/SCMAP.h"
    "SupremeCommander/SupremeCommanderAnimator.h"
)
source_group("Header Files\\SupremeCommander" FILES ${Header_Files__SupremeCommander})

set(Source_Files
    "AssimpUtil.cpp"
    "ImageIO.cpp"
    "IO.cpp"
    "Model3D.cpp"
    "STLWriter.cpp"
    "ZIP.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__MagickaVox
    "MagicaVox/Chunk.cpp"
    "MagicaVox/ChunkFactory.cpp"
    "MagicaVox/ChunkLAYR.cpp"
    "MagicaVox/ChunkMAIN.cpp"
    "MagicaVox/ChunkMATL.cpp"
    "MagicaVox/ChunknGRP.cpp"
    "MagicaVox/ChunknSHP.cpp"
    "MagicaVox/ChunknTRN.cpp"
    "MagicaVox/ChunkPACK.cpp"
    "MagicaVox/ChunkRGBA.cpp"
    "MagicaVox/ChunkrOBJ.cpp"
    "MagicaVox/ChunkSIZE.cpp"
    "MagicaVox/ChunkXYZI.cpp"
    "MagicaVox/Import.cpp"
    "MagicaVox/Reader.cpp"
    "MagicaVox/typeDICT.cpp"
    "MagicaVox/typeROTATION.cpp"
    "MagicaVox/VoxFile.cpp"
)
source_group("Source Files\\MagickaVox" FILES ${Source_Files__MagickaVox})

set(Source_Files__Sound
    "Sound/SoundFactory.cpp"
    "Sound/SoundIO.cpp"
    "Sound/XSB.cpp"
    "Sound/XWB.cpp"
)
source_group("Source Files\\Sound" FILES ${Source_Files__Sound})

set(Source_Files__SupremeCommander
    "SupremeCommander/SCA.cpp"
    "SupremeCommander/SCD.cpp"
    "SupremeCommander/SCM.cpp"
    "SupremeCommander/SCMAP.cpp"
    "SupremeCommander/SupremeCommanderAnimator.cpp"
)
source_group("Source Files\\SupremeCommander" FILES ${Source_Files__SupremeCommander})

set(lib
    "lib/json.hpp"
    "lib/json_fwd.hpp"
)
source_group("lib" FILES ${lib})

set(lib__assimp
    "lib/assimp/aabb.h"
    "lib/assimp/ai_assert.h"
    "lib/assimp/anim.h"
    "lib/assimp/BaseImporter.h"
    "lib/assimp/Bitmap.h"
    "lib/assimp/BlobIOSystem.h"
    "lib/assimp/ByteSwapper.h"
    "lib/assimp/camera.h"
    "lib/assimp/cexport.h"
    "lib/assimp/cfileio.h"
    "lib/assimp/cimport.h"
    "lib/assimp/ColladaMetaData.h"
    "lib/assimp/color4.h"
    "lib/assimp/color4.inl"
    "lib/assimp/commonMetaData.h"
    "lib/assimp/Compiler/poppack1.h"
    "lib/assimp/Compiler/pstdint.h"
    "lib/assimp/Compiler/pushpack1.h"
    "lib/assimp/config.h"
    "lib/assimp/config.h.in"
    "lib/assimp/CreateAnimMesh.h"
    "lib/assimp/DefaultIOStream.h"
    "lib/assimp/DefaultIOSystem.h"
    "lib/assimp/DefaultLogger.hpp"
    "lib/assimp/Defines.h"
    "lib/assimp/defs.h"
    "lib/assimp/Exceptional.h"
    "lib/assimp/Exporter.hpp"
    "lib/assimp/fast_atof.h"
    "lib/assimp/GenericProperty.h"
    "lib/assimp/Hash.h"
    "lib/assimp/Importer.hpp"
    "lib/assimp/importerdesc.h"
    "lib/assimp/IOStream.hpp"
    "lib/assimp/IOStreamBuffer.h"
    "lib/assimp/IOSystem.hpp"
    "lib/assimp/light.h"
    "lib/assimp/LineSplitter.h"
    "lib/assimp/LogAux.h"
    "lib/assimp/Logger.hpp"
    "lib/assimp/LogStream.hpp"
    "lib/assimp/material.h"
    "lib/assimp/material.inl"
    "lib/assimp/MathFunctions.h"
    "lib/assimp/matrix3x3.h"
    "lib/assimp/matrix3x3.inl"
    "lib/assimp/matrix4x4.h"
    "lib/assimp/matrix4x4.inl"
    "lib/assimp/MemoryIOWrapper.h"
    "lib/assimp/mesh.h"
    "lib/assimp/metadata.h"
    "lib/assimp/NullLogger.hpp"
    "lib/assimp/ParsingUtils.h"
    "lib/assimp/pbrmaterial.h"
    "lib/assimp/port/AndroidJNI/AndroidJNIIOSystem.h"
    "lib/assimp/port/AndroidJNI/BundledAssetIOSystem.h"
    "lib/assimp/postprocess.h"
    "lib/assimp/Profiler.h"
    "lib/assimp/ProgressHandler.hpp"
    "lib/assimp/qnan.h"
    "lib/assimp/quaternion.h"
    "lib/assimp/quaternion.inl"
    "lib/assimp/RemoveComments.h"
    "lib/assimp/scene.h"
    "lib/assimp/SceneCombiner.h"
    "lib/assimp/SGSpatialSort.h"
    "lib/assimp/SkeletonMeshBuilder.h"
    "lib/assimp/SmallVector.h"
    "lib/assimp/SmoothingGroups.h"
    "lib/assimp/SmoothingGroups.inl"
    "lib/assimp/SpatialSort.h"
    "lib/assimp/StandardShapes.h"
    "lib/assimp/StreamReader.h"
    "lib/assimp/StreamWriter.h"
    "lib/assimp/StringComparison.h"
    "lib/assimp/StringUtils.h"
    "lib/assimp/Subdivision.h"
    "lib/assimp/texture.h"
    "lib/assimp/TinyFormatter.h"
    "lib/assimp/types.h"
    "lib/assimp/vector2.h"
    "lib/assimp/vector2.inl"
    "lib/assimp/vector3.h"
    "lib/assimp/vector3.inl"
    "lib/assimp/version.h"
    "lib/assimp/Vertex.h"
    "lib/assimp/XmlParser.h"
    "lib/assimp/XMLTools.h"
    "lib/assimp/ZipArchiveIOSystem.h"
)
source_group("lib\\assimp" FILES ${lib__assimp})

set(lib__gli
    "lib/gli/clear.hpp"
    "lib/gli/comparison.hpp"
    "lib/gli/convert.hpp"
    "lib/gli/copy.hpp"
    "lib/gli/core/bc.hpp"
    "lib/gli/core/bc.inl"
    "lib/gli/core/clear.hpp"
    "lib/gli/core/clear.inl"
    "lib/gli/core/comparison.inl"
    "lib/gli/core/convert.inl"
    "lib/gli/core/convert_func.hpp"
    "lib/gli/core/coord.hpp"
    "lib/gli/core/copy.inl"
    "lib/gli/core/dummy.cpp"
    "lib/gli/core/duplicate.inl"
    "lib/gli/core/dx.inl"
    "lib/gli/core/file.hpp"
    "lib/gli/core/file.inl"
    "lib/gli/core/filter.hpp"
    "lib/gli/core/filter.inl"
    "lib/gli/core/filter_compute.hpp"
    "lib/gli/core/flip.hpp"
    "lib/gli/core/flip.inl"
    "lib/gli/core/format.inl"
    "lib/gli/core/generate_mipmaps.inl"
    "lib/gli/core/gl.inl"
    "lib/gli/core/image.inl"
    "lib/gli/core/levels.inl"
    "lib/gli/core/load.inl"
    "lib/gli/core/load_dds.inl"
    "lib/gli/core/load_kmg.inl"
    "lib/gli/core/load_ktx.inl"
    "lib/gli/core/make_texture.inl"
    "lib/gli/core/mipmaps_compute.hpp"
    "lib/gli/core/reduce.inl"
    "lib/gli/core/s3tc.hpp"
    "lib/gli/core/s3tc.inl"
    "lib/gli/core/sampler.inl"
    "lib/gli/core/sampler1d.inl"
    "lib/gli/core/sampler1d_array.inl"
    "lib/gli/core/sampler2d.inl"
    "lib/gli/core/sampler2d_array.inl"
    "lib/gli/core/sampler3d.inl"
    "lib/gli/core/sampler_cube.inl"
    "lib/gli/core/sampler_cube_array.inl"
    "lib/gli/core/save.inl"
    "lib/gli/core/save_dds.inl"
    "lib/gli/core/save_kmg.inl"
    "lib/gli/core/save_ktx.inl"
    "lib/gli/core/storage_linear.hpp"
    "lib/gli/core/storage_linear.inl"
    "lib/gli/core/texture.inl"
    "lib/gli/core/texture1d.inl"
    "lib/gli/core/texture1d_array.inl"
    "lib/gli/core/texture2d.inl"
    "lib/gli/core/texture2d_array.inl"
    "lib/gli/core/texture3d.inl"
    "lib/gli/core/texture_cube.inl"
    "lib/gli/core/texture_cube_array.inl"
    "lib/gli/core/transform.inl"
    "lib/gli/core/view.inl"
    "lib/gli/duplicate.hpp"
    "lib/gli/dx.hpp"
    "lib/gli/format.hpp"
    "lib/gli/generate_mipmaps.hpp"
    "lib/gli/gl.hpp"
    "lib/gli/gli.hpp"
    "lib/gli/image.hpp"
    "lib/gli/levels.hpp"
    "lib/gli/load.hpp"
    "lib/gli/load_dds.hpp"
    "lib/gli/load_kmg.hpp"
    "lib/gli/load_ktx.hpp"
    "lib/gli/make_texture.hpp"
    "lib/gli/reduce.hpp"
    "lib/gli/sampler.hpp"
    "lib/gli/sampler1d.hpp"
    "lib/gli/sampler1d_array.hpp"
    "lib/gli/sampler2d.hpp"
    "lib/gli/sampler2d_array.hpp"
    "lib/gli/sampler3d.hpp"
    "lib/gli/sampler_cube.hpp"
    "lib/gli/sampler_cube_array.hpp"
    "lib/gli/save.hpp"
    "lib/gli/save_dds.hpp"
    "lib/gli/save_kmg.hpp"
    "lib/gli/save_ktx.hpp"
    "lib/gli/target.hpp"
    "lib/gli/texture.hpp"
    "lib/gli/texture1d.hpp"
    "lib/gli/texture1d_array.hpp"
    "lib/gli/texture2d.hpp"
    "lib/gli/texture2d_array.hpp"
    "lib/gli/texture3d.hpp"
    "lib/gli/texture_cube.hpp"
    "lib/gli/texture_cube_array.hpp"
    "lib/gli/transform.hpp"
    "lib/gli/type.hpp"
    "lib/gli/view.hpp"
)
source_group("lib\\gli" FILES ${lib__gli})

set(lib__lodepng
    "lib/lodepng/include/lodepng/lodepng.cpp"
    "lib/lodepng/include/lodepng/lodepng.h"
    "lib/lodepng/include/lodepng/lodepng_util.cpp"
    "lib/lodepng/include/lodepng/lodepng_util.h"
    "lib/lodepng/lodepng.cpp"
    "lib/lodepng/lodepng.h"
    "lib/lodepng/lodepng_util.cpp"
    "lib/lodepng/lodepng_util.h"
)
source_group("lib\\lodepng" FILES ${lib__lodepng})

set(lib__zipper
    "lib/zipper/CDirEntry.h"
    "lib/zipper/defs.h"
    "lib/zipper/tools.h"
    "lib/zipper/unzipper.h"
    "lib/zipper/zipper.h"
)
source_group("lib\\zipper" FILES ${lib__zipper})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__MagickaVox}
    ${Header_Files__Sound}
    ${Header_Files__SupremeCommander}
    ${Source_Files}
    ${Source_Files__MagickaVox}
    ${Source_Files__Sound}
    ${Source_Files__SupremeCommander}
    ${lib}
    ${lib__assimp}
    ${lib__gli}
    ${lib__lodepng}
    ${lib__zipper}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE AezeselFileIOLib)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE        "TRUE"
        INTERPROCEDURAL_OPTIMIZATION_RELEASEWITHDBG "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE        "TRUE"
        INTERPROCEDURAL_OPTIMIZATION_RELEASEWITHDBG "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib;"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/minizip;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../IyathuumCoreLib/lib"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "$<$<CONFIG:ReleaseWithDbg>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "$<$<CONFIG:ReleaseWithDbg>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /Oi;
                /Gy
            >
            /permissive-;
            /std:c++latest;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /OPT:REF;
                /OPT:ICF
            >
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            $<$<CONFIG:ReleaseWithDbg>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    IyathuumCoreLib
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "$(ProjectDir)lib/zipper/Zipper-staticd;"
            "$(ProjectDir)lib/assimp/assimp-vc142-mtd;"
            "$(ProjectDir)lib\libnyquist\libnyquist_d;"
            "$(ProjectDir)lib\libnyquist\libopus_d;"
            "$(ProjectDir)lib\libnyquist\libwavpack_d"
        ">"
        "$<$<CONFIG:Release>:"
            "$(ProjectDir)lib/zipper/Zipper-static;"
            "$(ProjectDir)lib/assimp/assimp-vc142-mt;"
            "$(ProjectDir)lib\libnyquist\libnyquist;"
            "$(ProjectDir)lib\libnyquist\libopus;"
            "$(ProjectDir)lib\libnyquist\libwavpack"
        ">"
        "$<$<CONFIG:ReleaseWithDbg>:"
            "$(ProjectDir)lib/zipper/Zipper-static;"
            "$(ProjectDir)lib/assimp/assimp-vc142-mt;"
            "$(ProjectDir)lib\libnyquist\libnyquist;"
            "$(ProjectDir)lib\libnyquist\libopus;"
            "$(ProjectDir)lib\libnyquist\libwavpack"
        ">"
        "$(SolutionDir)x64/$(ConfigurationName)/IyathuumCoreLib;"
        "$(ProjectDir)lib/zipper/zlibstatic"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

