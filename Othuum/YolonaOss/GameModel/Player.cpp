#include "Player.h"

namespace YolonaOss
{
  namespace GameModel
  {
    nlohmann::json Player::toJson() {
      nlohmann::json result;
      result["Name"] = name;
      return result;
    }

    void Player::fromJson(nlohmann::json from) {
      name = from["Name"];
    }

    Vishala::BinaryPackage Player::toBinary() {
      Vishala::BinaryPackage result;
      val2bin(result, name);
      return result;
    }

    void Player::fromBinary(Vishala::BinaryPackage& data) {
      name = bin2val<std::string>(data);
    }
  }
}