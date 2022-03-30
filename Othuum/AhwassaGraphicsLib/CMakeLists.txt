set(PROJECT_NAME AhwassaGraphicsLib)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "Util.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__BufferObjects
    "BufferObjects/FBO.h"
    "BufferObjects/IBO.h"
    "BufferObjects/IMesh.h"
    "BufferObjects/IVBO.h"
    "BufferObjects/Mesh.h"
    "BufferObjects/VAO.h"
    "BufferObjects/VBO.h"
)
source_group("Header Files\\BufferObjects" FILES ${Header_Files__BufferObjects})

set(Header_Files__Core
    "Core/AttributeDescription.h"
    "Core/Camera.h"
    "Core/Renderer.h"
    "Core/ShaderProgram.h"
    "Core/Window.h"
)
source_group("Header Files\\Core" FILES ${Header_Files__Core})

set(Header_Files__Drawables
    "Drawables/Background.h"
    "Drawables/Drawable.h"
    "Drawables/FPS.h"
)
source_group("Header Files\\Drawables" FILES ${Header_Files__Drawables})

set(Header_Files__Geometry
    "Geometry/BasicShapeGenerator.h"
    "Geometry/HeightFieldMeshGenerator.h"
)
source_group("Header Files\\Geometry" FILES ${Header_Files__Geometry})

set(Header_Files__Input
    "Input/ArcBallCamera.h"
    "Input/FileDropper.h"
    "Input/FreeCamera.h"
    "Input/IMGUIRenderer.h"
    "Input/Input.h"
    "Input/UIElement.h"
)
source_group("Header Files\\Input" FILES ${Header_Files__Input})

set(Header_Files__PostProcessing
    "PostProcessing/AdditiveComposer.h"
    "PostProcessing/Bloom.h"
    "PostProcessing/CubeReflection.h"
    "PostProcessing/DeferredComposer.h"
    "PostProcessing/PostProcessingEffect.h"
)
source_group("Header Files\\PostProcessing" FILES ${Header_Files__PostProcessing})

set(Header_Files__Renderer
    "Renderer/BasicBoxRenderer.h"
    "Renderer/BasicMeshRenderer.h"
    "Renderer/BasicRectangleRenderer.h"
    "Renderer/BasicTextRenderer.h"
    "Renderer/BasicTexture2DRenderer.h"
    "Renderer/BoxRenderer.h"
    "Renderer/Decal.h"
    "Renderer/DecalRenderer.h"
    "Renderer/DiffuseMeshRenderer.h"
    "Renderer/Dot.h"
    "Renderer/IBox.h"
    "Renderer/Line.h"
    "Renderer/Rectangle.h"
    "Renderer/RectangleRenderer.h"
    "Renderer/RendererTemplate.h"
    "Renderer/Sphere.h"
    "Renderer/SphereRenderer.h"
)
source_group("Header Files\\Renderer" FILES ${Header_Files__Renderer})

set(Header_Files__Sound
    "sound/sound.h"
    "sound/SoundEngine.h"
    "sound/SoundHandler.h"
)
source_group("Header Files\\Sound" FILES ${Header_Files__Sound})

set(Header_Files__Uniforms
    "Uniforms/CubeTexture.h"
    "Uniforms/InstancedVecMat4.h"
    "Uniforms/InstancedVecVec3.h"
    "Uniforms/Rendertarget.h"
    "Uniforms/SSBOint.h"
    "Uniforms/SSBOmat4.h"
    "Uniforms/SSBOvec3.h"
    "Uniforms/SSBOvec4.h"
    "Uniforms/Texture.h"
    "Uniforms/Uniform.h"
    "Uniforms/UniformFloat.h"
    "Uniforms/UniformMat4.h"
    "Uniforms/UniformVec2.h"
    "Uniforms/UniformVec3.h"
    "Uniforms/UniformVec4.h"
    "Uniforms/UniformVecMat4.h"
    "Uniforms/UniformVecTexture.h"
    "Uniforms/UniformVecVec2.h"
    "Uniforms/UniformVecVec3.h"
)
source_group("Header Files\\Uniforms" FILES ${Header_Files__Uniforms})

set(Header_Files__VR
    "VR/VR.h"
    "VR/VRController.h"
)
source_group("Header Files\\VR" FILES ${Header_Files__VR})

