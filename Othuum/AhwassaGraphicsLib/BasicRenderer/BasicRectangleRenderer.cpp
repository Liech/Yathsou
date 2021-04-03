#include "BasicRectangleRenderer.h"

#include "glad/glad.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"

#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"

#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/BufferObjects/VBO.h"
#include "AhwassaGraphicsLib/Vertex/PositionVertex.h"

namespace Ahwassa {
  struct BasicRectangleRenderer::RenderVars {
    std::unique_ptr<VBO<PositionVertex>>   vbo;
    std::unique_ptr<VAO<PositionVertex>>   vao;
    std::unique_ptr<ShaderProgram>         shader;
    Window* window;
    std::unique_ptr<UniformMat4>           projection;
    std::unique_ptr<UniformVec3>           color;

    virtual ~RenderVars() {}
  };

  BasicRectangleRenderer::BasicRectangleRenderer(Window* w) {
    _vars = std::make_shared<BasicRectangleRenderer::RenderVars>();
    _vars->window = w;
    makeShader();
  }

  void BasicRectangleRenderer::drawRectangle(glm::vec2 pos, glm::vec2 size, Iyathuum::Color color) {
    Iyathuum::glmAABB<2> box;
    box.setPosition(pos);
    box.setSize(size);
    drawRectangle(box, color);
  }
  
  void BasicRectangleRenderer::drawRectangle(Iyathuum::glmAABB<2> box, Iyathuum::Color color) {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in drawText");

    _vars->color->setValue(color.to3());

    if (_clipping)
      box = _clippingBox.getIntersection(box);

    glm::vec2 pos  = box.getPosition();
    glm::vec2 size = box.getSize();

    GLfloat xpos = pos[0];
    GLfloat ypos = pos[1];

    GLfloat w = size[0];
    GLfloat h = size[1];

    std::vector<PositionVertex> vertices = {
      PositionVertex(glm::vec3(xpos,     ypos + h,0)),
      PositionVertex(glm::vec3(xpos,     ypos,    0)),
      PositionVertex(glm::vec3(xpos + w, ypos,    0)),
      PositionVertex(glm::vec3(xpos,     ypos + h,0)),
      PositionVertex(glm::vec3(xpos + w, ypos,    0)),
      PositionVertex(glm::vec3(xpos + w, ypos + h,0))
    };
    _vars->color->bind();
    _vars->vbo->setData(vertices);
    _vars->vao->draw();
  }

  void BasicRectangleRenderer::start() {
    if (_inRenderProcess == true)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in startTextRender");
    _inRenderProcess = true;
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _vars->shader->bind();
  }

  void BasicRectangleRenderer::end() {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in endTextRender");
    _inRenderProcess = false;
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
  }

  void BasicRectangleRenderer::makeShader() {
    std::cout << "Load Shader" << std::endl;

    std::string vertex_shader_source = R"(

    void main()
    {
        gl_Position = projection * vec4(position.xy, 0.0, 1.0);
    }  
   )";

    std::string fragment_shader_source = R"(
    out vec4 color;

    void main()
    {    
        color = vec4(textColor, 1.0);
    }  
   )";

    std::vector<Uniform*> uniforms;
    _vars->projection = std::make_unique<UniformMat4>("projection");
    _vars->projection->setValue(glm::ortho(0.0f, (float)_vars->window->getWidth(), 0.0f, (float)_vars->window->getHeight()));
    _vars->color = std::make_unique<UniformVec3>("textColor");
    uniforms.push_back(_vars->projection.get());
    uniforms.push_back(_vars->color.get());

    std::vector<PositionVertex> input;
    input.resize(6);
    _vars->vbo = std::make_unique<VBO<PositionVertex>>(input);
    _vars->vao = std::make_unique<VAO<PositionVertex>>(_vars->vbo.get());
    _vars->shader = std::make_unique<ShaderProgram>(PositionVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }
  void BasicRectangleRenderer::setClippingRectangle(Iyathuum::glmAABB<2> box) {
    _clipping = true;
    _clippingBox = box;
  }

  void BasicRectangleRenderer::disableClipping() {
    _clipping = false;
  }
}