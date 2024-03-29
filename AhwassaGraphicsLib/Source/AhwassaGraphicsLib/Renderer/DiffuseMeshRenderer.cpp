#include "DiffuseMeshRenderer.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecMat4.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecVec3.h"

namespace Ahwassa {
  DiffuseMeshRenderer::DiffuseMeshRenderer(std::shared_ptr<Camera> camera) {
    _camera = camera;
    _bufferSize = (Util::maxUniformAmount() - 10) / 2;
    _lightDirection = glm::normalize(glm::vec3(25, 31, -21));
    makeShader();
  }

  DiffuseMeshRenderer::~DiffuseMeshRenderer() {

  }


  void DiffuseMeshRenderer::setLightDirection(const glm::vec3& dir) {
    _lightDirection = dir;
  }

  glm::vec3 DiffuseMeshRenderer::getLightDirection() const {
    return _lightDirection;
  }

  void DiffuseMeshRenderer::addMesh(std::shared_ptr<DiffuseMeshRendererMesh> mesh) {
    _meshes[mesh->mesh].push_back(mesh);
  }

  void DiffuseMeshRenderer::makeShader() {
    std::string vertex_shader_source = R"(
      out vec3 clr;
      out vec3 nrm;
      void main() {
      
        mat4 view = )" + _camera->getName() + R"(Projection *  )" + _camera->getName() + R"(View;
        gl_Position = view *  models[gl_InstanceID] *vec4(position , 1.0);
        clr = colors[gl_InstanceID];
        nrm = normal;
      }
   )";

    std::string fragment_shader_source = R"(
     in vec3 clr;
     in vec3 nrm;
     
     out vec4 frag_color;
     void main() {
       float ambientStrength = 0.5;  
       float diffuseStrength = 0.5;
       float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;
     
       vec4 result = vec4(clr,1) *  diff + vec4(clr,1) * ambientStrength;
       result[3] = 1;
     	frag_color = result;
     }
   )";
    std::vector<Uniform*> uniforms;

    std::vector<Uniform*> cameraUniforms = _camera->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    _light = std::make_unique<UniformVec3>("Light");
    _models = std::make_unique<UniformVecMat4>("models", _bufferSize);
    _colors = std::make_unique<UniformVecVec3>("colors", _bufferSize);
    _light->setValue(glm::normalize(glm::vec3(0)));
    uniforms.push_back(_light .get());
    uniforms.push_back(_models.get());
    uniforms.push_back(_colors.get());
    _shader = std::make_unique<ShaderProgram>(PositionNormalVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void DiffuseMeshRenderer::draw() {
    std::vector< std::shared_ptr<Mesh<PositionNormalVertex>>> toDeleteMeshes;

    Util::setDepthTest(true); 
    Util::setDepthFuncLess();
    _shader->bind();
    _camera->bind();

    for (auto& meshVector : _meshes) {
      std::vector<glm::mat4> models;
      std::vector<glm::vec3> colors;
      models.resize(_bufferSize);
      colors.resize(_bufferSize);

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
        colors[currentPosition] = m->color.to3();
        currentPosition++;
      }

      _light ->setValue(getLightDirection());
      _models->setValue(models);
      _colors->setValue(colors);
      _models->bind();
      _colors->bind();
      meshVector.first->drawInstanced(currentPosition);

      for (int i = toDelete.size()-1; i >= 0; i--)
        meshVector.second.erase(meshVector.second.begin() + i);
      if (meshVector.second.size() == 0)
        toDeleteMeshes.push_back(meshVector.first);

      Util::setDepthTest(false);
    }

    for (auto x : toDeleteMeshes) {
      _meshes.erase(x);
    }
  }

}