set(Header_Files__Vertex
    "Vertex/IVertex.h"
    "Vertex/PositionColorNormalVertex.h"
    "Vertex/PositionColorVertex.h"
    "Vertex/PositionNormalTextureVertex.h"
    "Vertex/PositionNormalVertex.h"
    "Vertex/PositionTextureVertex.h"
    "Vertex/PositionTextureVertexIndex.h"
    "Vertex/PositionVertex.h"
    "Vertex/SupComVertex.h"
)
source_group("Header Files\\Vertex" FILES ${Header_Files__Vertex})

set(Header_Files__Widgets
    "Widgets/Button.h"
    "Widgets/Checkbox.h"
    "Widgets/Label.h"
    "Widgets/LineEdit.h"
    "Widgets/ListLayout.h"
    "Widgets/Slider.h"
)
source_group("Header Files\\Widgets" FILES ${Header_Files__Widgets})

set(Source_Files
    "Util.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__BufferObjects
    "BufferObjects/FBO.cpp"
    "BufferObjects/IBO.cpp"
    "BufferObjects/IVBO.cpp"
    "BufferObjects/Mesh.cpp"
    "BufferObjects/VAO.cpp"
    "BufferObjects/VBO.cpp"
)
source_group("Source Files\\BufferObjects" FILES ${Source_Files__BufferObjects})

set(Source_Files__Core
    "Core/AttributeDescription.cpp"
    "Core/Camera.cpp"
    "Core/Renderer.cpp"
    "Core/ShaderProgram.cpp"
    "Core/Window.cpp"
)
source_group("Source Files\\Core" FILES ${Source_Files__Core})

set(Source_Files__Drawables
    "Drawables/Background.cpp"
    "Drawables/Drawable.cpp"
    "Drawables/FPS.cpp"
)
source_group("Source Files\\Drawables" FILES ${Source_Files__Drawables})

set(Source_Files__Geometry
    "Geometry/BasicShapeGenerator.cpp"
    "Geometry/HeightFieldMeshGenerator.cpp"
)
source_group("Source Files\\Geometry" FILES ${Source_Files__Geometry})

set(Source_Files__Input
    "Input/ArcBallCamera.cpp"
    "Input/FileDropper.cpp"
    "Input/FreeCamera.cpp"
    "Input/IMGUIRenderer.cpp"
    "Input/Input.cpp"
    "Input/UIElement.cpp"
)
source_group("Source Files\\Input" FILES ${Source_Files__Input})

set(Source_Files__Post_Processing
    "PostProcessing/AdditiveComposer.cpp"
    "PostProcessing/Bloom.cpp"
    "PostProcessing/CubeReflection.cpp"
    "PostProcessing/DeferredComposer.cpp"
    "PostProcessing/PostProcessingEffect.cpp"
)
source_group("Source Files\\Post Processing" FILES ${Source_Files__Post_Processing})

set(Source_Files__Renderer
    "Renderer/BasicBoxRenderer.cpp"
    "Renderer/BasicMeshRenderer.cpp"
    "Renderer/BasicRectangleRenderer.cpp"
    "Renderer/BasicTextRenderer.cpp"
    "Renderer/BasicTexture2DRenderer.cpp"
    "Renderer/Box.cpp"
    "Renderer/BoxRenderer.cpp"
    "Renderer/Decal.cpp"
    "Renderer/DecalRenderer.cpp"
    "Renderer/DiffuseMeshRenderer.cpp"
    "Renderer/Dot.cpp"
    "Renderer/Line.cpp"
    "Renderer/Rectangle.cpp"
    "Renderer/RectangleRenderer.cpp"
    "Renderer/RendererTemplate.cpp"
    "Renderer/Sphere.cpp"
    "Renderer/SphereRenderer.cpp"
    "Renderer/Text.cpp"
)
source_group("Source Files\\Renderer" FILES ${Source_Files__Renderer})

set(Source_Files__Sound
    "sound/sound.cpp"
    "sound/SoundEngine.cpp"
    "sound/SoundHandler.cpp"
)
source_group("Source Files\\Sound" FILES ${Source_Files__Sound})

