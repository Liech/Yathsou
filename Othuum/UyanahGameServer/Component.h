#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"
#include "IyathuumCoreLib/Singleton/Factory.h"
#include <map>

#define REGISTERCOMPONENT(SpecificType,name)\
   static inline Uyanah::Component::Registrator<SpecificType> Registrator{ name };


namespace Uyanah {
  class Component : public Vishala::Serialization {
  public:
    static nlohmann::json             factory_toJson(std::shared_ptr<Component>)  ;
    static std::shared_ptr<Component> factory_fromJson(nlohmann::json)            ;
    static Vishala::BinaryPackage     factory_toBinary(std::shared_ptr<Component>);
    static std::shared_ptr<Component> factory_fromBinary(Vishala::BinaryPackage&) ;

    virtual constexpr const std::string ComponentName() const = 0;
            constexpr const size_t      ComponentID() const;

  private:
    inline static std::map<size_t, std::string> id2name;


  public:
    template <typename T>
    class Registrator {
    public:
      Registrator(const std::string name) {
        Iyathuum::template Factory<Component>::template Register<T>(name, {});
        Component::id2name[create()->ComponentID()] = create()->ComponentName();
      }
    private:
      static std::shared_ptr<Component> create() {
        return std::static_pointer_cast<Component>(std::make_shared<T>());
      }
    };
  };
}