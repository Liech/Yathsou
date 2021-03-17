#include "CreateGameRequest.h"

namespace Vishala {
  nlohmann::json CreateGameRequest::toJson() {
    nlohmann::json result;
    result["GameName"]   = gameName;
    result["ServerPort"] = serverPort;
    return result;
  }

  void CreateGameRequest::fromJson(nlohmann::json from) {
    gameName   = from["GameName"];
    serverPort = from["ServerPort"];
  }

  BinaryPackage CreateGameRequest::toBinary() {
    BinaryPackage result;
    val2bin<std::string>(result, gameName);
    val2bin<int>        (result, serverPort);
    return result;
  }

  void CreateGameRequest::fromBinary(BinaryPackage& data) {
    gameName   = bin2val<std::string>(data);
    serverPort = bin2val<int>(data);
  }
}