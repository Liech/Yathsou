#include "NetworkGameSeedInput.h"

namespace Vishala {
  BinaryPackage NetworkGameSeedInput::toBinary() {
    BinaryPackage result;
    BinaryPackage::val2bin<int        >(result, ownPort);
    BinaryPackage::val2bin<int        >(result, numberOfChannels);

    int numberOfEntries = targets.size();
    BinaryPackage::val2bin<int>(result, numberOfEntries);
    for (int i = 0; i < numberOfEntries; i++) {
      BinaryPackage::val2bin<std::string>(result, targets[i].IP  );
      BinaryPackage::val2bin<int        >(result, targets[i].port);
    }    
    return result;
  }

  void NetworkGameSeedInput::fromBinary(BinaryPackage& Package) {
    ownPort = BinaryPackage::bin2val<int        >(Package);
    numberOfChannels = BinaryPackage::bin2val<int        >(Package);

    targets.clear();
    int numberOfEntries = BinaryPackage::bin2val<int>(Package);    
    for (int i = 0; i < numberOfEntries; i++){
      targets[i].IP   = BinaryPackage::bin2val<std::string>(Package);
      targets[i].port = BinaryPackage::bin2val<int        >(Package);
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