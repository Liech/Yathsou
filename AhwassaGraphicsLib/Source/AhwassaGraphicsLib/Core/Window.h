#pragma once

#include <memory>
#include <map>
#include <functional>
#include <glm/glm.hpp>

struct GLFWwindow;

namespace Ahwassa {
  class Drawable;
  class Input;
  class Renderer;
  class Camera;

  class Window
  {
  public:
    Window(const std::string& title, const glm::ivec2& resolution);
    virtual ~Window();

    Input&                  input   ();
    Renderer&               renderer();
    std::shared_ptr<Camera> camera  ();

    void run  ();
    void close();
    void frame();

    std::function<void(                 )> Startup = []() {};
    std::function<void(                 )> Update  = []() {};
    std::function<void(const glm::ivec2&)> Resize  = [](const glm::ivec2&) {};

    glm::ivec2 getResolution() const;

    GLFWwindow* ptr();
  private:
    static void windowResized(GLFWwindow* window, int width, int height);

    glm::ivec2                _resolution  = glm::ivec2(1920,1080);
    GLFWwindow*               _window = nullptr;
    std::unique_ptr<Input>    _input;
    std::unique_ptr<Renderer> _renderer;
    std::shared_ptr<Camera>   _camera;
    std::string               _title;

    inline static std::map<GLFWwindow*, Window*> _instanceMap;
  };
}
