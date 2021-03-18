#include "JoinGameRequest.h"

namespace Vishala {
  nlohmann::json JoinGameRequest::toJson() {
    nlohmann::json result;
    result["GameID"] = gameID;
    return result;
  }

  void JoinGameRequest::fromJson(nlohmann::json from) {
    gameID = from["GameID"];
  }

  BinaryPackage JoinGameRequest::toBinary() {
    BinaryPackage result;
    BinaryPackage::val2bin<int>(result, gameID);
    return result;
  }

  void JoinGameRequest::fromBinary(BinaryPackage& data) {
    gameID = BinaryPackage::bin2val<int>(data);
  }
}