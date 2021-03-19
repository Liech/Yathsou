#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"
#include <map>

#define REGISTERCOMPONENT(SpecificType,Name)\
   static inline Component::Registrator<SpecificType> Registrator{ Name };


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
    inline static std::map<int, std::string> id2name;


    template <typename T>
    class Registrator {
    public:
      Registrator(const std::string name) {
        //Iyathuum::Factory<Component>::Register<T>();
        Component::id2name.insert(create()->ComponentID(), create()->ComponentName());
      }
    private:
      static std::shared_ptr<Component> create() {
        return std::static_pointer_cast<Component>(std::make_shared<T>());
      }
    };
  };
}