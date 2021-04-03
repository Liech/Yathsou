#include "Graphics/Rectangles.h"

#include <iostream>
#include "glad/glad.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "Rectangle.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/BufferObjects/VBO.h"
#include "AhwassaGraphicsLib/Vertex/PositionVertex.h"

namespace Ahwassa {
  struct Rectangles::RenderVars {
    std::unique_ptr<VBO<PositionVertex>>   vbo;
    std::unique_ptr<VAO<PositionVertex>>   vao;
    std::unique_ptr<ShaderProgram>         shader;
    Window* window;
    std::unique_ptr<UniformMat4>           projection;
    std::unique_ptr<UniformMat4>           model;
    std::unique_ptr<UniformVec3>           color;

    virtual ~RenderVars() {}
  };

  Rectangles::Rectangles(Window* w) : Drawable(w) {
    _vars = std::make_shared<Rectangles::RenderVars>();
    _vars->window = w;
    makeShader();
  }

  void Rectangles::draw() {
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _vars->shader->bind();

    std::vector<size_t> destroyed;
    destroyed.resize(40);
    size_t destroyedIndex = 0;
    for (size_t i = 0; i < _rectangles.size(); i++) {
      auto rec = _rectangles[i].lock();
      if (rec) {
        shaderCall(rec);
      }
      else {
        if (destroyedIndex >= destroyed.size())
          destroyed.push_back(0);
        destroyed[destroyedIndex] = i;
        destroyedIndex++;
      }
    }
    for (size_t i = destroyedIndex; i > 0; i--)
      _rectangles.erase(_rectangles.begin() + i);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
  }

  void Rectangles::makeShader() {
    std::cout << "Load Shader" << std::endl;

    std::string vertex_shader_source = R"(

    void main()
    {
        gl_Position = projection * model * vec4(position.xy, 0.0, 1.0);
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
    _vars->model      = std::make_unique<UniformMat4>("model");

    _vars->color = std::make_unique<UniformVec3>("textColor");
    uniforms.push_back(_vars->projection.get());
    uniforms.push_back(_vars->model.get());
    uniforms.push_back(_vars->color.get());

    std::vector<PositionVertex> input;
    input.resize(6);
    _vars->vbo = std::make_unique<VBO<PositionVertex>>(input);
    _vars->vao = std::make_unique<VAO<PositionVertex>>(_vars->vbo.get());
    _vars->shader = std::make_unique<ShaderProgram>(PositionVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);

    std::vector<PositionVertex> vertices = {
    PositionVertex(glm::vec3(0, 1,0)),
    PositionVertex(glm::vec3(0, 0,0)),
    PositionVertex(glm::vec3(1, 0,0)),
    PositionVertex(glm::vec3(0, 1,0)),
    PositionVertex(glm::vec3(1, 0,0)),
    PositionVertex(glm::vec3(1, 1,0))
    };
    _vars->vbo->setData(vertices);
  }

  void Rectangles::shaderCall(std::shared_ptr<Rectangle> r) {
    auto mat = glm::mat4(1.0);
    mat = glm::translate(mat, glm::vec3(r->location.getPosition()[0], r->location.getPosition()[1], 1));
    mat = glm::scale    (mat, glm::vec3(r->location.getSize()[0]    , r->location.getSize()[1]    , 1));
    _vars->model->setValue(mat);

    _vars->color->setValue(r->color.to3());
    _vars->color->bind();
    _vars->vao->bind();
  }

  std::shared_ptr<Rectangle> Rectangles::newRectangle(Iyathuum::glmAABB<2> location, Iyathuum::Color color) {
    std::shared_ptr<Rectangle> result = std::make_shared<Rectangle>();
    result->location = location;
    result->color    = color   ;
    _rectangles.push_back(result);
    return result;
  }
}