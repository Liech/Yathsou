#include "Key.h"

#include "Scene.h"
#include "Components/Transform2D.h"


namespace Uyanah {
  namespace Commands {

    void KeyCmd::apply(Scene& s) {
      auto transform = s.objects[0].getComponent<Components::Transform2D>("Transform2D");
      if (key == Iyathuum::Key::KEY_W)
        transform->velocity += glm::vec2(0, 1);
      if (key == Iyathuum::Key::KEY_S)
        transform->velocity += glm::vec2(0, -1);
      if (key == Iyathuum::Key::KEY_A)
        transform->velocity += glm::vec2(-1,0);
      if (key == Iyathuum::Key::KEY_D)
        transform->velocity += glm::vec2(1,0);
    }

    Vishala::BinaryPackage KeyCmd::toBinary()
    {
      Vishala::BinaryPackage result;
      int k = (int)key;
      Vishala::BinaryPackage::val2bin(result, k);
      int s = (int)status;
      Vishala::BinaryPackage::val2bin(result, s);
      return result;
    }

    void KeyCmd::fromBinary(Vishala::BinaryPackage& Package)
    {
      key    = (Iyathuum::Key      )Vishala::BinaryPackage::bin2val<int>(Package);
      status = (Iyathuum::KeyStatus)Vishala::BinaryPackage::bin2val<int>(Package);
    }

    nlohmann::json KeyCmd::toJson()
    {
      nlohmann::json result;
      result["Key"]    = (int)key   ;
      result["Status"] = (int)status;
      return result;
    }

    void KeyCmd::fromJson(nlohmann::json input)
    {
      key      = (Iyathuum::Key)      input["Key"];
      status   = (Iyathuum::KeyStatus)input["Status"];
      targetID =                      input["Target"];
    }
  }
}