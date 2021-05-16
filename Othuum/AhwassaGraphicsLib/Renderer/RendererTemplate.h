#pragma once

#include <memory>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

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
      _description = description;
    }

    void init() {
      _initialized = true;
      _uniforms = initUniforms();
      makeShader();
    }

    virtual ~RendererTemplate() {

    }

    void addInstance(std::shared_ptr<IMesh> mesh, std::shared_ptr<AdditionalInfo> info) {
      if (!_initialized)
        throw std::runtime_error("Not initialized");
      if (_meshes.count(mesh) == 0)
        _meshes[mesh] = std::vector<std::weak_ptr<AdditionalInfo>>{ info };
      else
        _meshes[mesh].push_back(info);
    }

    void draw() {
      if (!_initialized)
        throw std::runtime_error("Not initialized");
      
     prepare();
     _shader->bind();
     _camera->bind();
     
     std::set<std::shared_ptr<IMesh>> toDeleteMesh;
     for (auto& meshVector : _meshes) {
        size_t currentPosition = 0;

        std::vector<int> toDelete;
        toDelete.reserve(40);
        for (auto x : meshVector.second){
          std::shared_ptr<AdditionalInfo> m = x.lock();
          if (!m) {
            continue;//removed at the end
          }
          if (currentPosition >= bufferSize()) {
            drawBatch(*meshVector.first,currentPosition);
            currentPosition = 0;
          }
          vectorize(currentPosition,m);
          currentPosition++;
        }
        
        drawBatch(*meshVector.first,currentPosition);
        
        auto IsMarkedToDelete = [](const std::weak_ptr<AdditionalInfo>& o)
        {
          return o.lock() == nullptr;
        };

        meshVector.second.erase(std::remove_if(meshVector.second.begin(), meshVector.second.end(), IsMarkedToDelete), meshVector.second.end());
        
        if (meshVector.second.size() == 0)
          toDeleteMesh.insert(meshVector.first);
      }
      for (auto x : toDeleteMesh)
        _meshes.erase(x);
      cleanup();
    }

  protected:
    virtual std::string vertexShader  () = 0;
    virtual std::string fragmentShader() = 0;
    virtual std::vector<std::shared_ptr<Ahwassa::Uniform>> initUniforms() = 0;
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

    std::shared_ptr<Camera> getCamera() const { return _camera; }


  private:

    void makeShader() {
      std::vector<Ahwassa::Uniform*> uniforms;
      std::vector<Ahwassa::Uniform*> cameraUniforms = _camera->getUniforms();
      uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
      for (int i = 0; i < _uniforms.size(); i++)
        uniforms.push_back(_uniforms[i].get());
      std::vector<Ahwassa::AttributeDescription> attributes = _description;
      std::string vs   = vertexShader();
      std::string fs = fragmentShader();
      _shader = std::make_shared<Ahwassa::ShaderProgram>(attributes, uniforms, vs, fs);
    }

    void drawBatch(const IMesh& mesh, size_t amount) {
      bind();
      mesh.drawInstanced(amount);
    }

    bool _initialized = false;
    std::vector<std::shared_ptr<Uniform>>   _uniforms   ;
    std::vector<AttributeDescription>       _description;
    std::shared_ptr<Ahwassa::ShaderProgram> _shader     ;
    std::shared_ptr<Ahwassa::Camera>        _camera     ;
    std::map<std::shared_ptr<IMesh>, std::vector<std::weak_ptr<AdditionalInfo>>> _meshes;
  };
}