#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

namespace Aezesel {
  namespace Private {
    class AssimpUtil {
    public:
      static glm::mat4 convert(aiMatrix4x4);
      static aiMatrix4x4 convert(glm::mat4 mat);
    };
  }
}