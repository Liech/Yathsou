#include "Util.h"

#include "AhwassaGraphicsLib/lib/glad/include/glad/glad.h"
#include "AhwassaGraphicsLib/lib/GLWF/include/GLFW/glfw3.h"

namespace Ahwassa {
  double Util::getTime() {
    return glfwGetTime();
  }

  size_t Util::maxUniformAmount() {
    int result = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&result);
    return result;
  }
}