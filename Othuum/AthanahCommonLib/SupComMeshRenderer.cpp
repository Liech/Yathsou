#include "SupComMeshRenderer.h"

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

#include "SupComModel.h"

namespace Athanah {
  SupComMeshRenderer::SupComMeshRenderer(std::shared_ptr<Ahwassa::Camera> camera) {
    _camera = camera;
    _bufferSize = 10;
    _lightDirection = glm::normalize(glm::vec3(25, 31, -21));
    makeShader();
  }

  SupComMeshRenderer::~SupComMeshRenderer() {

  }


  void SupComMeshRenderer::setLightDirection(glm::vec3 dir) {
    _lightDirection = dir;
  }

  glm::vec3 SupComMeshRenderer::getLightDirection() {
    return _lightDirection;
  }

  void SupComMeshRenderer::addMesh(std::shared_ptr<SupComMesh> mesh) {
    _meshes[mesh->model].push_back(mesh);
  }

  void SupComMeshRenderer::makeShader() {
    std::string vertex_shader_source = R"(
      out vec3 clr;
      out vec3 nrm;
      out vec2 UV1;

      void main() {
        uint boneSize =)" + std::to_string(_maxBoneSize) + R"( ;
        mat4 view = )" + _camera->getName() + R"(Projection *  )" + _camera->getName() + R"(View;
        gl_Position = view *  models[gl_InstanceID] * vec4(position , 1.0);
        clr = colors[gl_InstanceID];
        nrm = normal;
        UV1 = uv1;
      }
   )";

    std::string fragment_shader_source = R"(
     in vec3 clr;
     in vec3 nrm;
     in vec2 UV1;
     
     out vec4 frag_color;
     void main() {

       vec4 albedo = texture(Albedo, UV1);
       vec4 info   = texture(Info  , UV1);
       float specular   = info[0];
       float reflection = info[1];
       float glow       = info[2];
       float showTeamClr= info[3];
       float ambientStrength = 0.5;  
       float diffuseStrength = 0.5;
       float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;

       vec4 unlightColor = albedo + showTeamClr * (vec4(clr,1) - albedo);

       vec4 result = unlightColor *  diff + unlightColor * ambientStrength;
       result[3] = 1;
     	frag_color = result;
     }
   )";
    std::vector<Ahwassa::Uniform*> uniforms;

    std::vector<Ahwassa::Uniform*> cameraUniforms = _camera->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    _light = std::make_unique<Ahwassa::UniformVec3>("Light");

    std::vector<glm::mat4> modelContent;
    modelContent.resize(_bufferSize);
    for (size_t i = 0; i < _bufferSize; i++)
      modelContent[i] = glm::mat4(1);

    std::vector<glm::vec3> colorContent;
    colorContent.resize(_bufferSize);
    for (size_t i = 0; i < _bufferSize; i++)
      colorContent[i] = glm::vec3(0,1,0);

    _models = std::make_shared<Ahwassa::SSBOmat4>("models", modelContent);
    _colors = std::make_shared<Ahwassa::SSBOvec3>("colors", colorContent);
    _light->setValue(glm::normalize(glm::vec3(0)));
    uniforms.push_back(_light.get());
    uniforms.push_back(_models.get());
    uniforms.push_back(_colors.get());

    //_animations = std::make_unique<Ahwassa::InstancedVecMat4>("animation", _maxBoneSize* _bufferSize);
    //uniforms.push_back(_animations.get());

    _albedo = std::make_unique<Ahwassa::Texture>("Albedo", 0);
    _albedo->release();
    uniforms.push_back(_albedo.get());

    _info = std::make_unique<Ahwassa::Texture>("Info", 0);
    _info->release();
    uniforms.push_back(_info.get());

    _shader = std::make_unique<Ahwassa::ShaderProgram>(SupComVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void SupComMeshRenderer::draw() {
    std::vector< std::shared_ptr<SupComModel>> toDeleteMeshes;

    Ahwassa::Util::setDepthTest(true);
    Ahwassa::Util::setDepthFuncLess();
    Ahwassa::Util::depthMask(true);
    _shader->bind();
    _camera->bind();

    for (auto& meshVector : _meshes) {
      std::vector<glm::mat4> models;
      std::vector<glm::vec3> colors;
      std::vector<glm::mat4> anim;
      models.resize(_bufferSize);

      for (size_t i = 0; i < models.size(); i++)
        models[i] = glm::mat4(1.0);

      colors.resize(_bufferSize);
      anim.resize(_bufferSize * _maxBoneSize);

      std::vector<size_t> toDelete;

      size_t currentPosition = 0;
      for (size_t i = 0; i < meshVector.second.size(); i++) {
        auto m = meshVector.second[i].lock();
        if (!m)
        {
          toDelete.push_back(i);
          continue;
        }
        models[currentPosition] = m->transformation;
        colors[currentPosition] = m->teamColor.to3();
        if (m->animation.size() > _maxBoneSize)
          throw std::runtime_error("Too many bones");
        for (size_t a = 0; a < m->animation.size(); a++)
          anim[i * _maxBoneSize + a] = m->animation[a];
        for (size_t a = m->animation.size() - 1; a < _maxBoneSize; a++)
          anim[i * _maxBoneSize + a] = glm::mat4(1.0);
        currentPosition++;
      }

      _albedo->setTextureID(meshVector.first->albedo().getTextureID());
      _info->setTextureID(meshVector.first->info().getTextureID());
      _light->setValue(getLightDirection());
      //_models->setValue(models);
      //_colors->setValue(colors);
      //_animations->setValue(anim);
      _models->bind();
      _colors->bind();
      //_animations->bind();
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