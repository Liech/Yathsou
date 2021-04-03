#include "InstancedRenderer/InstancedRectangleRenderer.h"

#include <iostream>
#include "glad/glad.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "Rectangle.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecMat4.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/BufferObjects/VBO.h"
#include "AhwassaGraphicsLib/Vertex/PositionVertex.h"

namespace Ahwassa {
  struct InstancedRectangleRenderer::RenderVars {
    std::unique_ptr<VBO<PositionVertex>> vbo;
    std::unique_ptr<VAO<PositionVertex>> vao;
    std::unique_ptr<ShaderProgram>       shader;
    Window* window;                      
    std::unique_ptr<UniformMat4>         projection;
    std::unique_ptr<UniformVecMat4>      models;
    std::unique_ptr<UniformVecVec3>      colors;

    virtual ~RenderVars() {}
  };

  InstancedRectangleRenderer::InstancedRectangleRenderer(Window* w) : Drawable(w) {
    _vars = std::make_shared<InstancedRectangleRenderer::RenderVars>();
    _vars->window = w;
    _bufferSize = 1000;
    makeModelArray(_bufferSize);
    makeShader();
  }

  void InstancedRectangleRenderer::draw() {

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _vars->shader->bind();

    std::vector<glm::mat4> matrices;
    std::vector<glm::vec3> colors  ;
    matrices.resize(_bufferSize);
    colors  .resize(_bufferSize);

    std::vector<size_t> destroyed;
    destroyed.resize(40);
    size_t destroyedIndex = 0;
    size_t current = 0;
    for (size_t i = 0; i < _InstancedRectangleRenderer.size(); i++) {
      auto rec = _InstancedRectangleRenderer[i].lock();
      if (rec) {
        if (current == _bufferSize) {
          shaderCall(matrices, colors, current);
          current = 0;
        }
        matrices[current] = rec->matrix  ();
        colors  [current] = rec->colorVec();
        current++;
      }
      else {
        if (destroyedIndex >= destroyed.size())
          destroyed.push_back(0);
        destroyed[destroyedIndex] = i;
        destroyedIndex++;
      }
    }
    for (size_t i = destroyedIndex; i > 0; i--)
      _InstancedRectangleRenderer.erase(_InstancedRectangleRenderer.begin() + i);


    shaderCall(matrices,colors,current);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
  }

  void InstancedRectangleRenderer::makeModelArray(size_t bufferSize) {
    _vars->models = std::make_unique<UniformVecMat4>("models", bufferSize);
    _vars->colors = std::make_unique<UniformVecVec3>("colors", bufferSize);
  }

  void InstancedRectangleRenderer::makeShader() {
    std::cout << "Load Shader" << std::endl;

    std::string vertex_shader_source = R"(
    
    out vec3 clr;
    void main()
    {
        gl_Position = projection * models[gl_InstanceID] * vec4(position.xy, 0.0, 1.0);
        clr = colors[gl_InstanceID];
    }  
   )";

    std::string fragment_shader_source = R"(
    out vec4 color;
    in vec3 clr;
    void main()
    {    
        color = vec4(clr, 1.0);
    }  
   )";

    std::vector<Uniform*> uniforms;
    _vars->projection = std::make_unique<UniformMat4>("projection");
    _vars->projection->setValue(glm::ortho(0.0f, (float)_vars->window->getWidth(), 0.0f, (float)_vars->window->getHeight()));

    uniforms.push_back(_vars->projection.get());
    uniforms.push_back(_vars->models.get());
    uniforms.push_back(_vars->colors.get());

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

  void InstancedRectangleRenderer::shaderCall(const std::vector<glm::mat4>& mats, const std::vector<glm::vec3>&clr, size_t amount) {
    _vars->models->setValue(mats);
    _vars->colors->setValue(clr);
    _vars->models->bind();
    _vars->colors->bind();
    _vars->vao->drawInstanced(amount);
  }

  std::shared_ptr<Rectangle> InstancedRectangleRenderer::newRectangle(Iyathuum::glmAABB<2> location, Iyathuum::Color color) {
    std::shared_ptr<Rectangle> result = std::make_shared<Rectangle>();
    result->location = location;
    result->color    = color   ;
    _InstancedRectangleRenderer.push_back(result);
    return result;
  }
}