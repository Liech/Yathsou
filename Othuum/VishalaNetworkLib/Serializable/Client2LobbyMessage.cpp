#include "Client2LobbyMessage.h"

namespace Vishala {
  Client2LobbyMessage::Client2LobbyMessage() : nothing() {

  }

  Client2LobbyMessage::Client2LobbyMessage(const Client2LobbyMessage& req) {
    type = req.type;
    if (type == Type::CreateGame)
      createGame = req.createGame;
    else if (type == Type::JoinGame)
      joinGame = req.joinGame;
  }

  Client2LobbyMessage::~Client2LobbyMessage() {
    
  }

  nlohmann::json Client2LobbyMessage::toJson() {
    nlohmann::json result;
    result["Type"] = (int)type;
    
    if (type == Type::CreateGame)
      result["Content"] = createGame.toJson();
    else if (type == Type::CreateGame)
      result["Content"] = joinGame.toJson();
    else if (type != Type::LeaveGame && type != Type::LobbyRefresh && type != Type::StartGame)
      throw std::runtime_error("Unkown Message Type");
    return result;
  }

  void Client2LobbyMessage::fromJson(nlohmann::json from) {
    int number = from["Type"];
    type = (Type)number;
    if (type == Type::CreateGame)
      createGame.fromJson(from["Content"]);
    else if (type == Type::JoinGame)
      joinGame.fromJson(from["Content"]);
    else if (type != Type::LeaveGame && type != Type::LobbyRefresh && type != Type::StartGame)
      throw std::runtime_error("Unkown Message Type");
  }

  BinaryPackage Client2LobbyMessage::toBinary() {
    BinaryPackage result;
    int number = (int)type;
    val2bin<int>(result, number);
    if (type == Type::CreateGame)
      result.add(createGame.toBinary());
    else if (type == Type::JoinGame)
      result.add(joinGame.toBinary());
    else if (type != Type::LeaveGame && type != Type::LobbyRefresh && type != Type::LobbyRefresh && type != Type::StartGame)
      throw std::runtime_error("Unkown Message Type");
    return result;
  }

  void Client2LobbyMessage::fromBinary(BinaryPackage& data) {
    int number = bin2val<int>(data);
    type = (Type)number;
    if (type == Type::CreateGame)
      createGame.fromBinary(data);
    else if (type == Type::JoinGame)
      joinGame.fromBinary(data);
    else if (type != Type::LeaveGame && type != Type::LobbyRefresh && type != Type::StartGame)
      throw std::runtime_error("Unkown Message Type");
  }
}