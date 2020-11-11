#include "SupComModelRenderer.h"

#include "../OpenGL/Uniform.h"
#include "../OpenGL/Camera.h"
#include "../OpenGL/ShaderProgram.h"
#include "glad/glad.h"
#include "../OpenGL/SupComVertex.h"
#include "../OpenGL/IBO.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/Texture.h"

namespace YolonaOss
{
  class MeshPimpl
  {
  public:
    std::unique_ptr<GL::VBO<GL::SupComVertex>> vbo;
    std::unique_ptr<GL::VAO<GL::SupComVertex>> vao;
    std::unique_ptr<GL::IBO>                   ibo;
    std::shared_ptr<GL::Texture>               albedo = std::shared_ptr<GL::Texture>();
    std::shared_ptr<GL::Texture>               info   = std::shared_ptr<GL::Texture>();
    std::shared_ptr<GL::Texture>               normal = std::shared_ptr<GL::Texture>();
  };

  SupComGLMesh::SupComGLMesh(const std::vector<GL::SupComVertex>& vertecies, const std::vector<int>& indicies) :
    _p(std::make_unique<MeshPimpl>())
  {
    _p->ibo = std::make_unique<GL::IBO>(indicies);    
    _p->vbo = std::make_unique<GL::VBO<GL::SupComVertex>>(vertecies);
    _p->vao = std::make_unique<GL::VAO<GL::SupComVertex>>(_p->vbo.get());
  }

  void SupComGLMesh::setAlbedo(std::shared_ptr<GL::Texture>& texture)
  {
    _p->albedo = texture;
  }

  void SupComGLMesh::setInfo(std::shared_ptr<GL::Texture> texture)
  {
    _p->info = texture;
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
  int SupComGLMesh::getInfoID()   const { return _p->info  ->getTextureID(); }
  int SupComGLMesh::getNormalID() const { return _p->normal->getTextureID(); }

  void SupComModelRenderer::load(GL::DrawSpecification* spec)
  {
    _camera = std::make_unique<GL::Camera>("Camera", spec->getCam().get());
    _spec = spec;

    
    _anim.resize(maxBoneNumber);
    for (int i = 0; i < maxBoneNumber; i++)
      _anim[i] = glm::mat4(1.0);

    std::string vertex_shader_source = R"(
      out vec3 nrm;
      out vec2 UV1;
      out vec2 UV2;
      out vec4 boneMarker;

      void main() {      
        mat4 view = CameraProjection *  CameraView;
        gl_Position = view * model * mat4(animation[bones]) * vec4(position , 1.0);
        nrm = normal;
        UV1 = uv1;
        UV2 = uv2;
        boneMarker = vec4(0,0,0,0);//vec4(mod((bones * 6662177),100)/100.0,mod((bones * 7804957 ),100)/100.0,mod((bones * 9999943),100)/100.0,0);
      }
   )";

    //https://forums.faforever.com/viewtopic.php?f=41&t=14527
    /*
    albedo rgb = base colour + lighting data
    albedo a = something. it might be nothing. i forgot.
    normal map rgb (yes) = y vector
    normal map a = x vector
    spec team r = specular
    spec team g = reflection
    spec team b = glow/bloom
    spec team a = team colour (replaces albedo with a faction colour)
    */
    std::string fragment_shader_source = R"(
     in vec3 nrm;
     in vec2 UV1;
     in vec2 UV2;
     in vec4 boneMarker;
     
     out vec4 frag_color;
     void main() {
       float ambientStrength = 0.5;  
       float diffuseStrength = 0.5;
       //vec4 normal = texture(Normal, TexCoords);
       float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;
       
       vec4 albedo = texture(Albedo, UV1);
       vec4 info   = texture(Info  , UV1);
       float specular   = info[0];
       float reflection = info[1];
       float glow       = info[2];
       float showTeamClr= info[3];
       
       //team;//albedo * diff + albedo * ambientStrength + team +
       vec4 result = albedo + showTeamClr * (clr - albedo) + boneMarker;
       //result[3] = 1;
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
    _color = std::make_unique<GL::UniformVec4>("clr");
    uniforms.push_back(_color.get());
    _animation = std::make_unique<GL::UniformVecMat4>("animation", maxBoneNumber);
    _animation->setValue(_anim);
    uniforms.push_back(_animation.get());
    _albedo = std::make_unique<GL::Texture>("Albedo", 0);
    _albedo->release();
    uniforms.push_back(_albedo.get());
    _info = std::make_unique<GL::Texture>("Info", 1);
    _info->release();
    uniforms.push_back(_info.get());
    _normal = std::make_unique<GL::Texture>("Normal", 2);
    _normal->release();
    uniforms.push_back(_normal.get());
    _shader = std::make_unique<GL::ShaderProgram>(GL::SupComVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }    

  void SupComModelRenderer::draw(const SupComGLMesh& mesh, glm::mat4 transformation, const std::vector<glm::mat4>& animation)
  {
    if (animation.size() == 0)
    {
      std::vector<glm::mat4> anim;
      anim.resize(maxBoneNumber);
      for (int i = 0; i < maxBoneNumber; i++)
        anim[i] = glm::mat4(1.0);

      _animation->setValue(anim);
    }
    else
      _animation->setValue(animation);
    _albedo->setTextureID(mesh.getAlbedoID());
    _info  ->setTextureID(mesh.getInfoID  ());
    _normal->setTextureID(mesh.getNormalID());
    _shader->bind();
    _camera->bind();
    _color->setValue(glm::vec4(0, 1, 0, 1));
    _mat->setValue(transformation);
    mesh.draw();
  }

  void SupComModelRenderer::start()
  {
    _camera->fromCamera(_spec->getCam().get());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  }

  void SupComModelRenderer::end()
  {
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }
}