#include "SupComModelRenderer.h"

#include "../OpenGL/Uniform.h"
#include "../OpenGL/Camera.h"
#include "../OpenGL/ShaderProgram.h"
#include "glad/glad.h"
#include "../OpenGL/PositionNormalTextureVertex.h"
#include "../OpenGL/IBO.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/Texture.h"

namespace YolonaOss
{
  class MeshPimpl
  {
  public:
    std::unique_ptr<GL::VBO<GL::PositionNormalTextureVertex>> vbo;
    std::unique_ptr<GL::VAO<GL::PositionNormalTextureVertex>> vao;
    std::unique_ptr<GL::IBO>                           ibo;
    std::shared_ptr<GL::Texture>                       albedo = std::shared_ptr<GL::Texture>();
    std::shared_ptr<GL::Texture>                       team   = std::shared_ptr<GL::Texture>();
    std::shared_ptr<GL::Texture>                       normal = std::shared_ptr<GL::Texture>();
  };

  SupComGLMesh::SupComGLMesh(const std::vector<GL::PositionNormalTextureVertex>& vertecies, const std::vector<int>& indicies) :
    _p(std::make_unique<MeshPimpl>())
  {
    _p->ibo = std::make_unique<GL::IBO>(indicies);    
    _p->vbo = std::make_unique<GL::VBO<GL::PositionNormalTextureVertex>>(vertecies);
    _p->vao = std::make_unique<GL::VAO<GL::PositionNormalTextureVertex>>(_p->vbo.get());
  }

  void SupComGLMesh::setAlbedo(std::shared_ptr<GL::Texture>& texture)
  {
    _p->albedo = texture;
  }

  void SupComGLMesh::setTeam(std::shared_ptr<GL::Texture> texture)
  {
    _p->team = texture;
  }

  void SupComGLMesh::setNormal(std::shared_ptr<GL::Texture> texture)
  {
    _p->normal = texture;
  }

  void SupComGLMesh::draw() const
  {
    _p->ibo->bind(_p->vao.get());
  }
  int SupComGLMesh::getAlbedoID() const { return _p->albedo->getTextureID(); }
  int SupComGLMesh::getTeamID()   const { return _p->team  ->getTextureID(); }
  int SupComGLMesh::getNormalID() const { return _p->normal->getTextureID(); }

  void SupComModelRenderer::load(GL::DrawSpecification* spec)
  {
    _camera = std::make_unique<GL::Camera>("Camera", spec->getCam().get());
    _spec = spec;

    std::string vertex_shader_source = R"(
      out vec3 nrm;
      out vec2 TexCoords;

      void main() {
      
        mat4 view = CameraProjection *  CameraView;
        gl_Position = view * model *vec4(position , 1.0);
        nrm = normal;
        TexCoords = texCoord;
      }
   )";

    std::string fragment_shader_source = R"(
     in vec3 nrm;
     in vec2 TexCoords;
     
     out vec4 frag_color;
     void main() {
       float ambientStrength = 0.5;  
       float diffuseStrength = 0.5;
       //vec4 normal = texture(Normal, TexCoords);
       float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;
       
       vec4 albedo = texture(Albedo, TexCoords);
     
       vec4 result = albedo *  diff + albedo * ambientStrength;
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
    _albedo = std::make_unique<GL::Texture>("Albedo", 0);
    _albedo->release();
    uniforms.push_back(_albedo.get());
    _team = std::make_unique<GL::Texture>("Team", 0);
    _team->release();
    uniforms.push_back(_team.get());
    _normal = std::make_unique<GL::Texture>("Normal", 0);
    _normal->release();
    uniforms.push_back(_normal.get());
    _shader = std::make_unique<GL::ShaderProgram>(GL::PositionNormalTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }    

  void SupComModelRenderer::draw(const SupComGLMesh& mesh, glm::mat4 transformation)
  {
    _mat->setValue(transformation);
    _mat->bind();
    _albedo->setTextureID(mesh.getAlbedoID());
    _team  ->setTextureID(mesh.getTeamID  ());
    _normal->setTextureID(mesh.getNormalID());
    mesh.draw();
  }

  void SupComModelRenderer::start()
  {
    _camera->fromCamera(_spec->getCam().get());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    _shader->bind();
    _camera->bind();
  }

  void SupComModelRenderer::end()
  {
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }
}