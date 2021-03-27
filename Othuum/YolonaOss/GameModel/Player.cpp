#include "Player.h"

namespace YolonaOss
{
  namespace GameModel
  {
    nlohmann::json Player::toJson() const {
      nlohmann::json result;
      result["Name"] = name;
      return result;
    }

    void Player::fromJson(nlohmann::json from) {
      name = from["Name"];
    }

    Vishala::BinaryPackage Player::toBinary() const {
      Vishala::BinaryPackage result;
      Vishala::BinaryPackage::val2bin(result, name);
      return result;
    }

    void Player::fromBinary(Vishala::BinaryPackage& data) {
      name = Vishala::BinaryPackage::bin2val<std::string>(data);
    }
  }
}