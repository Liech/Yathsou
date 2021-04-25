#include "SkyBox.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AhwassaGraphicsLib/Vertex/PositionTextureVertex.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"

#include "AezeselFileIOLib/ImageIO.h"

namespace Athanah {
  SkyBox::SkyBox(std::string filename, std::shared_ptr<Ahwassa::Camera> camera) {
    auto img = Aezesel::ImageIO::readDDSCube(filename);
 
    _front  = std::make_shared <Ahwassa::Texture>("front" , img[0].get());
    _right  = std::make_shared <Ahwassa::Texture>("right" , img[1].get());
    _back   = std::make_shared <Ahwassa::Texture>("back"  , img[2].get());
    _left   = std::make_shared <Ahwassa::Texture>("left"  , img[3].get());
    _top    = std::make_shared <Ahwassa::Texture>("top"   , img[4].get());
    _bottom = std::make_shared <Ahwassa::Texture>("bottom", img[5].get());
    
    _camera = camera;
    _mesh = makeCube();
    makeShader();
  }   
  
  void SkyBox::draw() {
    Ahwassa::Util::enableCulling(false);
    Ahwassa::Util::setDepthTest(false);
    Ahwassa::Util::depthMask(false);
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, _camera->getPosition());
    model = glm::scale(model, glm::vec3(50, 50, 50));
    _mat->setValue(model);
    _camera->bind();
    _shader->bind();
    _mesh->draw();
  }
  
  void SkyBox::makeShader() {
    std::string vertex_shader_source = R"(
      out vec2 TexCoords;

      void main() {
        //vec3 camPos = )" + _camera->getName() + R"(Position;
        mat4 view = )" + _camera->getName() + R"(Projection *  )" + _camera->getName() + R"(View;
        //gl_Position = vec4(camPos,1.0) + Scale*vec4(position , 1.0);
        gl_Position = view*Scale*vec4(position , 1.0);
        TexCoords = texture;
      } 
   )";//)" + _camera->getName() + R"(Projection *

    std::string fragment_shader_source = R"(
     layout (location = 0) out vec4 gPosition;
     layout (location = 1) out vec4 gNormal;
     layout (location = 2) out vec4 gAlbedoSpec;
     layout (location = 3) out vec4 gSpecial;

     in vec2 TexCoords;

     void main() {
       vec4  sky = texture(front, TexCoords);
       
       gAlbedoSpec.rgb = sky.rgb;
       gAlbedoSpec.a = 1;
       gNormal.rgb = vec3(0,0,0); 
       gNormal.a = 1;
       gPosition.rgb = vec3(0,0,0); 	
       gPosition.a = 1;
       gSpecial.rgb = vec3(0,0,0);
       gSpecial.a = 1;
     }
   )";
    std::vector<Ahwassa::Uniform*> uniforms;
    std::vector<Ahwassa::Uniform*> cameraUniforms = _camera->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    uniforms.push_back(_front .get());
    uniforms.push_back(_right .get());
    uniforms.push_back(_back  .get());
    uniforms.push_back(_left  .get());
    uniforms.push_back(_top   .get());
    uniforms.push_back(_bottom.get());
    _mat = std::make_shared<Ahwassa::UniformMat4>("Scale");
    uniforms.push_back(_mat.get());
    _mat->setValue(glm::scale(glm::mat4(1), glm::vec3(50, 50, 50)));
    _shader = std::make_unique<Ahwassa::ShaderProgram>(Ahwassa::PositionTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }
  
  std::shared_ptr<Ahwassa::IMesh> SkyBox::makeCube() {
      std::vector<Ahwassa::PositionTextureVertex> input;
      float start = -0.5f;
      float end = 0.5f;
      //front
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, start, end), glm::vec2(1, 1)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end  , start, end), glm::vec2(0, 1)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end  , end  , end), glm::vec2(0, 0)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, end  , end), glm::vec2(1, 0)));

      //right
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end, end  , end  ), glm::vec2(1, 0)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end, end  , start), glm::vec2(0, 0)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end, start, start), glm::vec2(0, 1)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end, start, end  ), glm::vec2(1, 1)));

      //back
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, start, start), glm::vec2(1, 1)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end  , start, start), glm::vec2(0, 1)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end  , end  , start), glm::vec2(0, 0)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, end  , start), glm::vec2(1, 0)));

      //left
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, start, start), glm::vec2(0, 1)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, start, end  ), glm::vec2(1, 1)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, end  , end  ), glm::vec2(1, 0)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, end  , start), glm::vec2(0, 0)));

      //upper
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end  , end, end  ), glm::vec2(0, 0)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, end, end  ), glm::vec2(1, 0)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, end, start), glm::vec2(1, 1)));
      input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end  , end, start), glm::vec2(0, 1)));

      //bottom
      //input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, start, start), glm::vec2(1, 1)));
      //input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end  , start, start), glm::vec2(0, 1)));
      //input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(end  , start, end  ), glm::vec2(0, 0)));
      //input.push_back(Ahwassa::PositionTextureVertex(glm::vec3(start, start, end  ), glm::vec2(1, 0)));

      //note every face of the cube is on a single line
      auto indices = std::vector<int>{
        0,  1,  2,  0,  2,  3,   //front
        4,  5,  6,  4,  6,  7,   //right
        8,  9,  10, 8,  10, 11,  //back
        12, 13, 14, 12, 14, 15,  //left
        //16, 17, 18, 16, 18, 19,  //upper
        //20, 21, 22, 20, 22, 23  //bottom
      };

      return std::make_shared<Ahwassa::Mesh<Ahwassa::PositionTextureVertex>>(input,indices);
  }

}

