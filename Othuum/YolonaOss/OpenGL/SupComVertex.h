#pragma once

#include <glad/glad.h>
#include <vector>
#include "AttributeDescription.h"
#include <IyathuumCoreLib/lib/glm/glm.hpp>
namespace YolonaOss {
  namespace GL {
    struct SupComVertex {     
      glm::vec3 position;
      glm::vec3 tangent ;
      glm::vec3 normal  ;
      glm::vec3 binormal;
      glm::vec2 uv1     ;
      glm::vec2 uv2     ;

      SupComVertex() {
        position = glm::vec3(0.0f);
        tangent  = glm::vec3(0.0f);
        normal   = glm::vec3(0.0f);
        binormal = glm::vec3(0.0f);
        uv1      = glm::vec2(0.0f);
        uv2      = glm::vec2(0.0f);
      };

      static std::vector<AttributeDescription> getBinding() {
        std::vector<AttributeDescription> result;
        result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
        result.push_back(AttributeDescription("tangent" , 3, AttributeDescription::DataType::Float));
        result.push_back(AttributeDescription("normal"  , 3, AttributeDescription::DataType::Float));
        result.push_back(AttributeDescription("binormal", 3, AttributeDescription::DataType::Float));
        result.push_back(AttributeDescription("uv1"     , 2, AttributeDescription::DataType::Float));
        result.push_back(AttributeDescription("uv2"     , 2, AttributeDescription::DataType::Float));
        return result;
      }
    };
  }
}