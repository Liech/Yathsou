#include "SkyBox.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecTexture.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AhwassaGraphicsLib/Vertex/PositionTextureVertexIndex.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"

#include "AezeselFileIOLib/ImageIO.h"

namespace Athanah {
  SkyBox::SkyBox(const std::vector<unsigned char>& data, std::shared_ptr<Ahwassa::Camera> camera) {
    auto img = Aezesel::ImageIO::readDDSCube(Aezesel::ImageIO::Format::DDS,data);
    _textures = std::make_shared <Ahwassa::UniformVecTexture>("textures", img);

    _camera = camera;
    _mesh = makeCube();
    makeShader();
  }

  SkyBox::SkyBox(std::string filename, std::shared_ptr<Ahwassa::Camera> camera) {
    auto img = Aezesel::ImageIO::readDDSCube(filename);
    _textures = std::make_shared <Ahwassa::UniformVecTexture>("textures", img);

    _camera = camera;
    _mesh = makeCube();
    makeShader();
  }

  SkyBox::SkyBox(std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>>& img, std::shared_ptr<Ahwassa::Camera> camera) {
    _textures = std::make_shared <Ahwassa::UniformVecTexture>("textures", img);

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
      flat out float Index;

      void main() {
        mat4 view = )" + _camera->getName() + R"(Projection *  )" + _camera->getName() + R"(View;
        gl_Position = view*Scale*vec4(position , 1.0);
        TexCoords = texture;
        Index = index;
      } 
   )";

    std::string fragment_shader_source = R"(
     layout (location = 0) out vec4 gPosition;
     layout (location = 1) out vec4 gNormal;
     layout (location = 2) out vec4 gAlbedoSpec;
     layout (location = 3) out vec4 gSpecial;

     in vec2 TexCoords;
     flat in float Index;

     void main() {
       vec4  sky = texture(textures, vec3(TexCoords,Index));
       
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

    uniforms.push_back(_textures.get());
    _mat = std::make_shared<Ahwassa::UniformMat4>("Scale");
    uniforms.push_back(_mat.get());
    _mat->setValue(glm::scale(glm::mat4(1), glm::vec3(50, 50, 50)));
    _shader = std::make_unique<Ahwassa::ShaderProgram>(Ahwassa::PositionTextureVertexIndex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }
  
  std::shared_ptr<Ahwassa::IMesh> SkyBox::makeCube() {
      std::vector<Ahwassa::PositionTextureVertexIndex> input;
      float start = -0.5f;
      float end = 0.5f;
      //front
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, start, end), glm::vec2(1, 1),0));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end  , start, end), glm::vec2(0, 1),0));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end  , end  , end), glm::vec2(0, 0),0));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, end  , end), glm::vec2(1, 0),0));

      //right
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end, end  , end  ), glm::vec2(1, 0),4));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end, end  , start), glm::vec2(0, 0),4));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end, start, start), glm::vec2(0, 1),4));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end, start, end  ), glm::vec2(1, 1),4));

      //back
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, start, start), glm::vec2(0, 1),1));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end  , start, start), glm::vec2(1, 1),1));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end  , end  , start), glm::vec2(1, 0),1));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, end  , start), glm::vec2(0, 0),1));
                                                                                                         
      //left
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, start, start), glm::vec2(1, 1),5));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, start, end  ), glm::vec2(0, 1),5));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, end  , end  ), glm::vec2(0, 0),5));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, end  , start), glm::vec2(1, 0),5));

      //upper
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end  , end, end  ), glm::vec2(1, 1),2));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, end, end  ), glm::vec2(1, 0),2));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, end, start), glm::vec2(0, 0),2));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end  , end, start), glm::vec2(0, 1),2));

      //bottom
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, start, start), glm::vec2(0, 1),3));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end  , start, start), glm::vec2(0, 0),3));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(end  , start, end  ), glm::vec2(1, 0),3));
      input.push_back(Ahwassa::PositionTextureVertexIndex(glm::vec3(start, start, end  ), glm::vec2(1, 1),3));

      //note every face of the cube is on a single line
      auto indices = std::vector<int>{
        0,  1,  2,  0,  2,  3,   //front
        4,  5,  6,  4,  6,  7,   //right
        8,  9,  10, 8,  10, 11,  //back
        12, 13, 14, 12, 14, 15,  //left
        16, 17, 18, 16, 18, 19,  //upper
        20, 21, 22, 20, 22, 23  //bottom
      };

      return std::make_shared<Ahwassa::Mesh<Ahwassa::PositionTextureVertexIndex>>(input,indices);
  }

}

