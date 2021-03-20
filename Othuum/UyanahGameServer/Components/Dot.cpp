#include "Dot.h"

namespace Uyanah {
  namespace Components {
    REGISTERCOMPONENT(Dot, "Dot");

    Vishala::BinaryPackage Dot::toBinary()
    {
      Vishala::BinaryPackage result;
      Vishala::BinaryPackage::val2bin(result, color[0]);
      Vishala::BinaryPackage::val2bin(result, color[1]);
      Vishala::BinaryPackage::val2bin(result, color[2]);
      Vishala::BinaryPackage::val2bin(result, color[3]);
      return result;
    }

    void Dot::fromBinary(Vishala::BinaryPackage& Package)
    {
      color[0] = Vishala::BinaryPackage::bin2val<char>(Package);
      color[1] = Vishala::BinaryPackage::bin2val<char>(Package);
      color[2] = Vishala::BinaryPackage::bin2val<char>(Package);
      color[3] = Vishala::BinaryPackage::bin2val<char>(Package);
    }

    nlohmann::json Dot::toJson()
    {
      nlohmann::json result;
      result["Color"] = { color[0],color[1],color[2],color[3] };
      return result;
    }

    void Dot::fromJson(nlohmann::json input)
    {
      color[0] = input["Color"][0];
      color[1] = input["Color"][1];
      color[2] = input["Color"][2];
      color[3] = input["Color"][3];
    }
  }
}