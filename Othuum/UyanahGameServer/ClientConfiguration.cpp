#include "ClientConfiguration.h"

#include <fstream>
#include <filesystem>

namespace Uyanah {

  nlohmann::json ClientConfiguration::toJson() {
    nlohmann::json result;
    result["ServerIP"] = serverIP;
    result["ServerPort"] = serverPort;
    result["MyPort"] = myPort;
    return result;
  }

  void ClientConfiguration::fromJson(nlohmann::json from) {
    serverIP   = from["ServerIP"];
    serverPort = from["ServerPort"];
    myPort     = from["MyPort"];
  }

  Vishala::BinaryPackage ClientConfiguration::toBinary() {
    Vishala::BinaryPackage result;
    Vishala::BinaryPackage::val2bin<std::string>(result, serverIP);
    Vishala::BinaryPackage::val2bin<int>(result, serverPort);
    Vishala::BinaryPackage::val2bin<int>(result, myPort);
    return result;
  }

  void ClientConfiguration::fromBinary(Vishala::BinaryPackage& data) {
    serverIP   = Vishala::BinaryPackage::bin2val<std::string>(data);
    serverPort = Vishala::BinaryPackage::bin2val<int>(data);
    myPort     = Vishala::BinaryPackage::bin2val<int>(data);
  }
}