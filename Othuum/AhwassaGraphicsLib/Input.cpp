#include "Input.h"

#include "YolonaOss/Lib/glad/include/glad/glad.h"
#include "YolonaOss/Lib/GLWF/include/GLFW/glfw3.h"

namespace Ahwassa {
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

  Input::Input(GLFWwindow* win) {
    _window = win;


    // Set the required callback functions
    glfwSetMouseButtonCallback(_window, mouse_button_callback);
    glfwSetKeyCallback(_window, key_callback);
    glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset)
    {
    });
  }

  Iyathuum::KeyStatus Input::getKeyStatus(Iyathuum::Key key) {
    if ((int)key <= 7)
      return (Iyathuum::KeyStatus)((int)glfwGetMouseButton(_window, (int)key));
    else
      return (Iyathuum::KeyStatus)((int)glfwGetKey(_window, (int)key));
  }

  void Input::setCursorStatus(Iyathuum::CursorStatus status) {
    glfwSetInputMode(_window, GLFW_CURSOR, (int)status);
  }

  glm::vec2 Input::getCursorPos() {
    double xpos, ypos;
    glfwGetCursorPos(_window, &xpos, &ypos);
    return glm::vec2(xpos, ypos);
  }

  void Input::setCursorPos(glm::vec2 cursorPos) {
    glfwSetCursorPos(_window, cursorPos.x, cursorPos.y);
  }


  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
  }

  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
  {
    if ((int)key == GLFW_KEY_ESCAPE && (int)action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
  }
}