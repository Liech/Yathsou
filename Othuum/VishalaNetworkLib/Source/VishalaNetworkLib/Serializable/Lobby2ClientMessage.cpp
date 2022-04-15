#include "Lobby2ClientMessage.h"

namespace Vishala {
  Lobby2ClientMessage::Lobby2ClientMessage() : nothing() {

  }

  Lobby2ClientMessage::~Lobby2ClientMessage() {

  }

  nlohmann::json Lobby2ClientMessage::toJson() const {
    nlohmann::json result;
    result["Type"] = (int)type;

    if (type == Type::Acknowledgment)
      result["Content"] = acknowledgment.toJson();
    else if (type == Type::Acknowledgment)
      result["Content"] = lobbyBriefing.toJson();
    else if (type == Type::LobbyUpdate)
      result["Content"] = lobbyUpdate.toJson();
    else if (type == Type::GameLobbyUpdate)
      result["Content"] = gameLobbyUpdate.toJson();
    else if(type != Type::GameClosed && type != Type::StartGame)
      throw std::runtime_error("Unkown Message Type");
    return result;
  }

  void Lobby2ClientMessage::fromJson(nlohmann::json from) {
    int number = from["Type"];
    type = (Type)number;
    if (type == Type::Acknowledgment)
      acknowledgment.fromJson(from["Content"]);
    else if (type == Type::Acknowledgment)
      lobbyBriefing.fromJson(from["Content"]);
    else if (type == Type::LobbyUpdate)
      lobbyUpdate.fromJson(from["Content"]);
    else if (type == Type::GameLobbyUpdate)
      gameLobbyUpdate.fromJson(from["Content"]);
    else if (type != Type::GameClosed && type != Type::StartGame)
      throw std::runtime_error("Unkown Message Type");
  }

  BinaryPackage Lobby2ClientMessage::toBinary()const {
    BinaryPackage result;
    int number = (int)type;
    BinaryPackage::val2bin<int>(result, number);
    if (type == Type::Acknowledgment)
      result.add(acknowledgment.toBinary());
    else if (type == Type::LobbyBriefing)
      result.add(lobbyBriefing.toBinary());
    else if (type == Type::LobbyUpdate)
      result.add(lobbyUpdate.toBinary());
    else if (type == Type::GameLobbyUpdate)
      result.add(gameLobbyUpdate.toBinary());
    else if (type != Type::GameClosed && type != Type::StartGame)
      throw std::runtime_error("Unkown Message Type");
    return result;
  }

  void Lobby2ClientMessage::fromBinary(BinaryPackage& data) {
    int number = BinaryPackage::bin2val<int>(data);
    type = (Type)number;
    if (type == Type::Acknowledgment)
      acknowledgment.fromBinary(data);
    else if (type == Type::LobbyBriefing)
      lobbyBriefing.fromBinary(data);
    else if (type == Type::LobbyUpdate)
      lobbyUpdate.fromBinary(data);
    else if (type == Type::GameLobbyUpdate)
      gameLobbyUpdate.fromBinary(data);
    else if (type != Type::GameClosed && type != Type::StartGame)
      throw std::runtime_error("Unkown Message Type");
  }
}