#include "InstancedRectangle.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Ahwassa {
  glm::mat4 InstancedRectangle::matrix() const {
    const float x  = location.getPosition()[0];
    const float y  = location.getPosition()[1];
    const float xs = location.getSize    ()[0];
    const float ys = location.getSize    ()[1];
    float transAndScale[16] = {
      xs, 0 , 0, 0,
      0 , ys, 0, 0,
      0 , 0 , 1, 0,
      x , y , 0, 1
    };
    return glm::make_mat4(transAndScale);
  }

  glm::vec3 InstancedRectangle::colorVec() const {
    return color.to3();
  }
}