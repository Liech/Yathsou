#include "Initialize.h"

#include "Scene.h"
#include "Components/Transform2D.h"


namespace Uyanah {
  namespace Commands {

    void Initialize::apply(Scene& s) {
      s = scene;
    }

    Vishala::BinaryPackage Initialize::toBinary()
    {
      return scene.toBinary();
    }

    void Initialize::fromBinary(Vishala::BinaryPackage& Package)
    {
      scene.fromBinary(Package);
    }

    nlohmann::json Initialize::toJson()
    {
      return scene.toJson();
    }

    void Initialize::fromJson(nlohmann::json input)
    {
      scene.fromJson(input);
    }
  }
}