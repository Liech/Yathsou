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

  std::vector<unsigned char> Message::toBinary() {
    std::vector<unsigned char> result;
    val2bin<int>(result, playerID);
    val2bin<int>(result, message );
    return result;
  }

  void Message::fromBinary(std::vector<unsigned char> data, size_t position) {
    playerID = bin2val<int>(data, position);
    message  = bin2val<int>(data, position);
  }
}