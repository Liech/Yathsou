#include "AssimpUtil.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Aezesel {
  namespace Private {
    glm::mat4 AssimpUtil::convert(aiMatrix4x4 input) {
      float resultArray[16] = {
        input.a1,input.a2,input.a3,input.a4,
        input.b1,input.b2,input.b3,input.b4,
        input.c1,input.c2,input.c3,input.c4,
        input.d1,input.d2,input.d3,input.d4
      };

      glm::mat4 result = glm::make_mat4(resultArray);
      return result;
    }

    aiMatrix4x4 AssimpUtil::convert(glm::mat4 mat)
    {
      return aiMatrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
        mat[1][0], mat[1][1], mat[1][2], mat[1][3],
        mat[2][0], mat[2][1], mat[2][2], mat[2][3],
        mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
    }
  }
}