#include "InitializeCmd.h"

void InitializeCmd::_apply(Uyanah::Scene& t){
  t = data;
}

nlohmann::json InitializeCmd::toJson() const {
  return data.serializeJson();
}

void InitializeCmd::fromJson(nlohmann::json d) {
  data.fromJson(d);
}

Vishala::BinaryPackage InitializeCmd::toBinary() const {
  return data.toBinary();
}

void InitializeCmd::fromBinary(Vishala::BinaryPackage& msg) {
  data.fromBinary(msg);
}