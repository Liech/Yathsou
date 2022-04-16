#include "UpdateScene.h"

#include "Scene.h"
#include "Components/Transform2D.h"


namespace Uyanah {
  namespace Commands {
    void UpdateScene::_apply(Scene& s) {
      s.update();
    }

    Vishala::BinaryPackage UpdateScene::toBinary()const
    {
      Vishala::BinaryPackage result;
      return result;
    }

    void UpdateScene::fromBinary(Vishala::BinaryPackage& Package)
    {
    }

    nlohmann::json UpdateScene::toJson()const
    {
      nlohmann::json result;
      return result;
    }

    void UpdateScene::fromJson(nlohmann::json input)
    {
    }
  }
}