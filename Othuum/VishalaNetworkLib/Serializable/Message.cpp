#include "Message.h"

namespace Vishala {
  nlohmann::json Message::toJson() {
    nlohmann::json result;
    result["playerID"] = playerID;
    result["message"]  = message ;
    return result;
  }

  void Message::fromJson(nlohmann::json from) {
    playerID = from["playerID"];
    message  = from["message"] ;
  }

  BinaryPackage Message::toBinary() {
    BinaryPackage result;
    val2bin<int>(result, playerID);
    val2bin<int>(result, message );
    return result;
  }

  void Message::fromBinary(BinaryPackage& data) {
    playerID = bin2val<int>(data);
    message  = bin2val<int>(data);
  }
}