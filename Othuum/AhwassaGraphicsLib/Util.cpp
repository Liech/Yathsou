#include "Util.h"

#include "AhwassaGraphicsLib/lib/glad/include/glad/glad.h"
#include "AhwassaGraphicsLib/lib/GLWF/include/GLFW/glfw3.h"


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

  std::shared_ptr<Mesh<PositionNormalVertex>> Util::getCube() {
    std::vector<PositionNormalVertex> input;
    float start = 0;
    float end = 1;
    //front
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end), glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end), glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end), glm::vec3(0, 0, 1)));

    //right
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end), glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start), glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end), glm::vec3(1, 0, 0)));

    //back
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start), glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(0, 0, -1)));

    //left
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end), glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(-1, 0, 0)));

    //upper
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end), glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end), glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start), glm::vec3(0, 1, 0)));

    //bottom
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end), glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(0, -1, 0)));

    //note every face of the cube is on a single line
    auto indices = std::vector<int>{
      0,  1,  2,  0,  2,  3,   //front
      4,  5,  6,  4,  6,  7,   //right
      8,  9,  10, 8,  10, 11,  //back
      12, 13, 14, 12, 14, 15,  //left
      16, 17, 18, 16, 18, 19,  //upper
      20, 21, 22, 20, 22, 23 }; //bottom

    return std::make_shared< Mesh<PositionNormalVertex>>(input, indices);
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
}