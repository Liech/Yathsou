#include "CreateGameRequest.h"

namespace Vishala {
  nlohmann::json CreateGameRequest::toJson() const {
    nlohmann::json result;
    result["GameName"]   = gameName;
    result["ServerPort"] = serverPort;
    return result;
  }

  void CreateGameRequest::fromJson(nlohmann::json from) {
    gameName   = from["GameName"];
    serverPort = from["ServerPort"];
  }

  BinaryPackage CreateGameRequest::toBinary() const {
    BinaryPackage result;
    BinaryPackage::val2bin<std::string>(result, gameName);
    BinaryPackage::val2bin<int>        (result, serverPort);
    return result;
  }

  void CreateGameRequest::fromBinary(BinaryPackage& data) {
    gameName   = BinaryPackage::bin2val<std::string>(data);
    serverPort = BinaryPackage::bin2val<int>(data);
  }
}