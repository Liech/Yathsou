#pragma once

#include <memory>
#include <vector>
#include <map>
#include <set>

#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Core/AttributeDescription.h"
#include "AhwassaGraphicsLib/Uniforms/Uniform.h"
#include "AhwassaGraphicsLib/BufferObjects/IMesh.h"
#include "AhwassaGraphicsLib/Util.h"

namespace Ahwassa {

  template<typename AdditionalInfo>
  class RendererTemplate {
  public:
    RendererTemplate(std::shared_ptr<Ahwassa::Camera> camera, std::vector<AttributeDescription> description) {
      _camera      = camera     ;
      _uniforms    = initUniforms();
      _description = description;
    }

    virtual ~RendererTemplate() {

    }

    void addInstance(std::shared_ptr<IMesh> mesh, std::shared_ptr<AdditionalInfo> info) {
      if (_meshes.count(mesh) == 0)
        _meshes[mesh] = std::set<std::shared_ptr<AdditionalInfo>>{ info };
      else
        _meshes[mesh].insert(info);
    }

    void draw() {
      prepare();
      _shader->bind();
      _camera->bind();
      
      std::set<std::shared_ptr<IMesh>> toDeleteMesh;

      for (auto& meshVector : _meshes) {
        size_t currentPosition = 0;

        std::vector<std::weak_ptr<AdditionalInfo>> toDelete;
        toDelete.reserve(40);
        for (size_t i = 0; i < meshVector.second.size(); i++) {
          auto m = meshVector.second[i].lock();
          if (!m) {
            toDelete.push_back(i);
            continue;
          }
          if (currentPosition >= bufferSize()) {
            drawBatch(*meshVector.first,currentPosition);
            currentPosition = 0;
          }
          vectorize(currentPosition,meshVector.second[i]);
          currentPosition++;
        }
        
        drawBatch(*meshVector.first,currentPosition);

        for (auto x : toDelete)
          meshVector.second.erase(x);
        if (meshVector.second.size() == 0)
          toDeleteMesh.insert(meshVector.first);
      }
      for (auto x : toDeleteMesh)
        _meshes.erase(x);
      cleanup();
    }

  protected:
    virtual const std::string vertexShader  () const = 0;
    virtual const std::string fragmentShader() const = 0;
    virtual std::vector<std::shared_ptr<Uniform>> initUniforms() = 0;
    virtual void vectorize(const size_t& index, std::shared_ptr<AdditionalInfo>) = 0; //place vars in ssbo
    virtual void bind() = 0;

    virtual void prepare() {
      Ahwassa::Util::setDepthTest(true);
      Ahwassa::Util::setDepthFuncLess();
      Ahwassa::Util::depthMask(true);
    }

    virtual void cleanup() {
      Ahwassa::Util::setDepthTest(false);
    }

    virtual size_t bufferSize() const { return 1000; }

  private:
    void drawBatch(const IMesh& mesh ,size_t amount) {
      bind();
      mesh.drawInstanced(amount);
    }

    void makeShader() {
      std::vector<Ahwassa::Uniform*> uniforms;
      std::vector<Ahwassa::Uniform*> cameraUniforms = _camera->getUniforms();
      uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
      _shader = std::make_unique<Ahwassa::ShaderProgram>(_description, uniforms, vertexShader(), fragmentShader());
    }

    std::vector<std::shared_ptr<Uniform>>   _uniforms   ;
    std::vector<AttributeDescription>       _description;
    std::shared_ptr<Ahwassa::ShaderProgram> _shader     ;
    std::shared_ptr<Ahwassa::Camera>        _camera     ;
    std::map<std::shared_ptr<IMesh>, std::set<std::weak_ptr<AdditionalInfo>>> _meshes;
  };
}