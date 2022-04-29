#pragma once

#include "IVertex.h"
#include <glm/glm.hpp>
#include <vector>

#include "IyathuumCoreLib/BaseTypes/Model3D.h"

namespace Ahwassa {
  struct AttributeDescription;

  struct Model3DVertex {
    glm::vec3 position  ;
    glm::vec3 normal    ;
    glm::vec3 bitangent ;
    glm::vec3 tangent   ;
    glm::vec2 texCoord  ;
    glm::vec4 boneIndex ; //integer array in disguise
    glm::vec4 boneWeight; //float array in disguise

    Model3DVertex();
    Model3DVertex(glm::vec3 Position, glm::vec3 Normal, glm::vec3 Bitangent, glm::vec3 Tangent, glm::vec2 Texcoord, glm::vec4 boneI, glm::vec4 boneW);

    static std::vector<AttributeDescription> getBinding();
    std::vector<AttributeDescription>        binding() const;
  };
}