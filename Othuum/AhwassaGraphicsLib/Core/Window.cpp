#include "Window.h"

#include <iostream>
#include <string>
#include <functional>
#include <chrono>
#include <thread>

#include "Input/Input.h"

#include "glad/glad.h"
#include "YolonaOss/Lib/GLWF/include/GLFW/glfw3.h"

namespace Ahwassa {
  Window* win;

  Window::Window(int width, int height)
  {
    _width = width;
    _height = height;
  }

  Window::~Window()
  {
  }

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

	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
	
	if (msgSeverity == "MEDIUM")
      printf("glDebugMessage:\n%s \n type = %s source = %s severity = %s\n", message, msgType.c_str(), msgSource.c_str(), msgSeverity.c_str());
  if (msgSeverity == "HIGH") {
    std::cout << message << std::endl;
    throw std::runtime_error("OPENGL ERROR:" + std::string(message));
  }
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

    _input = std::make_unique<Input>(_window,this);

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

    auto start = std::chrono::steady_clock::now();

    // Game loop
    while (!glfwWindowShouldClose(_window))
    {
      auto now = std::chrono::steady_clock::now();
      auto diff = now - start;
      auto end = now + std::chrono::milliseconds(8);

      glfwPollEvents();
      //update

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      input().update();
      Update();
      std::this_thread::sleep_until(end);

      glfwSwapBuffers(_window);
    }

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
  }

  void Window::close() {
    glfwSetWindowShouldClose(_window, GL_TRUE);
  }

  Input& Window::input() {
    return *_input;
  }
}