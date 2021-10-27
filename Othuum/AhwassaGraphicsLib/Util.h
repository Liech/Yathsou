#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <utility>

namespace Ahwassa {

  class Util {
  public:
    static double getTime();
    static size_t maxUniformAmount();
    static void setDepthTest(bool enabled);
    static void setBlend(bool enabled);
    static void setDepthFuncLess();
    static void setDepthFuncMore();
    static void setCulling(bool front);
    static void enableCulling(bool enabled);
    static void depthMask(bool enabled);
    static void setWireframe(bool enabled);
    static void setTextureBlend();


    static glm::mat4 removeTranslation(const glm::mat4& input);

  };
}