#include "MapRenderer.h"

#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "AezeselFileIOLib/Model3D.h"
#include "AezeselFileIOLib/ImageIO.h"

namespace Athanah {
  MapRenderer::MapRenderer(std::shared_ptr<Ahwassa::Camera> camera, std::array<std::string,5> textures, Gamedata& gamedata){
    _camera = camera;

    for (int i = 0; i < textures.size(); i++)
    {
      auto img = Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS,gamedata.loadBinary(textures[i].substr(1)));
      _textures[i] = std::make_shared<Ahwassa::Texture>("TerrainTexture" + std::to_string(i), img.get());
    }

    std::string vertex_shader_source = R"(
      out vec4 clr;
      out vec3 nrm;
      out vec3 pos;
      out vec3 FragPos;
      void main() {
      
        mat4 view = )" + _camera->getName() + R"(Projection *  )" + _camera->getName() + R"(View;
        gl_Position = view *vec4(position , 1.0);
        clr = color;
        nrm    = (model* vec4(normal, 1.0)).xyz;
        pos = position;
        FragPos   = (model * vec4(position , 1.0)).xyz;
      }
   )";

    std::string fragment_shader_source = R"(
     layout (location = 0) out vec4 gPosition;
     layout (location = 1) out vec4 gNormal;
     layout (location = 2) out vec4 gAlbedoSpec;
     layout (location = 3) out vec4 gSpecial;

     in vec4 clr;
     in vec3 nrm;
     in vec3 pos;
     in vec3 FragPos;
     
     out vec4 frag_color;
     void main() {
       vec4 baseTexture = texture(TerrainTexture0, vec2(pos.x,pos.z));
       vec4 layerAlpha  = texture(TerrainTexture1, vec2(pos.x,pos.z));
       vec4 layerBlue   = texture(TerrainTexture2, vec2(pos.x,pos.z));
       vec4 layerGreen  = texture(TerrainTexture3, vec2(pos.x,pos.z));
       vec4 layerRed    = texture(TerrainTexture4, vec2(pos.x,pos.z));

       vec4 resultSample = baseTexture;
       resultSample = layerRed   * clr[0] + resultSample * (1-clr[0]);
       resultSample = layerGreen * clr[1] + resultSample * (1-clr[1]);
       resultSample = layerBlue  * clr[2] + resultSample * (1-clr[2]);
       resultSample = layerAlpha * clr[3] + resultSample * (1-clr[3]);

     
       gAlbedoSpec = resultSample;
       gAlbedoSpec.a = 1;
       gNormal.rgb = (normalize(nrm).rgb /2.0 + vec3(0.5,0.5,0.5));  
       gNormal.a = 1;
       gPosition.rgb = FragPos.rgb; 	
       gPosition.a = 1;
       gSpecial.r = 0;
       gSpecial.g = 0;
       gSpecial.b = 0;
       gSpecial.a = 1;
     }
   )";

    std::vector<Ahwassa::Uniform*> uniforms;
    std::vector<Ahwassa::Uniform*> cameraUniforms = _camera->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    _light     = std::make_unique<Ahwassa::UniformVec3>("Light");
    _transform = std::make_unique<Ahwassa::UniformMat4>("model");
    _light->setValue(glm::normalize(glm::vec3(0)));
    uniforms.push_back(_light    .get());
    uniforms.push_back(_transform.get());
    for (int i = 0; i < 5; i++)
      uniforms.push_back(_textures[i].get());
    _transform->setValue(glm::mat4(1.0));
    _light->setValue(glm::normalize(glm::vec3(25, 31, -21)));
    _shader = std::make_shared<Ahwassa::ShaderProgram>(Ahwassa::PositionColorNormalVertex::getBinding(),uniforms,vertex_shader_source,fragment_shader_source);
  }
  
  MapRenderer::~MapRenderer() {
  
  }

  void MapRenderer::draw(Ahwassa::IMesh& mesh) {

    Ahwassa::Util::setDepthTest(true);
    Ahwassa::Util::setDepthFuncLess();
    Ahwassa::Util::depthMask(true);
    _camera->bind();
    _shader->bind();
    mesh.draw();
    Ahwassa::Util::setDepthTest(false);
  }

  void MapRenderer::setTextures(std::array<std::shared_ptr<Ahwassa::Texture>, 5> textures) {
    _textures = textures;
  }
}