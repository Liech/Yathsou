#pragma once

#include <map>
#include <vector>
#include <memory>
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"
#include <glm/glm.hpp>
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class ShaderProgram;
  class Camera;
  class IMesh;
  class UniformVec3;
  class UniformVecMat4;
  class UniformVecVec3;

  struct DiffuseMeshRendererMesh {
    glm::mat4                                   transformation = glm::mat4(1.0);
    Iyathuum::Color                             color = Iyathuum::Color(255, 255, 255);
    std::shared_ptr<Mesh<PositionNormalVertex>> mesh;
  };

  class DiffuseMeshRenderer {
  public:
    DiffuseMeshRenderer(std::shared_ptr<Camera> camera);
    virtual ~DiffuseMeshRenderer();

    void setLightDirection(const glm::vec3& dir);
    glm::vec3 getLightDirection() const;

    void addMesh(std::shared_ptr<DiffuseMeshRendererMesh>);

    void draw();

  private:
    void makeShader();

    std::shared_ptr<ShaderProgram>    _shader;
    std::shared_ptr<Camera>           _camera;
    glm::vec3                         _lightDirection;
    
    std::shared_ptr<UniformVec3   >   _light ;
    std::unique_ptr<UniformVecMat4>   _models;
    std::unique_ptr<UniformVecVec3>   _colors;

    size_t _bufferSize = 1000;
    std::map<std::shared_ptr<Mesh<PositionNormalVertex>>, std::vector<std::weak_ptr<DiffuseMeshRendererMesh>>> _meshes; //sorry :(
  };
}