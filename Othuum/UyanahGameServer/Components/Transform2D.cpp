#include "Transform2D.h"


namespace Uyanah {
  namespace Components {
    //REGISTERGROUP(Component,Transform2D, "Transform2D");
    Vishala::BinaryPackage Transform2D::toBinary()const
    {
      Vishala::BinaryPackage result;
      Vishala::BinaryPackage::val2bin(result, position[0]);
      Vishala::BinaryPackage::val2bin(result, position[1]);
      return result;
    }

    void Transform2D::fromBinary(Vishala::BinaryPackage& Package)
    {
      position[0] = Vishala::BinaryPackage::bin2val<float>(Package);
      position[1] = Vishala::BinaryPackage::bin2val<float>(Package);
    }

    nlohmann::json Transform2D::toJson()const
    {
      nlohmann::json result;
      result["Position"] = { position[0],position[1] };
      return result;
    }

    void Transform2D::fromJson(nlohmann::json input)
    {
      position = glm::vec2(input["Position"][0], input["Position"][1]);
    }
  }
}