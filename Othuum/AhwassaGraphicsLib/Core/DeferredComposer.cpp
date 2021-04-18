#include "DeferredComposer.h"

#include "glad/glad.h"
#include <vector>
#include <string>
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "BufferObjects/FBO.h"
#include "BufferObjects/VAO.h"
#include "Uniforms/Rendertarget.h"
#include "Uniforms/Texture.h"
#include "Uniforms/UniformMat4.h"
#include "Core/Window.h"
#include "Core/ShaderProgram.h"

namespace Ahwassa {
  DeferredComposer::DeferredComposer(Window* window, int width, int height) :r(window) {
    _fbo = std::make_shared<Ahwassa::FBO>(width,height, std::vector<std::string> {"gPosition", "gNormal", "gAlbedoSpec"});
    _resultCanvas = std::make_shared<Ahwassa::Rendertarget>("Result", width, height);
    _width = width;
    _height = height;

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
      vec4 sampled = texture(gPosition, TexCoords);
      color = vec4(sampled.r,sampled.g,sampled.b,sampled.a);
    }  
   )";

    _vertices = {
      PositionTextureVertex(glm::vec3(0,1, 0),glm::vec2(0.0, 0.0)),
      PositionTextureVertex(glm::vec3(0,0, 0),glm::vec2(0.0, 1.0)),
      PositionTextureVertex(glm::vec3(1,0, 0),glm::vec2(1.0, 1.0)),
      PositionTextureVertex(glm::vec3(0,1, 0),glm::vec2(0.0, 0.0)),
      PositionTextureVertex(glm::vec3(1,0, 0),glm::vec2(1.0, 1.0)),
      PositionTextureVertex(glm::vec3(1,1, 0),glm::vec2(1.0, 0.0))
    };
    std::vector<Uniform*> uniforms;
    _projection = std::make_unique<UniformMat4>("projection");
    uniforms.push_back(_projection.get());
    _projection->setValue(glm::ortho(0.0f, (float)width, 0.0f, (float)height));

    for (auto x : getRawTextures()) {
      uniforms.push_back(x.get());
      x->setBindable(false);
    }

    _vbo = std::make_unique<VBO<PositionTextureVertex>>(_vertices);
    _vao = std::make_unique<VAO>(_vbo.get());
    _shader = std::make_shared<ShaderProgram>(PositionTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void DeferredComposer::start() {
    _fbo->start();
  }

  void DeferredComposer::end() {
    _fbo->end();
    _resultCanvas->start();
   

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _shader->bind();

    GLfloat x = 0;
    GLfloat y = 0;

    GLfloat w = _width;
    GLfloat h = _height;

    _vertices = {
       PositionTextureVertex(glm::vec3(x + 0, y + h, 0),glm::vec2(0.0, 0.0)),
       PositionTextureVertex(glm::vec3(x + 0, y + 0, 0),glm::vec2(0.0, 1.0)),
       PositionTextureVertex(glm::vec3(x + w, y + 0, 0),glm::vec2(1.0, 1.0)),
       PositionTextureVertex(glm::vec3(x + 0, y + h, 0),glm::vec2(0.0, 0.0)),
       PositionTextureVertex(glm::vec3(x + w, y + 0, 0),glm::vec2(1.0, 1.0)),
       PositionTextureVertex(glm::vec3(x + w, y + h, 0),glm::vec2(1.0, 0.0))
    };

    for (auto x : getRawTextures())
      x->bind();

    _vbo->setData(_vertices);
    _vao->draw();


    //r.start();
    //r.draw(*getRawTextures()[0], Iyathuum::glmAABB<2>(glm::vec2(0,0), glm::vec2(_width,_height)));
    //r.end();

    _resultCanvas->end();
  }

  std::vector<std::shared_ptr<Texture>> DeferredComposer::getRawTextures() {
    return _fbo->getUniforms();
  }

  std::shared_ptr<Texture> DeferredComposer::getResult() {
    std::shared_ptr<Ahwassa::Texture> result = std::make_shared<Ahwassa::Texture>("Result", _resultCanvas->getTextureID());
    result->release();
    return result;
  }
}