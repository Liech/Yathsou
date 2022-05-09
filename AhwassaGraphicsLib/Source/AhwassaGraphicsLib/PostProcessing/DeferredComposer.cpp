#include "DeferredComposer.h"

#include "glad/glad.h"
#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/BufferObjects/FBO.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformFloat.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"

namespace Ahwassa {
  DeferredComposer::DeferredComposer(Window* window, const glm::ivec2& resolution) :r(window) {
    _resolution = resolution;
    _fbo = std::make_shared<Ahwassa::FBO>(resolution, std::vector<std::string> {"gPosition", "gNormal", "gAlbedoSpec", "gSpecial"}, std::vector<TextureFormat>{TextureFormat::RGBA32,TextureFormat::RGBA,TextureFormat::RGBA,TextureFormat::RGBA});
    _resultCanvas = std::make_shared<Ahwassa::Rendertarget>("Result", _resolution);
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
      vec3  FragPos   = texture(gPosition  , TexCoords).rgb;
      vec3  Normal    = (texture(gNormal   , TexCoords).rgb - vec3(0.5,0.5,0.5))*2;
      vec3  Albedo    = texture(gAlbedoSpec, TexCoords).rgb;
      vec3  Special   = texture(gSpecial   , TexCoords).rgb;
      float Specular  = Special.b * SpecularValue;

      vec3 lighting = Albedo * 0.5 * AmbientValue;
      vec3 viewDir = normalize(CamPos - FragPos);
      for(int i = 0; i < NumberOfLights; ++i)
      {
          // diffuse
          vec3 lightDir = normalize(LightPositions[i] - FragPos);
          vec3 reflectDir = reflect(-lightDir, Normal);  
          vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * LightColors[i] * DiffuseValue;
          float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
          vec3 specular = Specular * spec * LightColors[i];  
          lighting += diffuse + specular;
      }
        
      color = vec4(lighting, 1.0);
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
    _projection->setValue(glm::ortho(0.0f, (float)_resolution[0], 0.0f, (float)_resolution[1]));

    _lightPositions = std::make_shared<UniformVecVec3>("LightPositions", MAXLIGHT);
    _lightColors    = std::make_shared<UniformVecVec3>("LightColors"   , MAXLIGHT);
    _numberOfLights = std::make_shared<UniformFloat  >("NumberOfLights");
    uniforms.push_back(_lightPositions.get());
    uniforms.push_back(_lightColors   .get());
    uniforms.push_back(_numberOfLights.get());

   _specular = std::make_shared<UniformFloat  >("SpecularValue");
   _diffuse  = std::make_shared<UniformFloat  >("DiffuseValue");
   _ambient  = std::make_shared<UniformFloat  >("AmbientValue");
   _specular ->setValue(1);
   _diffuse  ->setValue(1);
   _ambient  ->setValue(1);
   uniforms.push_back(_specular.get());
   uniforms.push_back(_diffuse .get());
   uniforms.push_back(_ambient .get());

    _camPos = std::make_shared<UniformVec3  >("CamPos");
    uniforms.push_back(_camPos.get());

    for (auto x : getRawTextures()) {
      uniforms.push_back(x.get());
      x->setBindable(false);
    }

    _vbo = std::make_unique<VBO<PositionTextureVertex>>(_vertices);
    _vao = std::make_shared<VAO>(_vbo.get());
    _shader = std::make_shared<ShaderProgram>(PositionTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);


    lights.resize(MAXLIGHT);
    for (int i = 0; i < lights.size(); i++) {
      lights[i] = glm::vec3(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50);
    }
    lights[0] = glm::vec3(100, 100, 0);
    clrs.resize(MAXLIGHT);
    for (int i = 0; i < clrs.size(); i++) {
      clrs[i] = glm::vec3(1,1,1);
    }
    clrs[0] = glm::vec3(1, 1, 1);
  }

  void DeferredComposer::start() {
    _projection->setValue(glm::ortho(0.0f, (float)_resolution[0], 0.0f, (float)_resolution[1]));
    _fbo->start();
    glClearColor(1,1,1, 1);
  }

  void DeferredComposer::end() {
    _fbo->end();
    _resultCanvas->start();

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _camPos->setValue(_window->camera()->getPosition());

    _lightColors   ->setValue(clrs);
    _lightPositions->setValue(lights);
    _numberOfLights->setValue(1);

    _shader->bind();

    GLfloat x = 0;
    GLfloat y = 0;

    GLfloat w = _resolution[0];
    GLfloat h = _resolution[1];

    _vertices = {
       PositionTextureVertex(glm::vec3(x + 0, y + h, 0),glm::vec2(0.0, 1.0)),
       PositionTextureVertex(glm::vec3(x + 0, y + 0, 0),glm::vec2(0.0, 0.0)),
       PositionTextureVertex(glm::vec3(x + w, y + 0, 0),glm::vec2(1.0, 0.0)),
       PositionTextureVertex(glm::vec3(x + 0, y + h, 0),glm::vec2(0.0, 1.0)),
       PositionTextureVertex(glm::vec3(x + w, y + 0, 0),glm::vec2(1.0, 0.0)),
       PositionTextureVertex(glm::vec3(x + w, y + h, 0),glm::vec2(1.0, 1.0))
    };

    for (auto x : getRawTextures())
      x->bind();

    _vbo->setData(_vertices);
    _vao->draw();

    _resultCanvas->end();
  }

  void DeferredComposer::blitDepth() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo->getID());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
    glBlitFramebuffer(0, 0, _resolution[0], _resolution[1], 0, 0, _resolution[0], _resolution[1], GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  std::vector<std::shared_ptr<Texture>> DeferredComposer::getRawTextures() const {
    return _fbo->getUniforms();
  }

  std::shared_ptr<Texture> DeferredComposer::getDepth() const {
    return _fbo->getDepth();
  }
  
  std::shared_ptr<Texture> DeferredComposer::getResult() const {
    std::shared_ptr<Ahwassa::Texture> result = std::make_shared<Ahwassa::Texture>("Deferred", _resultCanvas->getTextureID());
    result->release();
    return result;
  }

  void DeferredComposer::draw() {
    r.start();
    r.draw(*getResult(), Iyathuum::glmAABB<2>(glm::vec2(0,0), glm::vec2(_resolution[0], _resolution[1])),true);
    r.end();
  }
  
  void DeferredComposer::setResolution(const glm::ivec2& resolution) {
    _resolution = resolution;
    _fbo->setResolution(resolution);
    _resultCanvas->setResolution(resolution);
  }

  float DeferredComposer::ambient() const {
    return _ambient->getValue();
  }

  void DeferredComposer::setAmbient(float value) {
    _ambient->setValue(value);
  }

  float DeferredComposer::specular() const{
    return _specular->getValue();
  }

  void DeferredComposer::setSpecular(float value) {
    _specular->setValue(value);
  }

  float DeferredComposer::diffuse() const {
    return _diffuse->getValue();
  }

  void DeferredComposer::setDiffuse(float value) {
    _diffuse->setValue(value);
  }
}