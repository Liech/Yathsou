#include "MapRenderer.h"

#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AezeselFileIOLib/Model3D.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"

namespace Athanah {
  MapRenderer::MapRenderer(std::shared_ptr<Ahwassa::Camera> camera, std::array<std::shared_ptr<Ahwassa::Texture>, 5> textures){
    _camera = camera;
    _textures = textures;


    std::string vertex_shader_source = R"(
      out vec4 clr;
      out vec3 nrm;
      out vec3 pos;
      void main() {
      
        mat4 view = )" + _camera->getName() + R"(Projection *  )" + _camera->getName() + R"(View;
        gl_Position = view *  model *vec4(position , 1.0);
        clr = color;
        nrm = normal;
        pos = position;
      }
   )";

    std::string fragment_shader_source = R"(
     in vec4 clr;
     in vec3 nrm;
     in vec3 pos;
     
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

       float ambientStrength = 0.5;  
       float diffuseStrength = 0.5;
       float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;
     
       vec4 result = resultSample *  diff + resultSample * ambientStrength;
       result[3] = 1;
     	frag_color = result;
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
    _shader->bind();
    _camera->bind();
    mesh.draw();
    Ahwassa::Util::setDepthTest(false);
  }
}