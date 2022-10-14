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

  class BufferAPI {
    public:
    static BufferAPI& instance();

    ~BufferAPI();

    void add(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

    private:
      BufferAPI() = default;

      void drawBuffer(Iyathuum::API&, Iyathuum::FunctionRelay& relay);
      void createVBO (Iyathuum::API&, Iyathuum::FunctionRelay& relay);
      void createIBO (Iyathuum::API&, Iyathuum::FunctionRelay& relay);

      std::map<std::string, std::shared_ptr<IVBO>> _vbos;
      std::map<std::string, std::shared_ptr<VAO>>  _vaos;
      std::map<std::string, std::shared_ptr<IBO>>  _ibos;
  };
}