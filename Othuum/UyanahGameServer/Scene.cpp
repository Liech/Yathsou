#include "Scene.h"
#include "VishalaNetworkLib/Core/BinaryPackage.h"

namespace Uyanah {
  Vishala::BinaryPackage Scene::toBinary()
  {
    Vishala::BinaryPackage result;
    int numberOfObjects = objects.size();
    Vishala::BinaryPackage::val2bin(result,numberOfObjects);
    for (auto obj : objects)
      result.add(obj.toBinary());
    return result;
  }

  void Scene::fromBinary(Vishala::BinaryPackage& Package)
  {
    objects.clear();
    int numberOfObjects = Vishala::BinaryPackage::bin2val<int>(Package);
    for (int i = 0; i < numberOfObjects; i++) {
      Entity e;
      e.fromBinary(Package);
      objects.push_back(e);
    }
  }

  nlohmann::json Scene::toJson()
  {
    nlohmann::json arr = nlohmann::json::array();
    for (auto obj : objects) {
      nlohmann::json d = obj.toJson();
      arr.push_back(d);
    }
    nlohmann::json result;
    result["Objects"] = arr;
    return result;
  }

  void Scene::fromJson(nlohmann::json input)
  {
    objects.clear();
    for (auto comp : input["Objects"]) {
      Entity g;
      g.fromJson(comp);
      objects.push_back(g);
    }
  }
}