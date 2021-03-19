#include "Entity.h"

#include "VishalaNetworkLib/Core/BinaryPackage.h"

namespace Uyanah {
  nlohmann::json Entity::toJson()
  {
    return nlohmann::json();
  }

  void Entity::fromJson(nlohmann::json)
  {
  }

  Vishala::BinaryPackage Entity::toBinary()
  {
    return Vishala::BinaryPackage();
  }

  void Entity::fromBinary(Vishala::BinaryPackage&)
  {
  }
}