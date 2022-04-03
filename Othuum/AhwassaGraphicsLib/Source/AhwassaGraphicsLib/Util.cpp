#include "Util.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Ahwassa {
  double Util::getTime() {
    return glfwGetTime();
  }

  size_t Util::maxUniformAmount() {
    int result = 1000;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &result);
    //glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &result);
    return result;
  }

  void Util::setDepthTest(bool enabled) {
    if (enabled)
      glEnable(GL_DEPTH_TEST);
    else
      glDisable(GL_DEPTH_TEST);
  }

  void Util::setBlend(bool enabled) {
    if (enabled)
      glEnable(GL_BLEND);
    else
      glDisable(GL_BLEND);
  }

  void Util::depthMask(bool enabled) {
    if (enabled)
      glDepthMask(GL_TRUE);
    else
      glDepthMask(GL_FALSE);
  }

  void Util::setDepthFuncLess() {
    glDepthFunc(GL_LESS);
  }

  void Util::setDepthFuncMore() {
    glDepthFunc(GL_GREATER);
  }

  void Util::setTextureBlend() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void Util::setCulling(bool front) {
    if (front)
      glCullFace(GL_FRONT);
    else
      glCullFace(GL_BACK);
  }
  void Util::enableCulling(bool enabled) {
    if (enabled)
      glEnable(GL_CULL_FACE);
    else
      glDisable(GL_CULL_FACE);
  }

  void Util::setWireframe(bool enabled) {
    if (enabled)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  glm::mat4 Util::removeTranslation(const glm::mat4& input) {
    double dArray[16] = { 0.0 };

    const float* pSource = (const float*)glm::value_ptr(input);
    for (int i = 0; i < 12; ++i)
      dArray[i] = pSource[i];
    dArray[15] = 1;
    return glm::make_mat4(dArray);
  }
}