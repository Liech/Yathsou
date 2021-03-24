#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"
#include "IyathuumCoreLib/Singleton/Factory.h"
#include "IyathuumCoreLib/Util/ConstExprHash.h"
#include <map>



namespace Vishala {
  
  template<typename T>
  class SerializationGroup : public Vishala::Serialization {
  public:
    static nlohmann::json _toJson (std::shared_ptr<T> input) {
      nlohmann::json result = input->toJson();
      result["___ID___"] = input->Name();
      return result;
    }

    static std::shared_ptr<T> _fromJson (nlohmann::json input) {
      auto result = std::static_pointer_cast<T>(Iyathuum::Factory<SerializationGroup<T>>::make(input["___ID___"]));
      result->fromJson(input);
      return result;
    }

    static Vishala::BinaryPackage _toBinary(std::shared_ptr<T> input) {
      Vishala::BinaryPackage result;
      size_t hash = input->ID();
      Vishala::BinaryPackage::val2bin(result, hash);
      result.add(input->toBinary());
      return result;
    }

    static std::shared_ptr<T> _fromBinary(Vishala::BinaryPackage& input) {
      size_t hash = Vishala::BinaryPackage::bin2val<size_t>(input);
      std::shared_ptr<T> result = std::static_pointer_cast<T>(Iyathuum::Factory<SerializationGroup<T>>::make(id2name[hash]));
      result->fromBinary(input);
      return result;
    }

    virtual constexpr const std::string Name() const = 0;
    constexpr const size_t              ID() const {
      return constexprHASH(Name());
    }

  private:
    inline static std::map<size_t, std::string> id2name;
  public:
    template <typename X>
    class Registrator {
    public:
      Registrator(const std::string name) {
        Iyathuum::template Factory<SerializationGroup<T>>::template Register<X>(name, {});
        SerializationGroup<T>::id2name[create()->ID()] = create()->Name();
      }
    private:
      static std::shared_ptr<SerializationGroup<T>> create() {
        return std::static_pointer_cast<SerializationGroup<T>>(std::make_shared<X>());
      }
    };
  };
}

#define REGISTERGROUP(Group,SpecificType,name)\
   static inline Vishala::SerializationGroup<Group>::Registrator<SpecificType> Registrator{ name };
