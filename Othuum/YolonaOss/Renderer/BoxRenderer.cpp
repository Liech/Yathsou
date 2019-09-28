#include "BoxRenderer.h"
#include "glad/glad.h"
#include "../OpenGL/Camera.h"
#include "../OpenGL/PositionNormalVertex.h"
#include "../OpenGL/IBO.h"
#include "../OpenGL/ShaderProgram.h"
#include "../OpenGL/Uniform.h"
#include <glm/gtc/matrix_transform.hpp>
namespace YolonaOss {
  void BoxRenderer::load(GL::DrawSpecification* spec)
  {
    _spec = spec;
    std::vector<GL::PositionNormalVertex> input;


    //front
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0, 0, 1)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, -0.5, 0.5) , glm::vec3(0, 0, 1)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, 0.5, 0.5)  , glm::vec3(0, 0, 1)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, 0.5, 0.5) , glm::vec3(0, 0, 1)));

    //right
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, 0.5, 0.5)  , glm::vec3(1, 0, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, 0.5, -0.5) , glm::vec3(1, 0, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, -0.5, -0.5), glm::vec3(1, 0, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, -0.5, 0.5) , glm::vec3(1, 0, 0)));

    //back
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0, 0, -1)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, -0.5, -0.5) , glm::vec3(0, 0, -1)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, 0.5, -0.5)  , glm::vec3(0, 0, -1)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, 0.5, -0.5) , glm::vec3(0, 0, -1)));

    //left
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-1, 0, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, -0.5, 0.5) , glm::vec3(-1, 0, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, 0.5, 0.5)  , glm::vec3(-1, 0, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, 0.5, -0.5) , glm::vec3(-1, 0, 0)));

    //upper
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, 0.5, 0.5)  , glm::vec3(0, 1, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, 0.5, 0.5) , glm::vec3(0, 1, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0, 1, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, 0.5, -0.5) , glm::vec3(0, 1, 0)));

    //bottom
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0, -1, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, -0.5, -0.5) , glm::vec3(0, -1, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(0.5, -0.5, 0.5)  , glm::vec3(0, -1, 0)));
    _cube.push_back(GL::PositionNormalVertex(glm::vec3(-0.5, -0.5, 0.5) , glm::vec3(0, -1, 0)));

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
      
        mat4 view = CameraProjection * CameraView;
        gl_Position = view * Matrix * vec4(position , 1.0);
        clr = Color;
        nrm = normal;
      }
   )";

    std::string fragment_shader_source = R"(
     in vec4 clr;
     in vec3 nrm;
     
     out vec4 frag_color;
     void main() {
       float ambientStrength = 0.7;  
       float diffuseStrength = 0.3;
       float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;
     
       vec4 result = clr *  diff + clr;
       result[3] = 1;
     	frag_color = result;
     }
   )";

    std::vector<GL::Uniform*> uniforms;

    std::vector<GL::Uniform*> cameraUniforms = _spec->getCam()->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    _ibo = std::make_unique<GL::IBO>(_indices);
    _light = std::make_unique<GL::UniformVec3>("Light");
    _light->setValue(glm::normalize(glm::vec3(1, 1, 1)));
    uniforms.push_back(_light.get());
    _mat = std::make_unique<GL::UniformMat4>("Matrix");
    uniforms.push_back(_mat.get());
    _color = std::make_unique<GL::UniformVec4>("Color");
    uniforms.push_back(_color.get());
    _vbo = std::make_unique<GL::VBO<GL::PositionNormalVertex>>(input);
    _vao = std::make_unique<GL::VAO<GL::PositionNormalVertex>>(_vbo.get());
    _shader = std::make_unique<GL::ShaderProgram>(_vao.get(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void BoxRenderer::start()
  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    _shader->bind();
    _spec->getCam()->bind();
  }

  void BoxRenderer::end()
  {
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
  }

  void BoxRenderer::drawBox(glm::vec3 start, glm::vec3 end, glm::vec4 color) {
    glm::mat4 m = glm::mat4(1);
    m = glm::scale(m,end);
    m = glm::translate(m,start);
    _mat->setValue(m);
    _mat->bind();
    _color->setValue(color);
    _color->bind();
    _ibo->bind(_vao.get());
  }

  void BoxRenderer::drawLine(glm::vec3 start, glm::vec3 end, float thickness, glm::vec4 color)
  {
    _ibo->bind(_vao.get());
  }

}