#include "RectangleRenderer.h"


#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGL/DrawSpecification.h"
#include "../OpenGL/Window.h"
RectangleRenderer::RenderVars RectangleRenderer::_vars;

void RectangleRenderer::drawRectangle(glm::vec2 pos, glm::vec2 size, glm::vec3 color){
  if (_inRenderProcess == false)
    throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in drawText");

  // Activate corresponding render state	
  _vars.color->setValue(color);

  // Iterate through all characters
  std::string::const_iterator c;

  GLfloat xpos = pos[0];
  GLfloat ypos = pos[1];

  GLfloat w = size[0];
  GLfloat h = size[1];
  // Update VBO for each character
  std::vector<PositionVertex> vertices = {
    PositionVertex(glm::vec3(xpos,     ypos + h,0)),
    PositionVertex(glm::vec3(xpos,     ypos,    0)),
    PositionVertex(glm::vec3(xpos + w, ypos,    0)),
    PositionVertex(glm::vec3(xpos,     ypos + h,0)),
    PositionVertex(glm::vec3(xpos + w, ypos,    0)),
    PositionVertex(glm::vec3(xpos + w, ypos + h,0))
  };

  // Render glyph texture over quad
  _vars.vbo->setData(vertices);

  _vars.vao->bind();
}

void RectangleRenderer::startTextRender() {
  if (_inRenderProcess == true)
    throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in startTextRender");
  _inRenderProcess = true;
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  _vars.shader->bind();
}

void RectangleRenderer::endTextRender() {
  if (_inRenderProcess == false)
    throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in endTextRender");
  _inRenderProcess = false;
  glDisable(GL_BLEND);
}

void RectangleRenderer::load(DrawSpecification* spec) {
  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++ Load Text Renderer +++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  if (_alreadyLoaded)
    throw std::runtime_error("RectangleRenderer Twice Initialized.");
  _alreadyLoaded = true;
  _vars.spec = spec;
  makeShader();
  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++ End Of Load Text Renderer +++++++++++++++++++++++++++++++++++++" << std::endl;
};

void RectangleRenderer::makeShader() {
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
  _vars.projection = std::make_unique<UniformMat4>("projection");
  _vars.projection->setValue(glm::ortho(0.0f, (float)_vars.spec->getWindow()->getWidth(), 0.0f, (float)_vars.spec->getWindow()->getHeight()));
  _vars.color = std::make_unique<UniformVec3>("textColor");
  uniforms.push_back(_vars.projection.get());
  uniforms.push_back(_vars.color.get());

  std::vector<PositionVertex> input;
  input.resize(6);
  _vars.vbo    = std::make_unique<VBO<PositionVertex>>(input);
  _vars.vao    = std::make_unique<VAO<PositionVertex>>(_vars.vbo.get());
  _vars.shader = std::make_unique<ShaderProgram>(_vars.vao.get(), uniforms, vertex_shader_source, fragment_shader_source);
}