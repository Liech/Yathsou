#include "DedicatedServerConfiguration.h"

#include <fstream>
#include <filesystem>

namespace Uyanah {

  nlohmann::json DedicatedServerConfiguration::toJson()const {
    nlohmann::json result;
    result["WelcomePort"] = welcomePort;
    return result;
  }

  void DedicatedServerConfiguration::fromJson(nlohmann::json from) {
    welcomePort = from["WelcomePort"];
  }

  Vishala::BinaryPackage DedicatedServerConfiguration::toBinary()const {
    Vishala::BinaryPackage result;
    Vishala::BinaryPackage::val2bin<int>(result, welcomePort);
    return result;
  }

  void DedicatedServerConfiguration::fromBinary(Vishala::BinaryPackage& data) {
    welcomePort = Vishala::BinaryPackage::bin2val<int>(data);
  }
}