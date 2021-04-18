#pragma once

#include "AezeselFileIOLib/lib/json.hpp"

namespace Athanah {
  class Blueprint {
  public:
    Blueprint(std::string id,  const nlohmann::json& input);
    Blueprint(const std::string id);

    std::string getName() const;

  private:
    std::string _name;
    std::string _id;

  };
}