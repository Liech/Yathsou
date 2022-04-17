#include "LiberalMessage.h"

#include "Core/Command.h"

namespace Vishala {
  nlohmann::json LiberalMessage::toJson() const {
    nlohmann::json result;
    int number = (int)type;
    result["Type"] = number;
    if (type == LiberalMessage::Type::Command || type == LiberalMessage::Type::Initialization) {
      result["Command"] = command->serializeJson();
    }
    if (type == LiberalMessage::Type::ClientReport || type == LiberalMessage::Type::Command)
      result["Tick"] = tick;

    return result;
  }

  void LiberalMessage::fromJson(nlohmann::json from) {
    int number = from["Type"];
    type = (LiberalMessage::Type)number;
    if (type == LiberalMessage::Type::Command || type == LiberalMessage::Type::Initialization) {
      command = Serialization::deserializeJsonCast<ICommand>(from["Command"]);
    }
    if (type == LiberalMessage::Type::ClientReport || type == LiberalMessage::Type::Command)
      tick = from["Tick"];
  }

  BinaryPackage LiberalMessage::toBinary() const {
    BinaryPackage result;
    int number = (int)type;
    BinaryPackage::val2bin<int>(result, number);
    if (type == LiberalMessage::Type::ClientReport || type == LiberalMessage::Type::Command)
      BinaryPackage::val2bin<size_t>(result, tick);
    if (type == LiberalMessage::Type::Command || type == LiberalMessage::Type::Initialization) {
      result.add(command->serialize());
    }      
    return result;
  }

  void LiberalMessage::fromBinary(BinaryPackage& data) {
    int number = BinaryPackage::bin2val<int>(data);
    type = (LiberalMessage::Type)number;
    if (type == LiberalMessage::Type::ClientReport || type == LiberalMessage::Type::Command)
      tick = BinaryPackage::bin2val<size_t>(data);
    if (type == LiberalMessage::Type::Command || type == LiberalMessage::Type::Initialization) {
      command = Serialization::deserializeCast<ICommand>(data);
    }
  }
}