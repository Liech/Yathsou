#include "Entity.h"

#include "VishalaNetworkLib/Core/BinaryPackage.h"
#include "Component.h"

namespace Uyanah {
  nlohmann::json Entity::toJson()
  {
    nlohmann::json arr = nlohmann::json::array();
    for (auto comp : components) {
      nlohmann::json d = Component::_toJson(comp);
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
      std::shared_ptr<Component> g = Component::_fromJson(comp);
      components.push_back(g);
    }
  }

  Vishala::BinaryPackage Entity::toBinary()
  {
    Vishala::BinaryPackage result;
    int numberOfComponents = components.size();
    Vishala::BinaryPackage::val2bin(result,numberOfComponents);
    for (auto comp : components)
      result.add(Component::_toBinary(comp));
    return result;
  }

  void Entity::fromBinary(Vishala::BinaryPackage& input)
  {
    components.clear();
    int numberOfPackages = Vishala::BinaryPackage::bin2val<int>(input);
    for (int i = 0; i < numberOfPackages; i++)
      components.push_back(Component::_fromBinary(input));
  }
}