#include "Window.h"
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include "IyathuumCoreLib/Singleton/Factory.h"
#include "Drawable.h"
#include "Loadable.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "Drawables/Widgets/Widget.h"
#include "../Camera/Camera.h"
#include "Updateable.h"
#include <functional>
#include "Util/Util.h"
#include "InputHandling.h"

namespace YolonaOss {
  namespace GL {
    Window* win;

    Window::Window(int width, int height)
    {
      _width = width;
      _height = height;
    }

    Window::~Window()
    {
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
      std::string msgSource;
      switch (source) {
      case GL_DEBUG_SOURCE_API:
        msgSource = "WINDOW_SYSTEM";
        break;
      case GL_DEBUG_SOURCE_SHADER_COMPILER:
        msgSource = "SHADER_COMPILER";
        break;
      case GL_DEBUG_SOURCE_THIRD_PARTY:
        msgSource = "THIRD_PARTY";
        break;
      case GL_DEBUG_SOURCE_APPLICATION:
        msgSource = "APPLICATION";
        break;
      case GL_DEBUG_SOURCE_OTHER:
        msgSource = "OTHER";
        break;
      }

      std::string msgType;
      switch (type) {
      case GL_DEBUG_TYPE_ERROR:
        msgType = "ERROR";
        break;
      case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        msgType = "DEPRECATED_BEHAVIOR";
        break;
      case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        msgType = "UNDEFINED_BEHAVIOR";
        break;
      case GL_DEBUG_TYPE_PORTABILITY:
        msgType = "PORTABILITY";
        break;
      case GL_DEBUG_TYPE_PERFORMANCE:
        msgType = "PERFORMANCE";
        break;
      case GL_DEBUG_TYPE_OTHER:
        msgType = "OTHER";
        break;
      }

      std::string msgSeverity;
      switch (severity) {
      case GL_DEBUG_SEVERITY_LOW:
        msgSeverity = "LOW";
        break;
      case GL_DEBUG_SEVERITY_MEDIUM:
        msgSeverity = "MEDIUM";
        break;
      case GL_DEBUG_SEVERITY_HIGH:
        msgSeverity = "HIGH";
        break;
      }

	  //printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
	  
	  if (msgSeverity == "MEDIUM")
        printf("glDebugMessage:\n%s \n type = %s source = %s severity = %s\n", message, msgType.c_str(), msgSource.c_str(), msgSeverity.c_str());
      if (msgSeverity == "HIGH")
        throw std::runtime_error("OPENGL ERROR:" + std::string(message));
    }


    void Window::run() {
      std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
      // Init GLFW
      glfwInit();
      // Set all the required options for GLFW
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
      glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

      // Create a GLFWwindow object that we can use for GLFW's functions
      _window = glfwCreateWindow(_width, _height, "GL", NULL, NULL);
      win = this;
      InputHandling::getInstance(). setWindow(_window, win);
      glfwMakeContextCurrent(_window);
      if (_window == NULL)
      {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
      }

      // Set the required callback functions
      glfwSetMouseButtonCallback(_window, mouse_button_callback);
      glfwSetKeyCallback(_window, key_callback);
      glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
          win->_mouseWheelMovement += (float)yoffset;
          InputHandling::getInstance().mouseWheel(xoffset,yoffset);
        });

      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
      }

      GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
      if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
      {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
      }

      Startup();
      // Define the viewport dimensions
      glViewport(0, 0, _width, _height);
      glDepthFunc(GL_LESS);

      std::shared_ptr<YolonaOss::Camera::Camera> camera = std::make_shared<YolonaOss::Camera::Camera>(_width, _height);
      DrawSpecification spec(this, camera);
      _spec = &spec;
      spec.width = _width;
      spec.height = _height;
      std::vector<std::shared_ptr<Loadable>> loadList;
      for (auto renderStep : Iyathuum::Factory<Loadable>::getNamesByTag("Main"))
        loadList.push_back(Iyathuum::Factory<Loadable>::make(renderStep));
      for (auto renderStep : Iyathuum::Database<std::shared_ptr<GL::Drawable>>::getByTag("Main")) {
        loadList.push_back(renderStep);
      }
      for (auto renderStep : Iyathuum::Database<std::shared_ptr <Updateable>>::getByTag("Main")) {
        loadList.push_back(renderStep);
      }
      for (auto renderStep : loadList)
        renderStep->load(&spec);      

      // Game loop
      while (!glfwWindowShouldClose(_window))
      {
        _mouseWheelMovement = 0;
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        InputHandling::getInstance().updateEvent();
        for (auto update : Iyathuum::Database<std::shared_ptr <Updateable>>::getByTag("Main"))
          update->update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto draw : Iyathuum::Database<std::shared_ptr<GL::Drawable>>::getByTag("Main"))
          draw->draw();
        Update();

        glfwSwapBuffers(_window);
      }

      // Terminates GLFW, clearing any resources allocated by GLFW.
      glfwTerminate();
    }

    Widgets::Widget* pressed = nullptr;
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
      InputHandling::getInstance().mouseEvent((Iyathuum::Key)button, (Iyathuum::KeyStatus)action, mods);
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
      InputHandling::getInstance().keyEvent((Iyathuum::Key)key, (Iyathuum::KeyStatus)action, mode);
      if ((int)key == GLFW_KEY_ESCAPE && (int)action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    Iyathuum::KeyStatus Window::getKeyStatus(Iyathuum::Key key) {
      if ((int)key <= 7)
        return (Iyathuum::KeyStatus)((int)glfwGetMouseButton(_window, (int)key));
      else
        return (Iyathuum::KeyStatus)((int)glfwGetKey(_window, (int)key));
    }

    void Window::setCursorStatus(Iyathuum::CursorStatus status) {
      glfwSetInputMode(_window, GLFW_CURSOR, (int)status);
    }

    glm::vec2 Window::getCursorPos() {
      double xpos, ypos;
      glfwGetCursorPos(_window, &xpos, &ypos);
      return glm::vec2(xpos, ypos);
    }

    void Window::setCursorPos(glm::vec2 cursorPos) {
      glfwSetCursorPos(_window, cursorPos.x, cursorPos.y);
    }

    double Window::getTime() {
      return glfwGetTime();
    }

    float Window::getMouseWheelMovement() {
      return _mouseWheelMovement;
    }

    void Window::close() {
      glfwSetWindowShouldClose(_window, GL_TRUE);
    }
  }
}