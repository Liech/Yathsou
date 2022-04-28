cmake_minimum_required(VERSION 3.23)
project(AhwassaGraphicsLib)
include(FetchContent)

find_package(glm)
find_package(glfw3 REQUIRED)
find_package(portaudio REQUIRED)
find_package(Freetype REQUIRED)
find_package(imgui REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(OpenVR REQUIRED)

############################################################################
############################################################################
############################################################################

set(Header_Files
    "Source/AhwassaGraphicsLib/Util.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__BufferObjects
    "Source/AhwassaGraphicsLib/BufferObjects/FBO.h"
    "Source/AhwassaGraphicsLib/BufferObjects/IBO.h"
    "Source/AhwassaGraphicsLib/BufferObjects/IMesh.h"
    "Source/AhwassaGraphicsLib/BufferObjects/IVBO.h"
    "Source/AhwassaGraphicsLib/BufferObjects/Mesh.h"
    "Source/AhwassaGraphicsLib/BufferObjects/VAO.h"
    "Source/AhwassaGraphicsLib/BufferObjects/VBO.h"
)
source_group("Header Files\\BufferObjects" FILES ${Header_Files__BufferObjects})

set(Header_Files__Core
    "Source/AhwassaGraphicsLib/Core/AttributeDescription.h"
    "Source/AhwassaGraphicsLib/Core/Camera.h"
    "Source/AhwassaGraphicsLib/Core/Renderer.h"
    "Source/AhwassaGraphicsLib/Core/ShaderProgram.h"
    "Source/AhwassaGraphicsLib/Core/Window.h"
)
source_group("Header Files\\Core" FILES ${Header_Files__Core})

set(Header_Files__Drawables
    "Source/AhwassaGraphicsLib/Drawables/Background.h"
    "Source/AhwassaGraphicsLib/Drawables/Drawable.h"
    "Source/AhwassaGraphicsLib/Drawables/FPS.h"
)
source_group("Header Files\\Drawables" FILES ${Header_Files__Drawables})

set(Header_Files__Geometry
    "Source/AhwassaGraphicsLib/Geometry/BasicShapeGenerator.h"
    "Source/AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.h"
)
source_group("Header Files\\Geometry" FILES ${Header_Files__Geometry})

set(Header_Files__Input
    "Source/AhwassaGraphicsLib/Input/ArcBallCamera.h"
    "Source/AhwassaGraphicsLib/Input/FileDropper.h"
    "Source/AhwassaGraphicsLib/Input/FreeCamera.h"
    "Source/AhwassaGraphicsLib/Input/IMGUIRenderer.h"
    "Source/AhwassaGraphicsLib/Input/Input.h"
    "Source/AhwassaGraphicsLib/Input/UIElement.h"
)
source_group("Header Files\\Input" FILES ${Header_Files__Input})

set(Header_Files__PostProcessing
    "Source/AhwassaGraphicsLib/PostProcessing/AdditiveComposer.h"
    "Source/AhwassaGraphicsLib/PostProcessing/Bloom.h"
    "Source/AhwassaGraphicsLib/PostProcessing/CubeReflection.h"
    "Source/AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
    "Source/AhwassaGraphicsLib/PostProcessing/PostProcessingEffect.h"
)
source_group("Header Files\\PostProcessing" FILES ${Header_Files__PostProcessing})

set(Header_Files__Renderer
    "Source/AhwassaGraphicsLib/Renderer/BasicBoxRenderer.h"
    "Source/AhwassaGraphicsLib/Renderer/BasicMeshRenderer.h"
    "Source/AhwassaGraphicsLib/Renderer/BasicRectangleRenderer.h"
    "Source/AhwassaGraphicsLib/Renderer/BasicTextRenderer.h"
    "Source/AhwassaGraphicsLib/Renderer/BasicTexture2DRenderer.h"
    "Source/AhwassaGraphicsLib/Renderer/BoxRenderer.h"
    "Source/AhwassaGraphicsLib/Renderer/DecalRenderer.h"
    "Source/AhwassaGraphicsLib/Renderer/DiffuseMeshRenderer.h"
    "Source/AhwassaGraphicsLib/Renderer/RectangleRenderer.h"
    "Source/AhwassaGraphicsLib/Renderer/RendererTemplate.h"
    "Source/AhwassaGraphicsLib/Renderer/SphereRenderer.h"
    "Source/AhwassaGraphicsLib/Renderer/Model3DRenderer.h"
)
source_group("Header Files\\Renderer" FILES ${Header_Files__Renderer})

set(Header_Files__RendererPrimitives
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Dot.h"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/IBox.h"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Line.h"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Rectangle.h"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Sphere.h"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Decal.h"
)
source_group("Header Files\\Renderer\\Primitives" FILES ${Header_Files__RendererPrimitives})

set(Header_Files__Sound
    "Source/AhwassaGraphicsLib/sound/sound.h"
    "Source/AhwassaGraphicsLib/sound/SoundEngine.h"
    "Source/AhwassaGraphicsLib/sound/SoundHandler.h"
)
source_group("Header Files\\Sound" FILES ${Header_Files__Sound})

set(Header_Files__Uniforms
    "Source/AhwassaGraphicsLib/Uniforms/CubeTexture.h"
    "Source/AhwassaGraphicsLib/Uniforms/InstancedVecMat4.h"
    "Source/AhwassaGraphicsLib/Uniforms/InstancedVecVec3.h"
    "Source/AhwassaGraphicsLib/Uniforms/Rendertarget.h"
    "Source/AhwassaGraphicsLib/Uniforms/SSBOint.h"
    "Source/AhwassaGraphicsLib/Uniforms/SSBOmat4.h"
    "Source/AhwassaGraphicsLib/Uniforms/SSBOvec3.h"
    "Source/AhwassaGraphicsLib/Uniforms/SSBOvec4.h"
    "Source/AhwassaGraphicsLib/Uniforms/Texture.h"
    "Source/AhwassaGraphicsLib/Uniforms/Uniform.h"
    "Source/AhwassaGraphicsLib/Uniforms/UniformFloat.h"
    "Source/AhwassaGraphicsLib/Uniforms/UniformMat4.h"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVec2.h"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVec3.h"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVec4.h"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVecMat4.h"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVecTexture.h"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVecVec2.h"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVecVec3.h"
)
source_group("Header Files\\Uniforms" FILES ${Header_Files__Uniforms})

set(Header_Files__VR
    "Source/AhwassaGraphicsLib/VR/VR.h"
    "Source/AhwassaGraphicsLib/VR/VRController.h"
)
source_group("Header Files\\VR" FILES ${Header_Files__VR})

set(Header_Files__Vertex
    "Source/AhwassaGraphicsLib/Vertex/IVertex.h"
    "Source/AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"
    "Source/AhwassaGraphicsLib/Vertex/PositionColorVertex.h"
    "Source/AhwassaGraphicsLib/Vertex/PositionNormalTextureVertex.h"
    "Source/AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"
    "Source/AhwassaGraphicsLib/Vertex/PositionTextureVertex.h"
    "Source/AhwassaGraphicsLib/Vertex/PositionTextureVertexIndex.h"
    "Source/AhwassaGraphicsLib/Vertex/PositionVertex.h"
    "Source/AhwassaGraphicsLib/Vertex/SupComVertex.h"
)
source_group("Header Files\\Vertex" FILES ${Header_Files__Vertex})

set(Header_Files__Widgets
    "Source/AhwassaGraphicsLib/Widgets/Button.h"
    "Source/AhwassaGraphicsLib/Widgets/Checkbox.h"
    "Source/AhwassaGraphicsLib/Widgets/Label.h"
    "Source/AhwassaGraphicsLib/Widgets/LineEdit.h"
    "Source/AhwassaGraphicsLib/Widgets/ListLayout.h"
    "Source/AhwassaGraphicsLib/Widgets/Slider.h"
)
source_group("Header Files\\Widgets" FILES ${Header_Files__Widgets})

set(Source_Files
    "Source/AhwassaGraphicsLib/Util.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__BufferObjects
    "Source/AhwassaGraphicsLib/BufferObjects/FBO.cpp"
    "Source/AhwassaGraphicsLib/BufferObjects/IBO.cpp"
    "Source/AhwassaGraphicsLib/BufferObjects/IVBO.cpp"
    "Source/AhwassaGraphicsLib/BufferObjects/Mesh.cpp"
    "Source/AhwassaGraphicsLib/BufferObjects/VAO.cpp"
    "Source/AhwassaGraphicsLib/BufferObjects/VBO.cpp"
)
source_group("Source Files\\BufferObjects" FILES ${Source_Files__BufferObjects})

set(Source_Files__Core
    "Source/AhwassaGraphicsLib/Core/AttributeDescription.cpp"
    "Source/AhwassaGraphicsLib/Core/Camera.cpp"
    "Source/AhwassaGraphicsLib/Core/Renderer.cpp"
    "Source/AhwassaGraphicsLib/Core/ShaderProgram.cpp"
    "Source/AhwassaGraphicsLib/Core/Window.cpp"
)
source_group("Source Files\\Core" FILES ${Source_Files__Core})

set(Source_Files__Drawables
    "Source/AhwassaGraphicsLib/Drawables/Background.cpp"
    "Source/AhwassaGraphicsLib/Drawables/Drawable.cpp"
    "Source/AhwassaGraphicsLib/Drawables/FPS.cpp"
)
source_group("Source Files\\Drawables" FILES ${Source_Files__Drawables})

set(Source_Files__Geometry
    "Source/AhwassaGraphicsLib/Geometry/BasicShapeGenerator.cpp"
    "Source/AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.cpp"
)
source_group("Source Files\\Geometry" FILES ${Source_Files__Geometry})

set(Source_Files__Input
    "Source/AhwassaGraphicsLib/Input/ArcBallCamera.cpp"
    "Source/AhwassaGraphicsLib/Input/FileDropper.cpp"
    "Source/AhwassaGraphicsLib/Input/FreeCamera.cpp"
    "Source/AhwassaGraphicsLib/Input/IMGUIRenderer.cpp"
    "Source/AhwassaGraphicsLib/Input/Input.cpp"
    "Source/AhwassaGraphicsLib/Input/UIElement.cpp"
)
source_group("Source Files\\Input" FILES ${Source_Files__Input})

set(Source_Files__Post_Processing
    "Source/AhwassaGraphicsLib/PostProcessing/AdditiveComposer.cpp"
    "Source/AhwassaGraphicsLib/PostProcessing/Bloom.cpp"
    "Source/AhwassaGraphicsLib/PostProcessing/CubeReflection.cpp"
    "Source/AhwassaGraphicsLib/PostProcessing/DeferredComposer.cpp"
    "Source/AhwassaGraphicsLib/PostProcessing/PostProcessingEffect.cpp"
)
source_group("Source Files\\Post Processing" FILES ${Source_Files__Post_Processing})

set(Source_Files__Renderer
    "Source/AhwassaGraphicsLib/Renderer/BasicBoxRenderer.cpp"
    "Source/AhwassaGraphicsLib/Renderer/BasicMeshRenderer.cpp"
    "Source/AhwassaGraphicsLib/Renderer/BasicRectangleRenderer.cpp"
    "Source/AhwassaGraphicsLib/Renderer/BasicTextRenderer.cpp"
    "Source/AhwassaGraphicsLib/Renderer/BasicTexture2DRenderer.cpp"
    "Source/AhwassaGraphicsLib/Renderer/BoxRenderer.cpp"
    "Source/AhwassaGraphicsLib/Renderer/DecalRenderer.cpp"
    "Source/AhwassaGraphicsLib/Renderer/DiffuseMeshRenderer.cpp"
    "Source/AhwassaGraphicsLib/Renderer/RectangleRenderer.cpp"
    "Source/AhwassaGraphicsLib/Renderer/RendererTemplate.cpp"
    "Source/AhwassaGraphicsLib/Renderer/SphereRenderer.cpp"
    "Source/AhwassaGraphicsLib/Renderer/Model3DRenderer.cpp"
)
source_group("Source Files\\Renderer" FILES ${Source_Files__Renderer})

set(Source_Files__RendererPrimitives
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Box.cpp"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Decal.cpp"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Dot.cpp"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Line.cpp"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Rectangle.cpp"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Sphere.cpp"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Text.cpp"
    "Source/AhwassaGraphicsLib/Renderer/Primitives/Decal.cpp"
)
source_group("Source Files\\Renderer\\Primitives" FILES ${Source_Files__RendererPrimitives})

set(Source_Files__Sound
    "Source/AhwassaGraphicsLib/sound/sound.cpp"
    "Source/AhwassaGraphicsLib/sound/SoundEngine.cpp"
    "Source/AhwassaGraphicsLib/sound/SoundHandler.cpp"
)
source_group("Source Files\\Sound" FILES ${Source_Files__Sound})

set(Source_Files__Uniforms
    "Source/AhwassaGraphicsLib/Uniforms/CubeTexture.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/InstancedVecMat4.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/InstancedVecVec3.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/Rendertarget.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/SSBOint.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/SSBOmat4.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/SSBOvec3.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/SSBOvec4.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/Texture.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/Uniform.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/UniformFloat.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/UniformMat4.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVec2.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVec3.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVec4.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVecMat4.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVecTexture.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVecVec2.cpp"
    "Source/AhwassaGraphicsLib/Uniforms/UniformVecVec3.cpp"
)
source_group("Source Files\\Uniforms" FILES ${Source_Files__Uniforms})

set(Source_Files__VR
    "Source/AhwassaGraphicsLib/VR/VR.cpp"
    "Source/AhwassaGraphicsLib/VR/VRController.cpp"
)
source_group("Source Files\\VR" FILES ${Source_Files__VR})

set(Source_Files__Vertex
    "Source/AhwassaGraphicsLib/Vertex/IVertex.cpp"
    "Source/AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.cpp"
    "Source/AhwassaGraphicsLib/Vertex/PositionColorVertex.cpp"
    "Source/AhwassaGraphicsLib/Vertex/PositionNormalTextureVertex.cpp"
    "Source/AhwassaGraphicsLib/Vertex/PositionNormalVertex.cpp"
    "Source/AhwassaGraphicsLib/Vertex/PositionTextureVertex.cpp"
    "Source/AhwassaGraphicsLib/Vertex/PositionTextureVertexIndex.cpp"
    "Source/AhwassaGraphicsLib/Vertex/PositionVertex.cpp"
    "Source/AhwassaGraphicsLib/Vertex/SupComVertex.cpp"
)
source_group("Source Files\\Vertex" FILES ${Source_Files__Vertex})

set(Source_Files__Widgets
    "Source/AhwassaGraphicsLib/Widgets/Button.cpp"
    "Source/AhwassaGraphicsLib/Widgets/Checkbox.cpp"
    "Source/AhwassaGraphicsLib/Widgets/Label.cpp"
    "Source/AhwassaGraphicsLib/Widgets/LineEdit.cpp"
    "Source/AhwassaGraphicsLib/Widgets/ListLayout.cpp"
    "Source/AhwassaGraphicsLib/Widgets/Slider.cpp"
)
source_group("Source Files\\Widgets" FILES ${Source_Files__Widgets})

set(lib__glad
    "lib/glad/include/glad/glad.h"
    "lib/glad/include/KHR/khrplatform.h"
    "lib/glad/src/glad.c"
)
source_group("lib\\glad" FILES ${lib__glad})

set(lib__dear_imgui_filedialog
    "lib/IMGUIFileDialog/dirent/dirent.h"
    "lib/IMGUIFileDialog/ImGuiFileDialog.cpp"
    "lib/IMGUIFileDialog/ImGuiFileDialog.h"
    "lib/IMGUIFileDialog/ImGuiFileDialogConfig.h"
    "lib/IMGUIFileDialog/stb/stb_image.h"
    "lib/IMGUIFileDialog/stb/stb_image_resize.h"
)
source_group("lib\\dear imgui filedialog" FILES ${lib__dear_imgui_filedialog})


set(ALL_FILES
    ${Header_Files}
    ${Header_Files__BufferObjects}
    ${Header_Files__Core}
    ${Header_Files__Drawables}
    ${Header_Files__Geometry}
    ${Header_Files__Input}
    ${Header_Files__PostProcessing}
    ${Header_Files__Renderer}
    ${Header_Files__RendererPrimitives}
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
    ${Source_Files__RendererPrimitives}
    ${Source_Files__Sound}
    ${Source_Files__Uniforms}
    ${Source_Files__VR}
    ${Source_Files__Vertex}
    ${Source_Files__Widgets}
    ${lib__glad}
    ${lib__dear_imgui_filedialog}
)

############################################################################
############################################################################
############################################################################

add_library(AhwassaGraphicsLib ${ALL_FILES})
set_property(TARGET AhwassaGraphicsLib PROPERTY CXX_STANDARD 20)

target_link_libraries(AhwassaGraphicsLib PRIVATE
glm::glm
IyathuumCoreLib
glfw
Freetype::Freetype
portaudio
${OPENVR_LIBRARIES}
imgui::imgui
)

target_include_directories(AhwassaGraphicsLib PRIVATE 
"${AhwassaGraphicsLib_SOURCE_DIR}/Source"
"${AhwassaGraphicsLib_SOURCE_DIR}/lib/glad/include"
"${AhwassaGraphicsLib_SOURCE_DIR}/lib/"
"${IyathuumCoreLib_SOURCE_DIR}/Source"
"${glfw_SOURCE_DIR}/Source"
"${portaudio_SOURCE_DIR}"
"${openvr_SOURCE_DIR}/headers"
"${freetype_SOURCE_DIR}/include"
"${imgui_SOURCE_DIR}"
)

set_target_properties(AhwassaGraphicsLib PROPERTIES FOLDER "Yathsou")