#include "Bloom.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Uniforms/UniformFloat.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"

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

    //https://learnopengl.com/Advanced-Lighting/Bloom
    std::string fragment_shader_source = R"(
     in vec2 TexCoords;    
     out vec4 color;

    
    void main()
    {    
      vec4  inp = texture(Input, TexCoords);

      vec2 tex_offset = 1.0 / textureSize(Input, 0); // gets size of single texel
      vec3 result = texture(Input, TexCoords).rgb; // current fragment's contribution
      
      int width = 100;
      for(int i = 1; i < width; ++i)
      {
        float w = float(width-i) / float(width);
        w = w*w;
        float bloomPx = texture(BloomMap, TexCoords + vec2(tex_offset.x * i, 0.0))[int(BloomChannel)];
        float bloomMx = texture(BloomMap, TexCoords - vec2(tex_offset.x * i, 0.0))[int(BloomChannel)];
        float bloomPy = texture(BloomMap, TexCoords + vec2(0.0 ,tex_offset.y * i))[int(BloomChannel)];
        float bloomMy = texture(BloomMap, TexCoords - vec2(0.0 ,tex_offset.y * i))[int(BloomChannel)];
        float bl = bloomPx+bloomMx+bloomPy+bloomMy;
        result += vec3(bl,bl,bl)* w;
      }

      color = vec4(result, 1.0);
    }  
   )";

    _vertices = {
      Ahwassa::PositionTextureVertex(glm::vec3(0,1, 0),glm::vec2(0.0, 1.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(0,0, 0),glm::vec2(0.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(1,0, 0),glm::vec2(1.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(0,1, 0),glm::vec2(0.0, 1.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(1,0, 0),glm::vec2(1.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(1,1, 0),glm::vec2(1.0, 1.0))
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
    _vbo = std::make_unique<Ahwassa::VBO<Ahwassa::PositionTextureVertex>>(_vertices);
    _vao = std::make_unique<Ahwassa::VAO>(_vbo.get());
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


    float x = 0;
    float y = 0;
    float w = _width;
    float h = _height;

    _vertices = {
       Ahwassa::PositionTextureVertex(glm::vec3(x + 0, y + h, 0),glm::vec2(0.0, 1.0)),
       Ahwassa::PositionTextureVertex(glm::vec3(x + 0, y + 0, 0),glm::vec2(0.0, 0.0)),
       Ahwassa::PositionTextureVertex(glm::vec3(x + w, y + 0, 0),glm::vec2(1.0, 0.0)),
       Ahwassa::PositionTextureVertex(glm::vec3(x + 0, y + h, 0),glm::vec2(0.0, 1.0)),
       Ahwassa::PositionTextureVertex(glm::vec3(x + w, y + 0, 0),glm::vec2(1.0, 0.0)),
       Ahwassa::PositionTextureVertex(glm::vec3(x + w, y + h, 0),glm::vec2(1.0, 1.0))
    };

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
    _window->renderer().texture().start();
    _window->renderer().texture().draw(*getResult(), Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(_width, _height)));
    _window->renderer().texture().end();
  }
}