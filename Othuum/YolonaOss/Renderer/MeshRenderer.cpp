#include "MeshRenderer.h"

#include "../OpenGL/Uniform.h"
#include "../OpenGL/Camera.h"
#include "../OpenGL/ShaderProgram.h"
#include "glad/glad.h"
#include "../OpenGL/PositionNormalVertex.h"
#include "../OpenGL/IBO.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/VAO.h"

namespace YolonaOss
{
  struct MeshPimpl
  {
  public:
    std::unique_ptr<GL::VBO<GL::PositionNormalVertex>>        vbo;
    std::unique_ptr<GL::VAO<GL::PositionNormalVertex>>        vao;
    std::unique_ptr<GL::IBO>                                  ibo;
  };

  Mesh::Mesh(const std::vector<GL::PositionNormalVertex>& vertecies, const std::vector<int>& indicies) :
    _p(std::make_unique<MeshPimpl>())
  {
    _p->ibo = std::make_unique<GL::IBO>(indicies);    
    _p->vbo = std::make_unique<GL::VBO<GL::PositionNormalVertex>>(vertecies);
    _p->vao = std::make_unique<GL::VAO<GL::PositionNormalVertex>>(_p->vbo.get());
  }

  void Mesh::draw() const
  {
    _p->ibo->bind(_p->vao.get());
  }

  void MeshRenderer::load(GL::DrawSpecification* spec)
  {
    _camera = std::make_unique<GL::Camera>("Camera", spec->getCam().get());
    _spec = spec;

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
    _light = std::make_unique<GL::UniformVec3>("Light");
    _light->setValue(glm::normalize(glm::vec3(25, 31, -21)));
    uniforms.push_back(_light.get());
    _mat = std::make_unique<GL::UniformMat4>("model");
    uniforms.push_back(_mat.get());
    _color = std::make_unique<GL::UniformVec4>("Color");
    uniforms.push_back(_color.get());
    _shader = std::make_unique<GL::ShaderProgram>(GL::PositionNormalVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }    

  void MeshRenderer::draw(const Mesh& mesh, glm::mat4 transformation, glm::vec4 color)
  {
    _mat->setValue(transformation);
    _mat->bind();
    _color->setValue(color);
    _color->bind();
    mesh.draw();
  }

  void MeshRenderer::start()
  {
    _camera->fromCamera(_spec->getCam().get());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    _shader->bind();
    _camera->bind();
  }

  void MeshRenderer::end()
  {
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }
}