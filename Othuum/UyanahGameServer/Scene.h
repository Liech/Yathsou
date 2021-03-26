#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"
#include "Entity.h"

namespace Uyanah {
  class Scene : public Vishala::Serialization {
  public:
    const std::string Name() const override { return "Scene"; }

    void update();

    std::vector<Entity> objects;

    virtual Vishala::BinaryPackage toBinary()                                  override;
    virtual void                   fromBinary(Vishala::BinaryPackage& Package) override;
    virtual nlohmann::json         toJson()                                    override;
    virtual void                   fromJson(nlohmann::json)                    override;
  };
}