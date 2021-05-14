#include "SupCom/SupComMeshRendererDef.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/SSBOmat4.h"
#include "AhwassaGraphicsLib/Uniforms/SSBOvec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecVec3.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/BufferObjects/FBO.h"

#include "SupCom/SupComModel.h"

namespace Athanah {
  SupComMeshRendererDef::SupComMeshRendererDef(std::shared_ptr<Ahwassa::Camera> camera) {
    _camera = camera;
    _bufferSize = 5000;
    _lightDirection = glm::normalize(glm::vec3(25, 31, -21));
    makeShader();
  }

  SupComMeshRendererDef::~SupComMeshRendererDef() {

  }

  void SupComMeshRendererDef::addMesh(std::shared_ptr<SupComMesh> mesh) {
    _meshes[mesh->model].push_back(mesh);
  }

  void SupComMeshRendererDef::makeShader() {
    std::string vertex_shader_source = R"(
      out vec2 TexCoords;
      out vec3 FragPos;
      out vec3 Normal;
      out vec3 clr;
      out vec3 Tangent;
      out vec3 Bitangent;

      void main() {
        int boneSize =)" + std::to_string(_maxBoneSize) + R"( ;
        mat4 view = )" + _camera->getName() + R"(Projection *  )" + _camera->getName() + R"(View;
        mat4 world = models[gl_InstanceID] * animations[gl_InstanceID*boneSize+int(bone)];
        gl_Position = view * world * vec4(position , 1.0);
        
        world[3] = vec4(0, 0, 0, 1); //cancel translation
        clr       = colors[gl_InstanceID];
        Normal    = (modelsRot[gl_InstanceID] * vec4(normal, 1.0)).xyz;
        TexCoords = uv1;
        FragPos   = (world * vec4(position , 1.0)).xyz;
        
        Tangent   = vec3(modelsRot[gl_InstanceID]*vec4(tangent ,1));
        Bitangent = vec3(modelsRot[gl_InstanceID]*vec4(binormal,1));
      }
   )";

    std::string fragment_shader_source = R"(
     layout (location = 0) out vec4 gPosition;
     layout (location = 1) out vec4 gNormal;
     layout (location = 2) out vec4 gAlbedoSpec;
     layout (location = 3) out vec4 gSpecial;

     in vec2 TexCoords;
     in vec3 FragPos;
     in vec3 Normal;
     in vec3 clr;
     in vec3 Tangent;
     in vec3 Bitangent;
     
     void main() {
       vec4  albedo = texture(Albedo   , TexCoords);
       vec4  info   = texture(Info     , TexCoords);
       vec4  normMap= texture(NormalMap, TexCoords) * 2 - 1;
       float specular   = info[0];
       float reflection = info[1];
       float glow       = info[2];
       float showTeamClr= info[3]; 

       vec4 normalWithNormalMap = vec4(Bitangent * normMap.z + Tangent * normMap.y + Normal,1);

       gAlbedoSpec.rgb = (albedo + showTeamClr * (vec4(clr,1) - albedo)).rgb;
       gAlbedoSpec.a = 1;
       gNormal.rgb = (normalize(normalWithNormalMap).rgb /2.0 + vec3(0.5,0.5,0.5)); 
       gNormal.a = 1;
       gPosition.rgb = FragPos.rgb; 	
       gPosition.a = 1;
       gSpecial.r = reflection;
       gSpecial.g = glow;
       gSpecial.b = specular;
       gSpecial.a = 1;
     }
   )";
    std::vector<Ahwassa::Uniform*> uniforms;

    std::vector<Ahwassa::Uniform*> cameraUniforms = _camera->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    
    _models     = std::make_shared<Ahwassa::SSBOmat4>("models", _bufferSize);
    _modelsRot  = std::make_shared<Ahwassa::SSBOmat4>("modelsRot", _bufferSize);
    _colors     = std::make_shared<Ahwassa::SSBOvec3>("colors", _bufferSize);
    _animations = std::make_shared<Ahwassa::SSBOmat4>("animations", _bufferSize* _maxBoneSize);
    uniforms.push_back(_models.get());
    uniforms.push_back(_modelsRot.get());
    uniforms.push_back(_colors.get());
    uniforms.push_back(_animations.get());

    _albedo = std::make_unique<Ahwassa::Texture>("Albedo", 0);
    _albedo->release();
    uniforms.push_back(_albedo.get());

    _normal = std::make_unique<Ahwassa::Texture>("NormalMap", 0);
    _normal->release();
    uniforms.push_back(_normal.get());

    _info = std::make_unique<Ahwassa::Texture>("Info", 0);
    _info->release();
    uniforms.push_back(_info.get());

    _shader = std::make_unique<Ahwassa::ShaderProgram>(SupComVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  glm::mat4 removeTranslation(const glm::mat4& input) {
    double dArray[16] = { 0.0 };

    const float* pSource = (const float*)glm::value_ptr(input);
    for (int i = 0; i < 12; ++i)
      dArray[i] = pSource[i];
    dArray[15] = 1;
    return glm::make_mat4(dArray);
  }

  void SupComMeshRendererDef::draw() {
    std::vector< std::shared_ptr<SupComModel>> toDeleteMeshes;

    Ahwassa::Util::setDepthTest(true);
    Ahwassa::Util::setDepthFuncLess();
    Ahwassa::Util::depthMask(true);
    _shader->bind();
    _camera->bind();

    for (auto& meshVector : _meshes) {
      std::vector<glm::mat4> models;
      std::vector<glm::mat4> modelsRot;
      std::vector<glm::vec3> colors;
      std::vector<glm::mat4> anim;
      models   .resize(_bufferSize);
      modelsRot.resize(_bufferSize);
      colors   .resize(_bufferSize);
      anim     .resize(_bufferSize * _maxBoneSize);

      std::vector<size_t> toDelete;

      size_t currentPosition = 0;
      for (size_t i = 0; i < meshVector.second.size(); i++) {
        auto m = meshVector.second[i].lock();
        if (!m)
        {
          toDelete.push_back(i);
          continue;
        }
        models   [currentPosition] = m->transformation;
        modelsRot[currentPosition] = removeTranslation(m->transformation);
        colors[currentPosition] = m->teamColor.to3();
        if (m->animation.size() > _maxBoneSize)
          throw std::runtime_error("Too many bones");
        for (size_t a = 0; a < m->animation.size(); a++)
          anim[i * _maxBoneSize + a] = m->animation[a];
        for (size_t a = m->animation.size(); a < _maxBoneSize; a++)
          anim[i * _maxBoneSize + a] = glm::mat4(1.0);
        currentPosition++;
      }

      _albedo->setTextureID(meshVector.first->albedo().getTextureID());
      _normal->setTextureID(meshVector.first->normal().getTextureID());
      _info->setTextureID(meshVector.first->info().getTextureID());
      _models->setData(models);
      _modelsRot->setData(modelsRot);
      _colors->setData(colors);
      _animations->setData(anim);
      _models->bind();
      _modelsRot->bind();
      _colors->bind();
      _animations->bind();
      meshVector.first->mesh().drawInstanced(currentPosition);

      for (int i = toDelete.size() - 1; i >= 0; i--)
        meshVector.second.erase(meshVector.second.begin() + i);
      if (meshVector.second.size() == 0)
        toDeleteMeshes.push_back(meshVector.first);

      Ahwassa::Util::setDepthTest(false);
    }

    for (auto x : toDeleteMeshes) {
      _meshes.erase(x);
    }
  }
}