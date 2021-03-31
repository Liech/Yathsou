#include "InitializeCmd.h"

namespace Vishala {  
  void InitializeCmd::apply(Serialization& t){
    t = *data;
  }

  nlohmann::json InitializeCmd::toJson() const {
    return data->serializeJson();
  }

  void InitializeCmd::fromJson(nlohmann::json d) {
    data = deserializeJson(d);
  }

  BinaryPackage InitializeCmd::toBinary() const {
    return data->serialize();
  }

  void InitializeCmd::fromBinary(BinaryPackage& msg) {
    data = Vishala::Serialization::deserialize(msg);
  }
}