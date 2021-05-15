#pragma once

#include <map>
#include <vector>
#include <memory>
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AthanahCommonLib/SupCom/SupComVertex.h"

namespace Ahwassa {
  class ShaderProgram;
  class Camera;
  class IMesh;
  class SSBOmat4;
  class SSBOvec3;
  class Texture;
}

namespace Athanah {
  class SupComModel;

  struct SupComMesh {
    glm::mat4                    transformation;
    Iyathuum::Color              teamColor;
    std::shared_ptr<SupComModel> model;
    std::vector<glm::mat4>       animation;
  };

  //Def stands for deferred
  class SupComMeshRendererDef {
  public:
    SupComMeshRendererDef(std::shared_ptr<Ahwassa::Camera> camera);
    virtual ~SupComMeshRendererDef();

    void addMesh(std::shared_ptr<SupComMesh>);

    void draw();

  private:
    void makeShader();


    std::shared_ptr<Ahwassa::ShaderProgram>    _shader        ;
    std::shared_ptr<Ahwassa::Camera>           _camera        ;
    glm::vec3                                  _lightDirection;
    
    std::shared_ptr<Ahwassa::Texture       >   _albedo   ;
    std::shared_ptr<Ahwassa::Texture       >   _info     ;
    std::shared_ptr<Ahwassa::Texture       >   _normal   ;

    std::shared_ptr<Ahwassa::SSBOmat4> _animations ;
    std::shared_ptr<Ahwassa::SSBOmat4> _models     ;
    std::shared_ptr<Ahwassa::SSBOmat4> _modelsRot  ;
    std::shared_ptr<Ahwassa::SSBOvec3> _colors     ;

    size_t _bufferSize = 1000;
    size_t _maxBoneSize = 150;
    std::map<std::shared_ptr<SupComModel>, std::vector<std::weak_ptr<SupComMesh>>> _meshes;
  };
}