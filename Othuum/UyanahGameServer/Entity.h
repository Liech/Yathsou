#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Uyanah {
  class Component;

  class Entity : public Vishala::Serialization {
  public:
    virtual nlohmann::json          toJson()                            override;
    virtual void                    fromJson(nlohmann::json)            override;
    virtual Vishala::BinaryPackage  toBinary()                          override;
    virtual void                    fromBinary(Vishala::BinaryPackage&) override;

    std::vector<std::shared_ptr<Component>> components;
  };
}