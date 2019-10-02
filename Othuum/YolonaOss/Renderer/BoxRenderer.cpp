#include "BoxRenderer.h"
#include "glad/glad.h"
#include "../OpenGL/PositionNormalVertex.h"
#include "../OpenGL/IBO.h"
#include "../OpenGL/Uniform.h"
#include <glm/gtc/matrix_transform.hpp>
namespace YolonaOss {
  void BoxRenderer::load(GL::DrawSpecification* spec)
  {
    _camera = std::make_unique<GL::Camera>("Camera", spec->getCam().get());
    _spec = spec;
    std::vector<GL::PositionNormalVertex> input;
    float start = 0;
    float end = 1;
    //front
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(0, 0, 1)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, start, end) , glm::vec3(0, 0, 1)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, end, end)  , glm::vec3(0, 0, 1)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, end, end) , glm::vec3(0, 0, 1)));

    //right
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, end, end)  , glm::vec3(1, 0, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, end, start) , glm::vec3(1, 0, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(1, 0, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, start, end) , glm::vec3(1, 0, 0)));

    //back
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(0, 0, -1)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, start, start) , glm::vec3(0, 0, -1)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, end, start)  , glm::vec3(0, 0, -1)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, end, start) , glm::vec3(0, 0, -1)));

    //left
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(-1, 0, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, start, end) , glm::vec3(-1, 0, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, end, end)  , glm::vec3(-1, 0, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, end, start) , glm::vec3(-1, 0, 0)));

    //upper
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, end, end)  , glm::vec3(0, 1, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, end, end) , glm::vec3(0, 1, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(0, 1, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, end, start) , glm::vec3(0, 1, 0)));

    //bottom
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(0, -1, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, start, start) , glm::vec3(0, -1, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(end, start, end)  , glm::vec3(0, -1, 0)));
    input.push_back(GL::PositionNormalVertex(glm::vec3(start, start, end) , glm::vec3(0, -1, 0)));

    //note every face of the cube is on a single line
    _indices = std::vector<int>{
      0,  1,  2,  0,  2,  3,   //front
      4,  5,  6,  4,  6,  7,   //right
      8,  9,  10, 8,  10, 11,  //back
      12, 13, 14, 12, 14, 15,  //left
      16, 17, 18, 16, 18, 19,  //upper
      20, 21, 22, 20, 22, 23 }; //bottom

    std::string vertex_shader_source = R"(
      out vec4 clr;
      out vec3 nrm;
      void main() {
      
        mat4 view = CameraProjection *  CameraView;
        gl_Position = view * model *vec4(position , 1.0);
        clr = Color;
        nrm = normal;
      }
   )";

    std::string fragment_shader_source = R"(
     in vec4 clr;
     in vec3 nrm;
     
     out vec4 frag_color;
     void main() {
       float ambientStrength = 0.5;  
       float diffuseStrength = 0.5;
       float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;
     
       vec4 result = clr *  diff + clr * ambientStrength;
       result[3] = 1;
     	frag_color = result;
     }
   )";

    std::vector<GL::Uniform*> uniforms;

    std::vector<GL::Uniform*> cameraUniforms = _camera->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    _ibo = std::make_unique<GL::IBO>(_indices);
    _light = std::make_unique<GL::UniformVec3>("Light");
    _light->setValue(glm::normalize(glm::vec3(25, 31, -21)));
    uniforms.push_back(_light.get());
    _mat = std::make_unique<GL::UniformMat4>("model");
    uniforms.push_back(_mat.get());
    _color = std::make_unique<GL::UniformVec4>("Color");
    uniforms.push_back(_color.get());
    _vbo = std::make_unique<GL::VBO<GL::PositionNormalVertex>>(input);
    _vao = std::make_unique<GL::VAO<GL::PositionNormalVertex>>(_vbo.get());
    _shader = std::make_unique<GL::ShaderProgram>(_vao.get(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void BoxRenderer::start()
  {
    _camera->fromCamera(_spec->getCam().get());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    _shader->bind();
    _camera->bind();
  }

  void BoxRenderer::end()
  {
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);    
  }

  void BoxRenderer::draw(glm::mat4 m, glm::vec4 color) {
    _mat->setValue(m);
    _mat->bind();
    _color->setValue(color);
    _color->bind();
    _ibo->bind(_vao.get());
  }

  void BoxRenderer::drawDot(glm::vec3 start, glm::vec3 size, glm::vec4 color) {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, start);
    m = glm::scale(m, size);
    m = glm::translate(m, glm::vec3(-0.5f, -0.5f, -0.5f));
    draw(m, color);
  }
  void BoxRenderer::drawBox(glm::vec3 start, glm::vec3 size, glm::vec4 color) {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, start);
    m = glm::scale(m, size);
    //m = glm::translate(m, glm::vec3(-0.5f, -0.5f, -0.5f));
    draw(m, color);
  }

  void BoxRenderer::drawLine(glm::vec3 start, glm::vec3 end, float thickness, glm::vec4 color)
  {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, start);

    glm::vec3 dir = glm::normalize(end - start);
    float angle = std::atan2(dir[0], dir[2]);
    m = glm::rotate(m,angle, glm::vec3(0, 1.0, 0));    
    float angleZ = -std::asin(dir[1]);
    m = glm::rotate(m,angleZ, glm::vec3(1.0, 0.0, 0.0));

    m = glm::scale(m, glm::vec3(thickness,thickness,glm::length(end-start)));
    m = glm::translate(m, glm::vec3(-0.5, -0.5, 0));
    draw(m, color);
  }

}