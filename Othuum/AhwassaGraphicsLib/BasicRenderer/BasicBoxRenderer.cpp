#include "BasicBoxRenderer.h"

#include <vector>

#include "glad/glad.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/BaseTypes/Color.h"

#include "Vertex/PositionNormalVertex.h"
#include "Uniforms/UniformMat4.h"
#include "Uniforms/UniformVec3.h"
#include "Uniforms/UniformVec4.h"
#include "BufferObjects/VBO.h"
#include "BufferObjects/VAO.h"
#include "BufferObjects/IBO.h"
#include "Core/ShaderProgram.h"
#include "Core/Camera.h"

namespace Ahwassa {
  struct BasicBoxRenderer::RenderVars {
    std::vector<int>                           _indices;
    std::unique_ptr<UniformMat4>               _mat;
    std::unique_ptr<UniformVec4>               _color;
    std::unique_ptr<VBO<PositionNormalVertex>> _vbo;
    std::unique_ptr<VAO<PositionNormalVertex>> _vao;
    std::unique_ptr<IBO>                       _ibo;
    std::unique_ptr<ShaderProgram>             _shader;
    std::unique_ptr<UniformVec3>               _light;
    std::shared_ptr<Camera>                    _camera;
  };

  BasicBoxRenderer::BasicBoxRenderer(std::shared_ptr<Camera> camera){
    _vars = std::make_shared<RenderVars>();
    _vars->_camera = camera;
    std::vector<PositionNormalVertex> input;
    float start = 0;
    float end = 1;
    //front
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end) , glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end)  , glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end) , glm::vec3(0, 0, 1)));

    //right
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end)  , glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start) , glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end) , glm::vec3(1, 0, 0)));

    //back
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start) , glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start)  , glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start) , glm::vec3(0, 0, -1)));

    //left
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end) , glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end)  , glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start) , glm::vec3(-1, 0, 0)));

    //upper
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end)  , glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end) , glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start) , glm::vec3(0, 1, 0)));

    //bottom
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start) , glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end)  , glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end) , glm::vec3(0, -1, 0)));

    //note every face of the cube is on a single line
    _vars->_indices = std::vector<int>{
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
      
        mat4 view = )"+_vars->_camera->getName()+R"(Projection *  )" + _vars->_camera->getName() + R"(View;
        gl_Position = view * model * vec4(position , 1.0);
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

    std::vector<Uniform*> uniforms;

    std::vector<Uniform*> cameraUniforms = _vars->_camera->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    _vars->_ibo = std::make_unique<IBO>(_vars->_indices);
    _vars->_light = std::make_unique<UniformVec3>("Light");
    _vars->_light->setValue(glm::normalize(glm::vec3(25, 31, -21)));
    uniforms.push_back(_vars->_light.get());
    _vars->_mat = std::make_unique<UniformMat4>("model");
    uniforms.push_back(_vars->_mat.get());
    _vars->_color = std::make_unique<UniformVec4>("Color");
    uniforms.push_back(_vars->_color.get());
    _vars->_vbo = std::make_unique<VBO<PositionNormalVertex>>(input);
    _vars->_vao = std::make_unique<VAO<PositionNormalVertex>>(_vars->_vbo.get());
    _vars->_shader = std::make_unique<ShaderProgram>(PositionNormalVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void BasicBoxRenderer::start()
  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    _vars->_shader->bind();
    _vars->_camera->bind();
  }

  void BasicBoxRenderer::end()
  {
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);    
  }

  void BasicBoxRenderer::draw(glm::mat4 m, Iyathuum::Color color) {
    _vars->_mat->setValue(m);
    _vars->_mat->bind();
    _vars->_color->setValue(color.to4());
    _vars->_color->bind();
    _vars->_ibo->draw(_vars->_vao.get());
  }

  void BasicBoxRenderer::drawDot(glm::vec3 start, glm::vec3 size, Iyathuum::Color color) {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, start);
    m = glm::scale(m, size);
    m = glm::translate(m, glm::vec3(-0.5f, -0.5f, -0.5f));
    draw(m, color);
  }

  void BasicBoxRenderer::drawBox(glm::vec3 start, glm::vec3 size, Iyathuum::Color color) {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, start);
    m = glm::scale(m, size);
    draw(m, color);
  }

  void BasicBoxRenderer::drawLine(glm::vec3 start, glm::vec3 end, float thickness, Iyathuum::Color color)
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