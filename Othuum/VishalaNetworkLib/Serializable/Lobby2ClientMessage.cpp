#include "Lobby2ClientMessage.h"

namespace Vishala {
  Lobby2ClientMessage::Lobby2ClientMessage() : nothing() {

  }

  Lobby2ClientMessage::Lobby2ClientMessage(const Lobby2ClientMessage& req) {
    type = req.type;
    if (type == Type::Acknowledgment)
      acknowledgment = req.acknowledgment;
  }

  Lobby2ClientMessage::~Lobby2ClientMessage() {

  }

  nlohmann::json Lobby2ClientMessage::toJson() {
    nlohmann::json result;
    result["Type"] = (int)type;

    if (type == Type::Acknowledgment)
      result["Content"] = acknowledgment.toJson();
    else
      throw std::runtime_error("Unkown Message Type");
    return result;
  }

  void Lobby2ClientMessage::fromJson(nlohmann::json from) {
    int number = from["Type"];
    type = (Type)number;
    if (type == Type::Acknowledgment)
      acknowledgment.fromJson(from["Content"]);
    else
      throw std::runtime_error("Unkown Message Type");
  }

  BinaryPackage Lobby2ClientMessage::toBinary() {
    BinaryPackage result;
    int number = (int)type;
    val2bin<int>(result, number);
    if (type == Type::Acknowledgment)
      result.add(acknowledgment.toBinary());
    else
      throw std::runtime_error("Unkown Message Type");
    return result;
  }

  void Lobby2ClientMessage::fromBinary(BinaryPackage& data) {
    int number = bin2val<int>(data);
    type = (Type)number;
    if (type == Type::Acknowledgment)
      acknowledgment.fromBinary(data);
    else
      throw std::runtime_error("Unkown Message Type");
  }
}