#pragma once

namespace Iyathuum {
  class API;
  class FunctionRelay;
}

namespace Ahwassa {
  class WindowAPI {
    public:
    static WindowAPI& instance();

    void add(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

    private:
      WindowAPI() = default;

  };
}