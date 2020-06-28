#include "NetworkGameSeedInput.h"

namespace Vishala {
  BinaryPackage NetworkGameSeedInput::toBinary() {
    BinaryPackage result;
    val2bin<int        >(result, ownPort);
    val2bin<int        >(result, numberOfChannels);

    int numberOfEntries = targets.size();
    val2bin<int>(result, numberOfEntries);
    for (int i = 0; i < numberOfEntries; i++) {
      val2bin<std::string>(result, targets[i].IP  );
      val2bin<int        >(result, targets[i].port);
    }    
    return result;
  }

  void NetworkGameSeedInput::fromBinary(BinaryPackage& Package) {
    ownPort = bin2val<int        >(Package);
    numberOfChannels = bin2val<int        >(Package);

    targets.clear();
    int numberOfEntries = bin2val<int>(Package);    
    for (int i = 0; i < numberOfEntries; i++){
      targets[i].IP   = bin2val<std::string>(Package);
      targets[i].port = bin2val<int        >(Package);
    }
  }

  nlohmann::json NetworkGameSeedInput::toJson() {
    nlohmann::json result;
    
    result["OwnPort"] = ownPort;
    result["NumberOfChannels"] = numberOfChannels;

    nlohmann::json arr = nlohmann::json::array();

    for (auto target : targets) {
      nlohmann::json d;
      d["IP"] = target.IP;
      d["Port"] = target.port;
      arr.push_back(d);
    }
    result["Targets"] = arr;
    return result;
  }

  void NetworkGameSeedInput::fromJson(nlohmann::json data) {
    ownPort          = data["OwnPort"];
    numberOfChannels = data["NumberOfChannels"];

    targets.clear();
    for (auto target : data["Targets"]) {
      Address a;
      a.IP = target["IP"];
      a.port = target["Port"];
      targets.push_back(a);
    }
  }
}