#pragma once

#include <memory>
#include <map>
#include <string>

namespace Iyathuum {
  class API;
  class FunctionRelay;
}

namespace Ahwassa {
  class IVBO;
  class IBO;
  class VAO;

  class UtilAPI {
    public:
    static UtilAPI& instance();

    ~UtilAPI();

    void add(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

    private:
      void setDepthBufferTest(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

      UtilAPI() = default;

  };
}