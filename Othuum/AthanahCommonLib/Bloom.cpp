#include "Bloom.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Uniforms/UniformFloat.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Util.h"

namespace Athanah {
  Bloom::Bloom(Ahwassa::Window* window, int width, int height) {
    _result = std::make_shared<Ahwassa::Rendertarget>("Result", width, height);
    _width = width;
    _height = height;
    _window = window;

    std::string vertex_shader_source = R"(
    out vec2 TexCoords;

    void main()
    {
      gl_Position = projection * vec4(position.xy, 0.0, 1.0);
      TexCoords = texture;
    }  
   )";

    std::string fragment_shader_source = R"(
     in vec2 TexCoords;    
     out vec4 color;

    void main()
    {    
      float bloom = texture(BloomMap, TexCoords)[BloomChannel];
      vec4  input = texture(Input   , TexCoords);


      color = vec4(lighting, 1.0);
    }  
   )";

    _vertices = {
      Ahwassa::PositionTextureVertex(glm::vec3(0,1, 0),glm::vec2(0.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(0,0, 0),glm::vec2(0.0, 1.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(1,0, 0),glm::vec2(1.0, 1.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(0,1, 0),glm::vec2(0.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(1,0, 0),glm::vec2(1.0, 1.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(1,1, 0),glm::vec2(1.0, 0.0))
    };

    std::vector<Ahwassa::Uniform*> uniforms;

    _projection = std::make_unique<Ahwassa::UniformMat4>("projection");
    _projection->setValue(glm::ortho(0.0f, (float)width, 0.0f, (float)height));

    _bloomMap = std::make_shared<Ahwassa::Texture>("BloomMap", 0);
    _input    = std::make_shared<Ahwassa::Texture>("Input"   , 0);
    _bloomChannel = std::make_shared<Ahwassa::UniformFloat>("BloomChannel");

    uniforms.push_back(_projection  .get());
    uniforms.push_back(_bloomMap    .get());
    uniforms.push_back(_input       .get());
    uniforms.push_back(_bloomChannel.get());

    _shader = std::make_shared<Ahwassa::ShaderProgram>(Ahwassa::PositionTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);

  }

  void Bloom::draw(std::shared_ptr<Ahwassa::Texture> input, std::shared_ptr<Ahwassa::Texture> bloomMap, int channel) {
    _bloomChannel->setValue(channel);
    _bloomMap    ->setTextureID(bloomMap->getTextureID());
    _input       ->setTextureID(input->getTextureID());

    _result->start();
    Ahwassa::Util::setBlend(true);
    Ahwassa::Util::setDepthTest(false);
    Ahwassa::Util::setTextureBlend();

    _shader->bind();

    _vbo->setData(_vertices);
    _vao->draw();

    _result->end();
  }

  std::shared_ptr<Ahwassa::Texture> Bloom::getResult() {
    std::shared_ptr<Ahwassa::Texture> result = std::make_shared<Ahwassa::Texture>("Result", _result->getTextureID());
    result->release();
    return result;
  }

  void Bloom::drawResult() {
    r.start();
    r.draw(*getResult(), Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(_width, _height)));
    r.end();
  }
}