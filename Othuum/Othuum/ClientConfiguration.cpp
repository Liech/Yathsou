#include "ClientConfiguration.h"

nlohmann::json ClientConfiguration::toJson() {
  nlohmann::json result;
  result["PlayerName"] = playerName;
  result["Resolution"] = resolution;
  return result;
}

void ClientConfiguration::fromJson(nlohmann::json from) {
  playerName = from["PlayerName"];
  resolution = from["Resolution"];
}

Vishala::BinaryPackage ClientConfiguration::toBinary() {
  Vishala::BinaryPackage result;  
  val2bin<std::string>(result, playerName);
  arr2bin<int, 2>(result, resolution);
  return result;
}

void ClientConfiguration::fromBinary(Vishala::BinaryPackage& data) {
  playerName = bin2val<std::string>(data);
  resolution = bin2arr<int, 2>(data);
}