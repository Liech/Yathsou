#include "SphereRenderer.h"
#include "glad/glad.h"
#include "../OpenGL/PositionNormalVertex.h"
#include "../OpenGL/IBO.h"
#include "../OpenGL/Uniform.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>


namespace YolonaOss {
  void SphereRenderer::load(GL::DrawSpecification* spec)
  {
    _camera = std::make_unique<GL::Camera>("Camera", spec->getCam().get());
    _spec = spec;
    std::vector<GL::PositionNormalVertex> input = genSphere();
    


    //note every face of the cube is on a single line
    _indices.clear();
    for (size_t i = 0; i < input.size(); i++)
      _indices.push_back(i);
    
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

  void SphereRenderer::start()
  {
    _camera->fromCamera(_spec->getCam().get());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    _shader->bind();
    _camera->bind();
  }

  void SphereRenderer::end()
  {
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);    
  }

  void SphereRenderer::draw(glm::mat4 m, glm::vec4 color) {
    _mat->setValue(m);
    _mat->bind();
    _color->setValue(color);
    _color->bind();
    _ibo->bind(_vao.get());
  }

  void SphereRenderer::drawDot(glm::vec3 start, glm::vec3 size, glm::vec4 color) {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, start);
    m = glm::scale(m, size);
    m = glm::translate(m, glm::vec3(-0.5f, -0.5f, -0.5f));
    //m = glm::scale(m, glm::vec3(0.5f,0.5f,0.5f));
    draw(m, color);
  }

  void SphereRenderer::drawSphere(glm::vec3 start, glm::vec3 size, glm::vec4 color) {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, start);
    m = glm::scale(m, size);
    //m = glm::translate(m, glm::vec3(-0.5f, -0.5f, -0.5f));
    draw(m, color);
  }

  void SphereRenderer::drawLine(glm::vec3 start, glm::vec3 end, float thickness, glm::vec4 color)
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

  //https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere
  std::vector<GL::PositionNormalVertex> SphereRenderer::genSphere()
  {
    std::vector<GL::PositionNormalVertex> result;
    int uResolution = 15;
    int vResolution = 15;
    float r = 1;
    auto F = [](float u, float v, float r) {return glm::vec3(cos(u) * sin(v) * r, cos(v)* r, sin(u)* sin(v)* r); };
    auto triangle = [](glm::vec3 a, glm::vec3 b, glm::vec3 c) {};
    float startU = 0;
    float startV = 0;
    float endU = M_PI * 2;
    float endV = M_PI;
    float stepU = (endU - startU) / uResolution; // step size between U-points on the grid
    float stepV = (endV - startV) / vResolution; // step size between V-points on the grid
    for (int i = 0; i < uResolution; i++) { // U-points
     for (int j = 0; j < vResolution; j++) { // V-points
       float u = i * stepU + startU;
       float v = j * stepV + startV;
       float un = (i + 1 == uResolution) ? endU : (i + 1) * stepU + startU;
       float vn = (j + 1 == vResolution) ? endV : (j + 1) * stepV + startV;
       // Find the four points of the grid
       // square by evaluating the parametric
       // surface function
       glm::vec3 p0 = F(u, v  , r);
       glm::vec3 p1 = F(u, vn , r);
       glm::vec3 p2 = F(un, v , r);
       glm::vec3 p3 = F(un, vn, r);
       // NOTE: For spheres, the normal is just the normalized
       // version of each vertex point; this generally won't be the case for
       // other parametric surfaces.
       // Output the first triangle of this grid square
       glm::vec3 offset(0,0,0);
       result.push_back(GL::PositionNormalVertex(p0 + offset, -glm::cross(p0- p2, p1)));
       result.push_back(GL::PositionNormalVertex(p2 + offset, -glm::cross(p0- p2, p1)));
       result.push_back(GL::PositionNormalVertex(p1 + offset, -glm::cross(p0- p2, p1)));
       result.push_back(GL::PositionNormalVertex(p3 + offset,  glm::cross(p3- p1, p2)));
       result.push_back(GL::PositionNormalVertex(p1 + offset,  glm::cross(p3- p1, p2)));
       result.push_back(GL::PositionNormalVertex(p2 + offset,  glm::cross(p3- p1, p2)));
     }
    }
    return result;
  }
}