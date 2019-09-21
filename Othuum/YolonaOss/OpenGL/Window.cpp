#include "Window.h"
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include "structs/Factory.h"
#include "Drawable.h"
#include "Loadable.h"
#include "structs/Database.h"
#include "Drawables/Widgets/Widget.h"
#include "Camera.h"
#include "Updateable.h"

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
        });
      //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      //{
      //  std::cout << "Failed to initialize OpenGL context" << std::endl;
      //  return;
      //}
      gladLoadGL();


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

      std::shared_ptr<GL::Camera> camera = std::make_shared<GL::Camera>("Camera", _width, _height);
      DrawSpecification spec(this,camera);
      spec.width = _width;
      spec.height = _height;
      std::vector<std::shared_ptr<Loadable>> loadList;
      for (auto renderStep : Factory<Loadable>::getNamesByTag("Main"))
        loadList.push_back(Factory<Loadable>::make(renderStep));
      for (auto renderStep : Database<std::shared_ptr<GL::Drawable>>::getByTag("Main")) {
        loadList.push_back(renderStep);
      }
      for (auto renderStep : Database<std::shared_ptr <Updateable>>::getByTag("Main")) {
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

        for (auto update : Database<std::shared_ptr <Updateable>>::getByTag("Main"))
          update->update();

        Update();
        for (auto draw : Database<std::shared_ptr<GL::Drawable>>::getByTag("Main"))
          draw->draw();

        // Swap the screen buffers
        glfwSwapBuffers(_window);

      }

      // Terminates GLFW, clearing any resources allocated by GLFW.
      glfwTerminate();
    }

    std::shared_ptr<Widget> pressed = std::shared_ptr<Widget>();
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
      double xpos, ypos;
      glfwGetCursorPos(window, &xpos, &ypos);
      glm::vec2 mousePos((float)xpos, (float)(win->getHeight() - ypos));

      std::set<std::shared_ptr<Widget>> clickableWidgets = Database<std::shared_ptr<Widget>>::getByTag("MouseClick");
      for (auto w : clickableWidgets) {
        if (w->getPosition().inside(mousePos)) {
          if (action == (int)KeyStatus::PRESS)
            pressed = w;
          else
            if (action == (int)KeyStatus::RELEASE && pressed == w)
              w->mouseClick(mousePos - w->getPosition().position, (Key)button);
        }
      }
      if (action == (int)KeyStatus::RELEASE)
        pressed = std::shared_ptr<Widget>();
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
      //std::cout << key << std::endl;
      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    KeyStatus Window::getKeyStatus(Key key) {
      if ((int)key <= 7)
        return (KeyStatus)((int)glfwGetMouseButton(_window, (int)key));
      else
        return (KeyStatus)((int)glfwGetKey(_window, (int)key));
    }

    void Window::setCursorStatus(CursorStatus status) {
      glfwSetInputMode(_window, GLFW_CURSOR, (int)status);
    }

    std::pair<double, double> Window::getCursorPos() {
      double xpos, ypos;
      glfwGetCursorPos(_window, &xpos, &ypos);
      return std::make_pair(xpos, ypos);
    }


    void Window::setCursorPos(std::pair<double, double> cursorPos) {
      glfwSetCursorPos(_window, cursorPos.first, cursorPos.second);
    }

    double Window::getTime() {
      return glfwGetTime();
    }

    float Window::getMouseWheelMovement() {
      return _mouseWheelMovement;
    }
  }
}