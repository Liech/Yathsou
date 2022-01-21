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
    std::unique_ptr<VAO>                   vao;
    std::unique_ptr<ShaderProgram>         shader;
    Window* window;
    std::unique_ptr<UniformMat4>           projection;
    std::unique_ptr<UniformVec3>           color;

    virtual ~RenderVars() {}
  };

  BasicRectangleRenderer::BasicRectangleRenderer(Window* w) {
    _resolution = glm::ivec2(w->getWidth(), w->getHeight());
    _vars = std::make_shared<BasicRectangleRenderer::RenderVars>();
    _vars->window = w;
    makeShader();
  }

  void BasicRectangleRenderer::drawRectangle(const glm::vec2& pos, const glm::vec2& size, const Iyathuum::Color& color) {
    Iyathuum::glmAABB<2> box;
    box.setPosition(pos);
    box.setSize(size);
    drawRectangle(box, color);
  }
  
  void BasicRectangleRenderer::drawRectangle(const Iyathuum::glmAABB<2>& Box, const Iyathuum::Color& color) {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in drawText");

    Iyathuum::glmAABB<2> box = Box;

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

  void BasicRectangleRenderer::drawLine(const glm::vec2& posA, const glm::vec2& posB, float thicknessPx, const Iyathuum::Color& color) {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in drawText");

    _vars->color->setValue(color.to3());

    glm::vec2 dir = glm::normalize(posB - posA);
    glm::vec2 ortho = glm::vec2(dir.y, -dir.x) * thicknessPx * 0.5f;

    std::vector<PositionVertex> vertices = {
      PositionVertex(glm::vec3(posA[0] + ortho[0],posA[1] + ortho[1], 0)),
      PositionVertex(glm::vec3(posB[0] + ortho[0],posB[1] + ortho[1], 0)),
      PositionVertex(glm::vec3(posB[0] - ortho[0],posB[1] - ortho[1], 0)),
      PositionVertex(glm::vec3(posB[0] - ortho[0],posB[1] - ortho[1], 0)),
      PositionVertex(glm::vec3(posA[0] - ortho[0],posA[1] - ortho[1], 0)),
      PositionVertex(glm::vec3(posA[0] + ortho[0],posA[1] + ortho[1], 0))
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
    _vars->projection->setValue(glm::ortho(0.0f, (float)_resolution[0], 0.0f, (float)_resolution[1]));
    _vars->color = std::make_unique<UniformVec3>("textColor");
    uniforms.push_back(_vars->projection.get());
    uniforms.push_back(_vars->color.get());

    std::vector<PositionVertex> input;
    input.resize(6);
    _vars->vbo = std::make_unique<VBO<PositionVertex>>(input);
    _vars->vao = std::make_unique<VAO>(_vars->vbo.get());
    _vars->shader = std::make_unique<ShaderProgram>(PositionVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void BasicRectangleRenderer::setResolution(const glm::ivec2& newResolution) {
    _resolution = newResolution;
    _vars->projection->setValue(glm::ortho(0.0f, (float)_resolution[0], 0.0f, (float)_resolution[1]));
  }

  void BasicRectangleRenderer::setClippingRectangle(const Iyathuum::glmAABB<2>& box) {
    _clipping = true;
    _clippingBox = box;
  }

  void BasicRectangleRenderer::disableClipping() {
    _clipping = false;
  }

  void BasicRectangleRenderer::drawCircle(const glm::vec2& center, const glm::vec2& radius, float rotation, float thickness, const Iyathuum::Color& clr, float precision) {
    float rad_angle = glm::radians(rotation);
    auto rotatedEllipse = [&radius, rad_angle](float deg_t) {
      //https://math.stackexchange.com/questions/2645689/what-is-the-parametric-equation-of-a-rotated-ellipse-given-the-angle-of-rotatio
      float rad_t = glm::radians(deg_t);
      float rx = radius[0] * std::cos(rad_angle) * std::cos(rad_t) - radius[1] * std::sin(rad_angle) * std::sin(rad_t);
      float ry = radius[0] * std::cos(rad_angle) * std::sin(rad_t) + radius[1] * std::sin(rad_angle) * std::cos(rad_t);
      return glm::vec2(rx, ry);
    };
    
    glm::vec2 previous = rotatedEllipse(-precision);
    for (float current = 0; current < 360; current += precision) {
      glm::vec2 now  = rotatedEllipse(current);
      drawLine(center + previous, center + now, thickness, clr);
      previous = now;
    }
  }

}