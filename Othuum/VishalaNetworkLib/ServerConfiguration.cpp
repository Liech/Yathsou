#include "ServerConfiguration.h"

#include <fstream>
#include <filesystem>

namespace Vishala {

  nlohmann::json ServerConfiguration::toJson() {
    nlohmann::json result;
    result["Port"] = port;
    return result;
  }

  void ServerConfiguration::fromJson(nlohmann::json from) {
    port = from["Port"];
  }

  BinaryPackage ServerConfiguration::toBinary() {
    BinaryPackage result;
    val2bin<int>(result,port);
    return result;
  }

  void ServerConfiguration::fromBinary(BinaryPackage& data) {
    port = bin2val<int>(data);
  }
}