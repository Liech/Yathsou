#include "CreateGameRequest.h"

namespace Vishala {
  nlohmann::json CreateGameRequest::toJson() {
    nlohmann::json result;
    result["GameName"] = gameName;
    return result;
  }

  void CreateGameRequest::fromJson(nlohmann::json from) {
    gameName = from["GameName"];
  }

  BinaryPackage CreateGameRequest::toBinary() {
    BinaryPackage result;
    val2bin<std::string>(result, gameName);
    return result;
  }

  void CreateGameRequest::fromBinary(BinaryPackage& data) {
    gameName = bin2val<std::string>(data);
  }
}