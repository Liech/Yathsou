#include "OpenLobbyRequest.h"

namespace Vishala {
  OpenLobbyRequest::OpenLobbyRequest() {
    playerNumber = 0;
  }
  OpenLobbyRequest::OpenLobbyRequest(size_t number, Client2LobbyMessage req) {
    playerNumber = number;
    request = req;
  }


  BinaryPackage OpenLobbyRequest::toBinary()const {
    BinaryPackage result;    
    BinaryPackage::val2bin(result, playerNumber);
    result.add(request.toBinary());
    return result;
  }

  void OpenLobbyRequest::fromBinary(BinaryPackage& Package) {
    playerNumber = BinaryPackage::bin2val<size_t>(Package);
    request.fromBinary(Package);
  }

  nlohmann::json OpenLobbyRequest::toJson() const {
    nlohmann::json result;
    result["PlayerNumber"] = playerNumber;
    result["Request"] = request.toJson();   
    return result;
  }

  void OpenLobbyRequest::fromJson(nlohmann::json data) {
    playerNumber = data["PlayerNumber"];
    request.fromJson(data["Request"]);
  }
}