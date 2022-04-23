#pragma once

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <set>

#include "AthanahCommonLib/SupCom/SupComEnums.h"

namespace Athanah {
  class BlueprintGeneral;
  class BlueprintDisplay;
  class BlueprintPhysic;

  class Blueprint {
  public:
    Blueprint(std::string id,  const nlohmann::json& input);
    Blueprint(const std::string id);
    virtual ~Blueprint() = default;

    std::string       strategicIcon()           const;
    std::string       description()             const;
    BlueprintGeneral& general()                 const;
    BlueprintDisplay& display()                 const;
    BlueprintPhysic&  physic()                  const;
    glm::vec3         size()                    const;
    glm::vec3         selectionSize()           const;
    TechLevel         techLevel()               const;
    bool              hasCategory(UnitCategory) const;
    bool              invalid()                 const;

    const std::set<UnitCategory>& categories()         const;

    nlohmann::json getRaw() const;
  private:
    void readSize(const nlohmann::json& input);
    void readCategories(const nlohmann::json& input);

    std::string _description  ;
    std::string _id           ;
    std::string _strategicIcon;
    glm::vec3   _selectionSize;
    glm::vec3   _size         ;
    bool        _invalid      = false;

    std::shared_ptr<BlueprintGeneral> _general;
    std::shared_ptr<BlueprintDisplay> _display;
    std::shared_ptr<BlueprintPhysic > _physic ;
    std::set<UnitCategory>            _categories;

    nlohmann::json _raw;
  };
}