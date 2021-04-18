#pragma once

#include "AezeselFileIOLib/lib/json.hpp"

namespace Athanah {
  class BlueprintGeneral;

  class Blueprint {
  public:
    Blueprint(std::string id,  const nlohmann::json& input);
    Blueprint(const std::string id);


    std::string       getName() const;
    BlueprintGeneral& general() const;

  private:
    std::string _name;
    std::string _id;

    std::shared_ptr<BlueprintGeneral> _general;
  };
}