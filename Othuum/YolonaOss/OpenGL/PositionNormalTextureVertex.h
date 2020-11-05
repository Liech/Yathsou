#pragma once

#include <glad/glad.h>
#include <vector>
#include "AttributeDescription.h"
#include <IyathuumCoreLib/lib/glm/glm.hpp>
namespace YolonaOss {
  namespace GL {
    struct PositionNormalTextureVertex {
      glm::vec3 position;
      glm::vec3 normal  ;
      glm::vec2 texture ;
      
      PositionNormalTextureVertex() {
        position = glm::vec3(0, 0, 0);
        normal   = glm::vec3(1, 0, 0);
        texture  = glm::vec2(0, 0);
      };

      PositionNormalTextureVertex(glm::vec3 Position, glm::vec3 Normal, glm::vec2 Texture) {
        position = Position;
        normal   = Normal;
        texture  = Texture;
      }

      static std::vector<AttributeDescription> getBinding() {
        std::vector<AttributeDescription> result;
        result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
        result.push_back(AttributeDescription("normal"  , 3, AttributeDescription::DataType::Float));
        result.push_back(AttributeDescription("texCoord", 2, AttributeDescription::DataType::Float));
        return result;
      }
    };
  }
}