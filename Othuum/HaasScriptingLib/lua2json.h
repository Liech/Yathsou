#pragma once

#include "lib/json.hpp"

namespace Haas
{
  class lua2json
  {
  public:
    static nlohmann::json fromLua(std::string filename);
  };
}