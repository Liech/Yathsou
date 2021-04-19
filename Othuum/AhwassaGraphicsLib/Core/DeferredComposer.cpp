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
#include "Uniforms/UniformVecVec3.h"
#include "Uniforms/UniformVec3.h"
#include "Uniforms/UniformFloat.h"
#include "Core/Window.h"
#include "Core/ShaderProgram.h"
#include "Core/Camera.h"

namespace Ahwassa {
  DeferredComposer::DeferredComposer(Window* window, int width, int height) :r(window) {
    _fbo = std::make_shared<Ahwassa::FBO>(width,height, std::vector<std::string> {"gPosition", "gNormal", "gAlbedoSpec", "gSpecial"});
    _resultCanvas = std::make_shared<Ahwassa::Rendertarget>("Result", width, height);
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
      vec3 FragPos   = texture(gPosition  , TexCoords).rgb;
      vec3 Normal    = (texture(gNormal    , TexCoords).rgb - vec3(0.5,0.5,0.5))*2;
      vec3 Albedo    = texture(gAlbedoSpec, TexCoords).rgb;
      vec3 Special   = texture(gSpecial   , TexCoords).rgb;
      float Specular = Special.b;
      
      vec3 lighting = Albedo * 0.5;
      vec3 viewDir = normalize(CamPos - FragPos);
      for(int i = 0; i < NumberOfLights; ++i)
      {
          // diffuse
          vec3 lightDir = normalize(LightPositions[i] - FragPos);
          vec3 reflectDir = reflect(-lightDir, Normal);  
          vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * LightColors[i];
          float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
          vec3 specular = Specular * spec * LightColors[i];  
          lighting += diffuse + specular;
      }
      
      if (FragPos[0] == 0 && FragPos[1] == 0&& FragPos[2] == 0)
        discard;

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
    _projection->setValue(glm::ortho(0.0f, (float)width, 0.0f, (float)height));

    _lightPositions = std::make_shared<UniformVecVec3>("LightPositions", MAXLIGHT);
    _lightColors    = std::make_shared<UniformVecVec3>("LightColors"   , MAXLIGHT);
    _numberOfLights = std::make_shared<UniformFloat  >("NumberOfLights");
    uniforms.push_back(_lightPositions.get());
    uniforms.push_back(_lightColors   .get());
    uniforms.push_back(_numberOfLights.get());

    _camPos = std::make_shared<UniformVec3  >("CamPos");
    uniforms.push_back(_camPos.get());

    for (auto x : getRawTextures()) {
      uniforms.push_back(x.get());
      x->setBindable(false);
    }

    _vbo = std::make_unique<VBO<PositionTextureVertex>>(_vertices);
    _vao = std::make_unique<VAO>(_vbo.get());
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

  void DeferredComposer::draw() {
    r.start();
    r.draw(*getResult(), Iyathuum::glmAABB<2>(glm::vec2(0,0), glm::vec2(_width,_height)));
    r.end();
  }
}