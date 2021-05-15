//#include "Model3DRenderer.h"
//
//#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"
//#include "AhwassaGraphicsLib/Uniforms/SSBOmat4.h"
//#include "AhwassaGraphicsLib/Uniforms/Texture.h"
//
//namespace Athanah {
//  Model3DRenderer::Model3DRenderer(std::shared_ptr<Ahwassa::Camera> camera) : 
//    Ahwassa::RendererTemplate<Model3DRendererMesh>(camera,Ahwassa::PositionNormalVertex::getBinding()){
//    
//  }
//
//  Model3DRenderer::~Model3DRenderer() {
//
//  }
//
//  const std::string Model3DRenderer::vertexShader() const {
//    return R"(
//     out vec2 texCoords;
//     out vec3 fragPos  ;
//     out vec3 normal   ;
//     out vec3 clr      ;
//
//     void main() {
//        mat4 view = )" + getCamera()->getName() + R"(Projection *  )" + getCamera()->getName() + R"(View;
//        mat4 world = models[gl_InstanceID];
//        gl_Position = view * world * vec4(position , 1.0);
//        world[3] = vec4(0, 0, 0, 1); //cancel translation
//
//        clr       = colors[gl_InstanceID];
//        Normal    = (modelsRot[gl_InstanceID] * vec4(normal, 1.0)).xyz;
//        texCoords = uv1;
//        fragPos   = (world * vec4(position , 1.0)).xyz;
//     }
//    )";
//  }
//
//  const std::string Model3DRenderer::fragmentShader() const {
//    return R"(
//     layout (location = 0) out vec4 gPosition;
//     layout (location = 1) out vec4 gNormal;
//     layout (location = 2) out vec4 gAlbedoSpec;
//     layout (location = 3) out vec4 gSpecial;
//
//     in vec2 texCoords;
//     in vec3 fragPos  ;
//     in vec3 Normal   ;
//     in vec3 clr      ;
//
//     void main() {
//       vec4 albedo = texture(Albedo, TexCoords);
//
//       gAlbedoSpec.rgb = (albedo).rgb;
//       gAlbedoSpec.a = 1;
//       gNormal.rgb = normalize(Normal).rgb; 
//       gNormal.a = 1;
//       gPosition.rgb = FragPos.rgb; 	
//       gPosition.a = 1;
//
//       gSpecial.r = 0;
//       gSpecial.g = 0;
//       gSpecial.b = 0;
//       gSpecial.a = 1;
//
//     }
//    )";
//  }
//
//  std::vector<std::shared_ptr<Ahwassa::Uniform>> Model3DRenderer::initUniforms() {
//    return std::vector<std::shared_ptr<Ahwassa::Uniform>>{};
//  }
//
//  void Model3DRenderer::vectorize(const size_t& index, std::shared_ptr<Model3DRendererMesh>) {
//
//  }
//
//  void Model3DRenderer::bind() {
//
//  }
//}