set(Source_Files__Uniforms
    "Uniforms/CubeTexture.cpp"
    "Uniforms/InstancedVecMat4.cpp"
    "Uniforms/InstancedVecVec3.cpp"
    "Uniforms/Rendertarget.cpp"
    "Uniforms/SSBOint.cpp"
    "Uniforms/SSBOmat4.cpp"
    "Uniforms/SSBOvec3.cpp"
    "Uniforms/SSBOvec4.cpp"
    "Uniforms/Texture.cpp"
    "Uniforms/Uniform.cpp"
    "Uniforms/UniformFloat.cpp"
    "Uniforms/UniformMat4.cpp"
    "Uniforms/UniformVec2.cpp"
    "Uniforms/UniformVec3.cpp"
    "Uniforms/UniformVec4.cpp"
    "Uniforms/UniformVecMat4.cpp"
    "Uniforms/UniformVecTexture.cpp"
    "Uniforms/UniformVecVec2.cpp"
    "Uniforms/UniformVecVec3.cpp"
)
source_group("Source Files\\Uniforms" FILES ${Source_Files__Uniforms})

set(Source_Files__VR
    "VR/VR.cpp"
    "VR/VRController.cpp"
)
source_group("Source Files\\VR" FILES ${Source_Files__VR})

set(Source_Files__Vertex
    "Vertex/IVertex.cpp"
    "Vertex/PositionColorNormalVertex.cpp"
    "Vertex/PositionColorVertex.cpp"
    "Vertex/PositionNormalTextureVertex.cpp"
    "Vertex/PositionNormalVertex.cpp"
    "Vertex/PositionTextureVertex.cpp"
    "Vertex/PositionTextureVertexIndex.cpp"
    "Vertex/PositionVertex.cpp"
    "Vertex/SupComVertex.cpp"
)
source_group("Source Files\\Vertex" FILES ${Source_Files__Vertex})

set(Source_Files__Widgets
    "Widgets/Button.cpp"
    "Widgets/Checkbox.cpp"
    "Widgets/Label.cpp"
    "Widgets/LineEdit.cpp"
    "Widgets/ListLayout.cpp"
    "Widgets/Slider.cpp"
)
source_group("Source Files\\Widgets" FILES ${Source_Files__Widgets})

set(lib__GLWF
    "lib/GLWF/include/GLFW/glfw3.h"
    "lib/GLWF/include/GLFW/glfw3native.h"
)
source_group("lib\\GLWF" FILES ${lib__GLWF})

set(lib__dear_imgui
    "lib/DearIMGUI/imconfig.h"
    "lib/DearIMGUI/imgui.cpp"
    "lib/DearIMGUI/imgui.h"
    "lib/DearIMGUI/imgui_demo.cpp"
    "lib/DearIMGUI/imgui_draw.cpp"
    "lib/DearIMGUI/imgui_impl_glfw.cpp"
    "lib/DearIMGUI/imgui_impl_glfw.h"
    "lib/DearIMGUI/imgui_impl_opengl3.cpp"
    "lib/DearIMGUI/imgui_impl_opengl3.h"
    "lib/DearIMGUI/imgui_impl_opengl3_loader.h"
    "lib/DearIMGUI/imgui_internal.h"
    "lib/DearIMGUI/imgui_tables.cpp"
    "lib/DearIMGUI/imgui_widgets.cpp"
    "lib/DearIMGUI/imstb_rectpack.h"
    "lib/DearIMGUI/imstb_textedit.h"
    "lib/DearIMGUI/imstb_truetype.h"
)
source_group("lib\\dear imgui" FILES ${lib__dear_imgui})

set(lib__dear_imgui_filedialog
    "lib/DearIMGUI/imgui_stdlib.cpp"
    "lib/DearIMGUI/imgui_stdlib.h"
    "lib/IMGUIFileDialog/dirent/dirent.h"
    "lib/IMGUIFileDialog/ImGuiFileDialog.cpp"
    "lib/IMGUIFileDialog/ImGuiFileDialog.h"
    "lib/IMGUIFileDialog/ImGuiFileDialogConfig.h"
    "lib/IMGUIFileDialog/stb/stb_image.h"
    "lib/IMGUIFileDialog/stb/stb_image_resize.h"
)
source_group("lib\\dear imgui filedialog" FILES ${lib__dear_imgui_filedialog})

