#include "Key.h"

#include "Scene.h"

namespace Uyanah {
  namespace Commands {
    REGISTERGROUP(Command, Commands::Key, "Key");

    void Key::apply(Scene& s) {
      
    }

    Vishala::BinaryPackage Key::toBinary()
    {
      Vishala::BinaryPackage result;
      int k = (int)key;
      Vishala::BinaryPackage::val2bin(result, k);
      int s = (int)status;
      Vishala::BinaryPackage::val2bin(result, s);
      return result;
    }

    void Key::fromBinary(Vishala::BinaryPackage& Package)
    {
      key    = (Iyathuum::Key      )Vishala::BinaryPackage::bin2val<int>(Package);
      status = (Iyathuum::KeyStatus)Vishala::BinaryPackage::bin2val<int>(Package);
    }

    nlohmann::json Key::toJson()
    {
      nlohmann::json result;
      result["Key"]    = (int)key   ;
      result["Status"] = (int)status;
      return result;
    }

    void Key::fromJson(nlohmann::json input)
    {
      key      = (Iyathuum::Key)      input["Key"];
      status   = (Iyathuum::KeyStatus)input["Status"];
      targetID =                      input["Target"];
    }
  }
}