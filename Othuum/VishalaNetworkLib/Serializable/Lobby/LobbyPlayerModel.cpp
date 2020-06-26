#include "LobbyPlayerModel.h"

namespace Vishala {

  BinaryPackage LobbyPlayerModel::toBinary() {
    BinaryPackage result;
    int id_ = id;
    val2bin<int>        (result, id_  );
    val2bin<std::string>(result, name );
    arr2bin<int, 3>     (result, color);
    return result;
  }

  void LobbyPlayerModel::fromBinary(BinaryPackage& Package) {
    id    = bin2val<int>(Package);
    name  = bin2val<std::string>(Package);
    color = bin2arr<int,3>(Package);
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