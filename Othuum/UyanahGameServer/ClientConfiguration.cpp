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
    val2bin<std::string>(result, serverIP);
    val2bin<int>(result, serverPort);
    val2bin<int>(result, myPort);
    return result;
  }

  void ClientConfiguration::fromBinary(Vishala::BinaryPackage& data) {
    serverIP   = bin2val<std::string>(data);
    serverPort = bin2val<int>(data);
    myPort     = bin2val<int>(data);
  }
}