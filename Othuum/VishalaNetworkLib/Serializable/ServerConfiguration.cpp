#include "ServerConfiguration.h"

#include <fstream>
#include <filesystem>

namespace Vishala {

  nlohmann::json ServerConfiguration::toJson() {
    nlohmann::json result;
    result["WelcomePort"] = welcomePort;
    result["PortRange"]   = portRange;
    return result;
  }

  void ServerConfiguration::fromJson(nlohmann::json from) {
    welcomePort = from["WelcomePort"];
    portRange   = from["PortRange"];
  }

  BinaryPackage ServerConfiguration::toBinary() {
    BinaryPackage result;
    val2bin<int>(result, welcomePort);
    arr2bin<int>(result, portRange);
    return result;
  }

  void ServerConfiguration::fromBinary(BinaryPackage& data) {
    welcomePort = bin2val<int>(data);
    portRange   = bin2arr<int,2>(data);
  }
}