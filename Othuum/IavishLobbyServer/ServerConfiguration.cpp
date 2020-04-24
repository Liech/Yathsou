#include "ServerConfiguration.h"

#include <fstream>
#include <filesystem>

namespace Iavish {

  nlohmann::json ServerConfiguration::toJson() {
    nlohmann::json result;
    result["Port"] = port;
    return result;
  }

  void ServerConfiguration::fromJson(nlohmann::json from) {
    port = from["Port"];
  }

  Vishala::BinaryPackage ServerConfiguration::toBinary() {
    Vishala::BinaryPackage result;
    val2bin<int>(result,port);
    return result;
  }

  void ServerConfiguration::fromBinary(Vishala::BinaryPackage& data) {
    port = bin2val<int>(data);
  }
}