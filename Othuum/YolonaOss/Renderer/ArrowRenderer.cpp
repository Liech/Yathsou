#include "ArrowRenderer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "glad/glad.h"
#include "../OpenGL/PositionNormalVertex.h"
#include "../OpenGL/IBO.h"
#include "../OpenGL/Uniform.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "Util/Geometry.h"

namespace YolonaOss {
  void ArrowRenderer::load(GL::DrawSpecification* spec)
  {
    _camera = std::make_unique<GL::Camera>("Camera", spec->getCam().get());
    _spec = spec;
    std::vector<GL::PositionNormalVertex> input;
    float start = 0;
    float end = 1;

    glm::vec3 a = glm::vec3(0, -1, 0);

    const float stepsize = ((float)M_PI*2.0f) / 8.0f;
    for (float currentAngle = 0; currentAngle < M_PI*2; currentAngle += stepsize) {
      glm::vec3 b = glm::vec3(std::sin(currentAngle), 0, std::cos(currentAngle));
      glm::vec3 c = glm::vec3(std::sin(currentAngle + stepsize), 0, std::cos(currentAngle + stepsize));
      glm::vec3 normal = Geometry::getNormal(a, b, c);

      input.push_back(GL::PositionNormalVertex(a, normal));
      input.push_back(GL::PositionNormalVertex(b, normal));
      input.push_back(GL::PositionNormalVertex(c, normal));

      _indices.push_back((int)(input.size() - 3));
      _indices.push_back((int)(input.size() - 2));
      _indices.push_back((int)(input.size() - 1));
    }

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
    _shader = std::make_unique<GL::ShaderProgram>(GL::PositionNormalVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void ArrowRenderer::start()
  {
    _camera->fromCamera(_spec->getCam().get());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    _shader->bind();
    _camera->bind();
  }

  void ArrowRenderer::end()
  {
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);    
  }

  void ArrowRenderer::draw(glm::mat4 m, glm::vec4 color) {
    _mat->setValue(m);
    _mat->bind();
    _color->setValue(color);
    _color->bind();
    _ibo->bind(_vao.get());
  }

  void ArrowRenderer::drawArrow(glm::vec3 start, glm::vec3 dir, float size, glm::vec4 color) {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, start);

    glm::vec3 cross = glm::cross(dir, glm::vec3(0,1,0));
    m = glm::rotate(m, Geometry::getAngle(glm::vec3(0,1,0),dir), cross);

    m = glm::scale(m, glm::vec3(size*0.3f,size,size*0.3f));
    m = glm::translate(m, glm::vec3(-0.5f, -0.5f, -0.5f));
    //m = glm::lookAt(start, start + dir, glm::vec3(0, 1, 0));
    //m = glm::scale(m, glm::vec3(0.5f,0.5f,0.5f));
    draw(m, color);
  }

}