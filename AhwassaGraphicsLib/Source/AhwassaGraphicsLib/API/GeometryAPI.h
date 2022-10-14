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

  class GeometryAPI {
    public:
    static GeometryAPI& instance();

    ~GeometryAPI();

    void add(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

    private:
      void generateCube(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

      GeometryAPI() = default;

  };
}