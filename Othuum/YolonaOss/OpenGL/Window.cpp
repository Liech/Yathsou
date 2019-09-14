#include "Window.h"
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>

Window::Window(int width, int height)
{
  _width = width;
  _height = height;
}

Window::~Window()
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
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
  GLFWwindow* window = glfwCreateWindow(_width, _height, "GL", NULL, NULL);
  glfwMakeContextCurrent(window);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }

  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);
  _window = window;

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


  // Game loop
  while (!glfwWindowShouldClose(window))
  {
    // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
    glfwPollEvents();

    Update();

    // Swap the screen buffers
    glfwSwapBuffers(window);
  }

  // Terminates GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  std::cout << key << std::endl;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}