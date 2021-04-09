#pragma once

#include <map>
#include <vector>
#include <memory>
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "SupComVertex.h"

namespace Ahwassa {
  class ShaderProgram;
  class Camera;
  class IMesh;
  class UniformVec3;
  class UniformVecMat4;
  class UniformVecVec3;
  class Texture;
}

namespace Athanah {
  class SupComModel;

  struct SupComMesh {
    glm::mat4                    transformation;
    Iyathuum::Color              color;
    std::shared_ptr<SupComModel> model;
  };

  class SupComMeshRenderer {
  public:
    SupComMeshRenderer(std::shared_ptr<Ahwassa::Camera> camera);
    virtual ~SupComMeshRenderer();

    void setLightDirection(glm::vec3 dir);
    glm::vec3 getLightDirection();

    void addMesh(std::shared_ptr<SupComMesh>);

    void draw();

  private:
    void makeShader();

    std::shared_ptr<Ahwassa::ShaderProgram>    _shader        ;
    std::shared_ptr<Ahwassa::Camera>           _camera        ;
    glm::vec3                                  _lightDirection;
    
    std::shared_ptr<Ahwassa::UniformVec3   >   _light ;
    std::shared_ptr<Ahwassa::Texture       >   _albedo;
    std::shared_ptr<Ahwassa::Texture       >   _info  ;
    std::shared_ptr<Ahwassa::Texture       >   _normal;

    std::unique_ptr<Ahwassa::UniformVecMat4>   _models;
    std::unique_ptr<Ahwassa::UniformVecVec3>   _colors;

    size_t _bufferSize = 1000;
    std::map<std::shared_ptr<SupComModel>, std::vector<std::weak_ptr<SupComMesh>>> _meshes;
  };
}