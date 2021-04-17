#pragma once

#include "AezeselFileIOLib/lib/json.hpp"

namespace Athanah {
  class Blueprint {
  public:
    Blueprint(const nlohmann::json& input);

    std::string getName() const;

  private:
    std::string _name;

  };
}