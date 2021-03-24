#include "Entity.h"

#include "VishalaNetworkLib/Core/BinaryPackage.h"
#include "Component.h"

namespace Uyanah {
  nlohmann::json Entity::toJson()
  {
    nlohmann::json arr = nlohmann::json::array();
    for (auto comp : components) {
      nlohmann::json d = comp.second->serializeJson();
      d["___ID___"] = comp.second->Name();
      arr.push_back(d);
    }
    nlohmann::json result;
    result["Components"] = arr;
    return result;
  }

  void Entity::fromJson(nlohmann::json input)
  {
    components.clear();
    for (auto comp : input["Components"]) {
      std::shared_ptr<Component> g = Component::deserializeJsonCast<Component>(comp);
      components[input["___ID___"]] = g;
    }
  }

  Vishala::BinaryPackage Entity::toBinary()
  {
    Vishala::BinaryPackage result;
    int numberOfComponents = components.size();
    Vishala::BinaryPackage::val2bin(result,numberOfComponents);
    for (auto comp : components)
      result.add(comp.second->serialize());
    return result;
  }

  void Entity::fromBinary(Vishala::BinaryPackage& input)
  {
    components.clear();
    int numberOfPackages = Vishala::BinaryPackage::bin2val<int>(input);
    for (int i = 0; i < numberOfPackages; i++) {
      auto c = Component::deserializeCast<Component>(input);
      components[c->Name()] = c;
    }
  }

  void Entity::addComponent(std::shared_ptr<Component> c) {
    if (components.count(c->Name()) != 0)
      throw std::runtime_error("Component already there");
    components[c->Name()] = c;
  }

  std::shared_ptr<Component> Entity::getComponent(std::string name) {
    if (components.count(name) == 0)
      return nullptr;
    else
      return components[name];
  }

  std::vector<std::shared_ptr<Component>> Entity::getComponents() {
    std::vector<std::shared_ptr<Component>> result;
    for (auto c : components)
      result.push_back(c.second);
    return result;
  }

}