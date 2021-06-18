#include "MapRenderer.h"

#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AezeselFileIOLib/Model3D.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"

namespace Athanah {
  MapRenderer::MapRenderer(std::shared_ptr<Ahwassa::Camera> camera){
    _camera = camera;


    std::string vertex_shader_source = R"(
      out vec4 clr;
      out vec3 nrm;
      void main() {
      
        mat4 view = )" + _camera->getName() + R"(Projection *  )" + _camera->getName() + R"(View;
        gl_Position = view *  model *vec4(position , 1.0);
        clr = color;
        nrm = normal;
      }
   )";

    std::string fragment_shader_source = R"(
     in vec4 clr;
     in vec3 nrm;
     
     out vec4 frag_color;
     void main() {
       float ambientStrength = 0.5;  
       float diffuseStrength = 0.5;
       float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;
     
       vec4 result = clr *  diff + clr * ambientStrength;
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