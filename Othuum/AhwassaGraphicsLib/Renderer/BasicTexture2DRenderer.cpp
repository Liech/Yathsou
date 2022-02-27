#include "BasicTexture2DRenderer.h"

#include "glad/glad.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"

#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"

#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/BufferObjects/VBO.h"
#include "AhwassaGraphicsLib/Vertex/PositionTextureVertex.h"

namespace Ahwassa {
  struct BasicTexture2DRenderer::RenderVars {
    std::unique_ptr<VBO<PositionTextureVertex>> vbo;
    std::unique_ptr<VAO>                        vao;
    std::vector<PositionTextureVertex>          vertices;
    std::unique_ptr<Texture>                    shownTexture;
    
    std::unique_ptr<ShaderProgram>         shader;
    Window* window;
    std::unique_ptr<UniformMat4>           projection;

    virtual ~RenderVars() {}
  };

  BasicTexture2DRenderer::BasicTexture2DRenderer(Window* w) {
    _vars = std::make_shared<BasicTexture2DRenderer::RenderVars>();
    _vars->window = w;


    makeShader();
  }

  void BasicTexture2DRenderer::draw(const Texture& texture,glm::vec2 pos, glm::vec2 size) {
    Iyathuum::glmAABB<2> box;
    box.setPosition(pos);
    box.setSize(size);
    draw(texture, box);
  }
  
  void BasicTexture2DRenderer::draw(const Texture& texture,Iyathuum::glmAABB<2> box,bool yswap) {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in drawText");

    if (_clipping)
      box = _clippingBox.getIntersection(box);

    glm::vec2 pos  = box.getPosition();
    glm::vec2 size = box.getSize();

    GLfloat x = pos[0];
    GLfloat y = pos[1];

    GLfloat w = size[0];
    GLfloat h = size[1];


    _vars->vertices = {
  PositionTextureVertex(glm::vec3(x+0, y+h, 0),glm::vec2(0.0, yswap?1:0.0)),
  PositionTextureVertex(glm::vec3(x+0, y+0, 0),glm::vec2(0.0, yswap?0:1.0)),
  PositionTextureVertex(glm::vec3(x+w, y+0, 0),glm::vec2(1.0, yswap?0:1.0)),
  PositionTextureVertex(glm::vec3(x+0, y+h, 0),glm::vec2(0.0, yswap?1:0.0)),
  PositionTextureVertex(glm::vec3(x+w, y+0, 0),glm::vec2(1.0, yswap?0:1.0)),
  PositionTextureVertex(glm::vec3(x+w, y+h, 0),glm::vec2(1.0, yswap?1:0.0))
    };

    _vars->shownTexture->setTextureID(texture.getTextureID());
    _vars->shownTexture->bind();
    _vars->vbo->setData(_vars->vertices);
    _vars->vao->draw();
  }

  void BasicTexture2DRenderer::start() {
    if (_inRenderProcess == true)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in startTextRender");
    _inRenderProcess = true;
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _vars->shader->bind();
  }

  void BasicTexture2DRenderer::end() {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in endTextRender");
    _inRenderProcess = false;
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
  }

  void BasicTexture2DRenderer::makeShader() {
    std::cout << "Load Shader" << std::endl;

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
      vec4 sampled = texture(shownTexture, TexCoords);
      color = vec4(sampled.r,sampled.g,sampled.b,sampled.a);
    }  
   )";

    std::vector<Uniform*> uniforms;
    _vars->projection = std::make_unique<UniformMat4>("projection");
    _vars->projection->setValue(glm::ortho(0.0f, (float)_vars->window->getWidth(), 0.0f, (float)_vars->window->getHeight()));
    _vars->shownTexture = std::make_unique<Texture>("shownTexture", 0);
    _vars->shownTexture->setBindable(false);


    uniforms.push_back(_vars->projection.get());
    uniforms.push_back(_vars->shownTexture.get());

    std::vector<PositionTextureVertex> input;
    input.resize(6);
    _vars->vbo = std::make_unique<VBO<PositionTextureVertex>>(input);
    _vars->vao = std::make_unique<VAO>(_vars->vbo.get());
    _vars->shader = std::make_unique<ShaderProgram>(PositionTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void BasicTexture2DRenderer::setClippingRectangle(Iyathuum::glmAABB<2> box) {
    _clipping = true;
    _clippingBox = box;
  }

  void BasicTexture2DRenderer::disableClipping() {
    _clipping = false;
  }
}