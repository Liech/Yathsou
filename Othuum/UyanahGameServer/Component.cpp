#include "Component.h"

#include "IyathuumCoreLib/Util/ConstExprHash.h"

namespace Uyanah {
  constexpr const size_t Component::ComponentID() const {
    return constexprHASH(ComponentName());
  }

  nlohmann::json Component::factory_toJson(std::shared_ptr<Component> comp) {
    nlohmann::json result = comp->toJson();
    result["___ComponentID___"] = comp->ComponentName();     
    return result;
  }

  std::shared_ptr<Component> Component::factory_fromJson(nlohmann::json input) {
    auto result = Iyathuum::Factory<Component>::make(input["___ComponentID___"]);
    result->fromJson(input);
    return result;
  }

  Vishala::BinaryPackage Component::factory_toBinary(std::shared_ptr<Component> comp) {
    Vishala::BinaryPackage result;
    size_t hash = comp->ComponentID();
    Vishala::BinaryPackage::val2bin(result, hash);
    result.add(comp->toBinary());
    return result;
  }

  std::shared_ptr<Component> Component::factory_fromBinary(Vishala::BinaryPackage& input) {
    size_t hash = Vishala::BinaryPackage::bin2val<size_t>(input);
    auto result = Iyathuum::Factory<Component>::make(id2name[hash]);
    result->fromBinary(input);
    return result;
  }

}