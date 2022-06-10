#pragma once

#include <memory>

namespace Iyathuum {
  class API;
  class FunctionRelay;
}

namespace Ahwassa {
  class API {
    public:
      API() = default;
      virtual ~API() = default;

      std::unique_ptr<Iyathuum::API> getAPI(Iyathuum::FunctionRelay&);
  };
}