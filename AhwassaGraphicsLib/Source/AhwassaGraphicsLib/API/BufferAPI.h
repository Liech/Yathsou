#pragma once

#include <memory>
#include <map>
#include <string>

namespace Iyathuum {
  class API;
  class FunctionRelay;
}

namespace Ahwassa {
  class BufferAPI {
    public:
    static BufferAPI& instance();

    ~BufferAPI();

    void add(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

    private:
      BufferAPI() = default;

      void createVBO(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

      std::map<std::string, std::shared_ptr<IVBO>> _vbos;
  };
}