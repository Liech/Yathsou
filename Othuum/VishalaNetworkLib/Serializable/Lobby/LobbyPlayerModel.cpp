#include "LobbyPlayerModel.h"

namespace Vishala {

  BinaryPackage LobbyPlayerModel::toBinary() {
    BinaryPackage result;
    int id_ = id;
    BinaryPackage::val2bin<int>        (result, id_  );
    BinaryPackage::val2bin<std::string>(result, name );
    BinaryPackage::arr2bin<int, 3>     (result, color);
    return result;
  }

  void LobbyPlayerModel::fromBinary(BinaryPackage& Package) {
    id    = BinaryPackage::bin2val<int>(Package);
    name  = BinaryPackage::bin2val<std::string>(Package);
    color = BinaryPackage::bin2arr<int,3>(Package);
  }

  nlohmann::json LobbyPlayerModel::toJson() {
    nlohmann::json result;
    result["ID"]    = id;
    result["Color"] = color;
    result["Name"]  = name;
    return result;
  }

  void LobbyPlayerModel::fromJson(nlohmann::json data) {
    name  = data["Name"];
    color = data["Color"];
    id    = data["ID"];
  }
}