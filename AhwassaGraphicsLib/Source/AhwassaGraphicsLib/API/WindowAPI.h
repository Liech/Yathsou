#pragma once

#include <memory>

namespace Iyathuum {
  class API;
  class FunctionRelay;
}

namespace Ahwassa {
  class Window;

  class WindowAPI {
    public:
    static WindowAPI& instance();

    ~WindowAPI();

    void add(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

    private:
      WindowAPI() = default;

      void createWindow(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

      std::unique_ptr<Window> _window;
  };
}