set(lib__freetype
    "lib/freetype/include/freetype/config/ftconfig.h"
    "lib/freetype/include/freetype/config/ftheader.h"
    "lib/freetype/include/freetype/config/ftmodule.h"
    "lib/freetype/include/freetype/config/ftoption.h"
    "lib/freetype/include/freetype/config/ftstdlib.h"
    "lib/freetype/include/freetype/freetype.h"
    "lib/freetype/include/freetype/ftadvanc.h"
    "lib/freetype/include/freetype/ftbbox.h"
    "lib/freetype/include/freetype/ftbdf.h"
    "lib/freetype/include/freetype/ftbitmap.h"
    "lib/freetype/include/freetype/ftbzip2.h"
    "lib/freetype/include/freetype/ftcache.h"
    "lib/freetype/include/freetype/ftchapters.h"
    "lib/freetype/include/freetype/ftcid.h"
    "lib/freetype/include/freetype/ftcolor.h"
    "lib/freetype/include/freetype/ftdriver.h"
    "lib/freetype/include/freetype/fterrdef.h"
    "lib/freetype/include/freetype/fterrors.h"
    "lib/freetype/include/freetype/ftfntfmt.h"
    "lib/freetype/include/freetype/ftgasp.h"
    "lib/freetype/include/freetype/ftglyph.h"
    "lib/freetype/include/freetype/ftgxval.h"
    "lib/freetype/include/freetype/ftgzip.h"
    "lib/freetype/include/freetype/ftimage.h"
    "lib/freetype/include/freetype/ftincrem.h"
    "lib/freetype/include/freetype/ftlcdfil.h"
    "lib/freetype/include/freetype/ftlist.h"
    "lib/freetype/include/freetype/ftlzw.h"
    "lib/freetype/include/freetype/ftmac.h"
    "lib/freetype/include/freetype/ftmm.h"
    "lib/freetype/include/freetype/ftmodapi.h"
    "lib/freetype/include/freetype/ftmoderr.h"
    "lib/freetype/include/freetype/ftotval.h"
    "lib/freetype/include/freetype/ftoutln.h"
    "lib/freetype/include/freetype/ftparams.h"
    "lib/freetype/include/freetype/ftpfr.h"
    "lib/freetype/include/freetype/ftrender.h"
    "lib/freetype/include/freetype/ftsizes.h"
    "lib/freetype/include/freetype/ftsnames.h"
    "lib/freetype/include/freetype/ftstroke.h"
    "lib/freetype/include/freetype/ftsynth.h"
    "lib/freetype/include/freetype/ftsystem.h"
    "lib/freetype/include/freetype/fttrigon.h"
    "lib/freetype/include/freetype/fttypes.h"
    "lib/freetype/include/freetype/ftwinfnt.h"
    "lib/freetype/include/freetype/internal/autohint.h"
    "lib/freetype/include/freetype/internal/cffotypes.h"
    "lib/freetype/include/freetype/internal/cfftypes.h"
    "lib/freetype/include/freetype/internal/ftcalc.h"
    "lib/freetype/include/freetype/internal/ftdebug.h"
    "lib/freetype/include/freetype/internal/ftdrv.h"
    "lib/freetype/include/freetype/internal/ftgloadr.h"
    "lib/freetype/include/freetype/internal/fthash.h"
    "lib/freetype/include/freetype/internal/ftmemory.h"
    "lib/freetype/include/freetype/internal/ftobjs.h"
    "lib/freetype/include/freetype/internal/ftpsprop.h"
    "lib/freetype/include/freetype/internal/ftrfork.h"
    "lib/freetype/include/freetype/internal/ftserv.h"
    "lib/freetype/include/freetype/internal/ftstream.h"
    "lib/freetype/include/freetype/internal/fttrace.h"
    "lib/freetype/include/freetype/internal/ftvalid.h"
    "lib/freetype/include/freetype/internal/internal.h"
    "lib/freetype/include/freetype/internal/psaux.h"
    "lib/freetype/include/freetype/internal/pshints.h"
    "lib/freetype/include/freetype/internal/services/svbdf.h"
    "lib/freetype/include/freetype/internal/services/svcfftl.h"
    "lib/freetype/include/freetype/internal/services/svcid.h"
    "lib/freetype/include/freetype/internal/services/svfntfmt.h"
    "lib/freetype/include/freetype/internal/services/svgldict.h"
    "lib/freetype/include/freetype/internal/services/svgxval.h"
    "lib/freetype/include/freetype/internal/services/svkern.h"
    "lib/freetype/include/freetype/internal/services/svmetric.h"
    "lib/freetype/include/freetype/internal/services/svmm.h"
    "lib/freetype/include/freetype/internal/services/svotval.h"
    "lib/freetype/include/freetype/internal/services/svpfr.h"
    "lib/freetype/include/freetype/internal/services/svpostnm.h"
    "lib/freetype/include/freetype/internal/services/svprop.h"
    "lib/freetype/include/freetype/internal/services/svpscmap.h"
    "lib/freetype/include/freetype/internal/services/svpsinfo.h"
    "lib/freetype/include/freetype/internal/services/svsfnt.h"
    "lib/freetype/include/freetype/internal/services/svttcmap.h"
    "lib/freetype/include/freetype/internal/services/svtteng.h"
    "lib/freetype/include/freetype/internal/services/svttglyf.h"
    "lib/freetype/include/freetype/internal/services/svwinfnt.h"
    "lib/freetype/include/freetype/internal/sfnt.h"
    "lib/freetype/include/freetype/internal/t1types.h"
    "lib/freetype/include/freetype/internal/tttypes.h"
    "lib/freetype/include/freetype/t1tables.h"
    "lib/freetype/include/freetype/ttnameid.h"
    "lib/freetype/include/freetype/tttables.h"
    "lib/freetype/include/freetype/tttags.h"
    "lib/freetype/include/ft2build.h"
)
source_group("lib\\freetype" FILES ${lib__freetype})

