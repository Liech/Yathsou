#pragma once

#include <map>
#include <string>
#include <set>

#include "VishalaNetworkLib/lib/json.hpp"
#include "IyathuumCoreLib/Singleton/Factory.h"

#include "BinaryPackage.h"

#define SERIALIZATION(TYPE, NAME)\
   static inline Vishala::Serialization::Registrator<TYPE> __Serialization___Registrator__{ NAME };

namespace Vishala {
  struct Serialization {
    virtual   const std::string Name() const = 0;    
    constexpr const size_t      ID()   const;

    virtual BinaryPackage  toBinary() const = 0;
    virtual void           fromBinary(BinaryPackage& Package) = 0;
    virtual nlohmann::json toJson() const = 0;
    virtual void           fromJson    (nlohmann::json) = 0;
            void           toJsonFile  (std::string filename);
            void           fromJsonFile(std::string filename);
            void           toBinFile   (std::string filename);
            void           fromBinFile (std::string filename); 

    BinaryPackage                         serialize() const;
    static std::shared_ptr<Serialization> deserialize(BinaryPackage& Package);
    nlohmann::json                        serializeJson() const;
    static std::shared_ptr<Serialization> deserializeJson(nlohmann::json);

    template<typename T>
    static std::shared_ptr<T> deserializeCast(BinaryPackage& Package) {
      return std::static_pointer_cast<T>(deserialize(Package));
    }

    template<typename T>
    static std::shared_ptr<T> deserializeJsonCast(nlohmann::json Package) {
      return std::static_pointer_cast<T>(deserializeJson(Package));
    }

  private:
    inline static std::map<size_t, std::string> id2name;
  public:
    template <typename X>
    class Registrator {
    public:
      Registrator(const std::string name) {
        Iyathuum::template Factory<Serialization>::template Register<X>(name, {});
        Serialization::id2name[create()->ID()] = create()->Name();
      }
    private:
      static std::shared_ptr<Serialization> create() {
        return std::static_pointer_cast<Serialization>(std::make_shared<X>());
      }
    };
  };
}