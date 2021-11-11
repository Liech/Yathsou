#pragma once

#include "AezeselFileIOLib/lib/json.hpp"

namespace Athanah {
  class BlueprintGeneral;
  class BlueprintDisplay;
  class BlueprintPhysic;

  class Blueprint {
  public:
    Blueprint(std::string id,  const nlohmann::json& input);
    Blueprint(const std::string id);
    virtual ~Blueprint() = default;

    std::string       strategicIcon() const;
    std::string       description()   const;
    BlueprintGeneral& general()       const;
    BlueprintDisplay& display()       const;
    BlueprintPhysic&  physic()        const;

    nlohmann::json getRaw() const;
  private:
    std::string _description;
    std::string _id;
    std::string _strategicIcon;

    std::shared_ptr<BlueprintGeneral> _general;
    std::shared_ptr<BlueprintDisplay> _display;
    std::unique_ptr<BlueprintPhysic > _physic ;

    nlohmann::json _raw;
  };
}