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
    
    void                                    addComponent(std::shared_ptr<Component>);
    std::shared_ptr<Component>              getComponent(std::string name);
    std::vector<std::shared_ptr<Component>> getComponents();

    template<typename T>
    std::shared_ptr<T> getComponent(std::string name) {
      return std::static_pointer_cast<T>(getComponent(name));
    }

  private:
    std::map<std::string,std::shared_ptr<Component>> components;
  };
}