set(lib__glad
    "lib/glad/include/glad/glad.h"
    "lib/glad/include/KHR/khrplatform.h"
    "lib/glad/src/glad.c"
)
source_group("lib\\glad" FILES ${lib__glad})

set(lib__libnyquist
    "lib/libnyquist/Common.h"
    "lib/libnyquist/Decoders.h"
    "lib/libnyquist/Encoders.h"
)
source_group("lib\\libnyquist" FILES ${lib__libnyquist})

set(lib__openvr
    "lib/openvr/openvr.h"
    "lib/openvr/openvr_driver.h"
)
source_group("lib\\openvr" FILES ${lib__openvr})

set(lib__portaudio
    "lib/portaudio/pa_asio.h"
    "lib/portaudio/pa_jack.h"
    "lib/portaudio/pa_linux_alsa.h"
    "lib/portaudio/pa_mac_core.h"
    "lib/portaudio/pa_win_ds.h"
    "lib/portaudio/pa_win_wasapi.h"
    "lib/portaudio/pa_win_waveformat.h"
    "lib/portaudio/pa_win_wdmks.h"
    "lib/portaudio/pa_win_wmme.h"
    "lib/portaudio/portaudio.h"
)
source_group("lib\\portaudio" FILES ${lib__portaudio})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__BufferObjects}
    ${Header_Files__Core}
    ${Header_Files__Drawables}
    ${Header_Files__Geometry}
    ${Header_Files__Input}
    ${Header_Files__PostProcessing}
    ${Header_Files__Renderer}
    ${Header_Files__Sound}
    ${Header_Files__Uniforms}
    ${Header_Files__VR}
    ${Header_Files__Vertex}
    ${Header_Files__Widgets}
    ${Source_Files}
    ${Source_Files__BufferObjects}
    ${Source_Files__Core}
    ${Source_Files__Drawables}
    ${Source_Files__Geometry}
    ${Source_Files__Input}
    ${Source_Files__Post_Processing}
    ${Source_Files__Renderer}
    ${Source_Files__Sound}
    ${Source_Files__Uniforms}
    ${Source_Files__VR}
    ${Source_Files__Vertex}
    ${Source_Files__Widgets}
    ${lib__GLWF}
    ${lib__dear_imgui}
    ${lib__dear_imgui_filedialog}
    ${lib__freetype}
    ${lib__glad}
    ${lib__libnyquist}
    ${lib__openvr}
    ${lib__portaudio}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE AhwassaGraphicsLib)

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
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/GLWF/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/freetype/include"
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
        "_CRT_SECURE_NO_WARNINGS;"
        "WIN32;"
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
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$(ProjectDir)lib\portaudio\portaudio_static_x64;"
        "$(ProjectDir)lib/GLWF/lib/glfw3;"
        "$(ProjectDir)lib/freetype/lib/freetype;"
        "$(ProjectDir)lib/openvr/openvr_api"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

