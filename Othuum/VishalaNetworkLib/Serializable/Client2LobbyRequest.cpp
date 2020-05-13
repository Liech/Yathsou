#include "Client2LobbyRequest.h"

namespace Vishala {
  Client2LobbyRequest::Client2LobbyRequest() : nothing() {

  }

  Client2LobbyRequest::Client2LobbyRequest(const Client2LobbyRequest& req) {
    type = req.type;
    if (type == Type::CreateGame)
      createGame = req.createGame;
  }

  Client2LobbyRequest::~Client2LobbyRequest() {
    
  }

  nlohmann::json Client2LobbyRequest::toJson() {
    nlohmann::json result;
    result["Type"] = (int)type;
    
    if (type == Type::CreateGame)
      result["Content"] = createGame.toJson();
    else
      throw std::runtime_error("Unkown Message Type");
    return result;
  }

  void Client2LobbyRequest::fromJson(nlohmann::json from) {
    int number = from["Type"];
    type = (Type)number;
    if (type == Type::CreateGame)
      createGame.fromJson(from["Content"]);
    else
      throw std::runtime_error("Unkown Message Type");
  }

  BinaryPackage Client2LobbyRequest::toBinary() {
    BinaryPackage result;
    int number = (int)type;
    val2bin<int>(result, number);
    if (type == Type::CreateGame)
      result.add(createGame.toBinary());
    else
      throw std::runtime_error("Unkown Message Type");
    return result;
  }

  void Client2LobbyRequest::fromBinary(BinaryPackage& data) {
    int number = bin2val<int>(data);
    type = (Type)number;
    if (type == Type::CreateGame)
      createGame.fromBinary(data);
    else
      throw std::runtime_error("Unkown Message Type");
  }
}