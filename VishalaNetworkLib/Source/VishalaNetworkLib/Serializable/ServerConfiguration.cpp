#include "ServerConfiguration.h"

#include <fstream>
#include <filesystem>

namespace Vishala {

  nlohmann::json ServerConfiguration::toJson()const {
    nlohmann::json result;
    result["WelcomePort"] = welcomePort;
    result["PortRange"]   = portRange;
    return result;
  }

  void ServerConfiguration::fromJson(nlohmann::json from) {
    welcomePort = from["WelcomePort"];
    portRange   = from["PortRange"];
  }

  BinaryPackage ServerConfiguration::toBinary()const {
    BinaryPackage result;
    BinaryPackage::val2bin<int>(result, welcomePort);
    BinaryPackage::arr2bin<int>(result, portRange);
    return result;
  }

  void ServerConfiguration::fromBinary(BinaryPackage& data) {
    welcomePort = BinaryPackage::bin2val<int>(data);
    portRange   = BinaryPackage::bin2arr<int,2>(data);
  }
}