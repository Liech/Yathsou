#include "Config.h"

namespace Superb {
  nlohmann::json Config::toJson() const {
    nlohmann::json result;
    result["ScreenWidth"] = ScreenWidth;
    result["ScreenHeight"] = ScreenHeight;
    result["SupComPath"] = SupComPath;
    result["useSCDFiles"] = useSCDFiles;
    result["CameraPos"]    = std::vector<float>{ CameraPos   [0], CameraPos   [1], CameraPos   [2]};
    result["CameraTarget"] = std::vector<float>{ CameraTarget[0], CameraTarget[1], CameraTarget[2]};    
    return result;
  }

  void Config::fromJson(nlohmann::json from) {
    ScreenWidth  = from["ScreenWidth"];
    ScreenHeight = from["ScreenHeight"];
    SupComPath   = from["SupComPath"];
    useSCDFiles  = from["useSCDFiles"];
    CameraPos    = glm::vec3(from["CameraPos"][0], from["CameraPos"][1], from["CameraPos"][2]);
    CameraTarget = glm::vec3(from["CameraTarget"][0], from["CameraTarget"][1], from["CameraTarget"][2]);
  }

  Vishala::BinaryPackage Config::toBinary()const {
    Vishala::BinaryPackage result;
    Vishala::BinaryPackage::val2bin<int        >(result, ScreenWidth    );
    Vishala::BinaryPackage::val2bin<int        >(result, ScreenHeight   );
    Vishala::BinaryPackage::val2bin<std::string>(result, SupComPath     );
    Vishala::BinaryPackage::val2bin<bool       >(result, useSCDFiles    );
    Vishala::BinaryPackage::val2bin<float      >(result, CameraPos[0]   );
    Vishala::BinaryPackage::val2bin<float      >(result, CameraPos[1]   );
    Vishala::BinaryPackage::val2bin<float      >(result, CameraPos[2]   );
    Vishala::BinaryPackage::val2bin<float      >(result, CameraTarget[0]);
    Vishala::BinaryPackage::val2bin<float      >(result, CameraTarget[1]);
    Vishala::BinaryPackage::val2bin<float      >(result, CameraTarget[2]);
    return result;
  }

  void Config::fromBinary(Vishala::BinaryPackage& data) {
    ScreenWidth     = Vishala::BinaryPackage::bin2val<int        >(data);
    ScreenHeight    = Vishala::BinaryPackage::bin2val<int        >(data);
    SupComPath      = Vishala::BinaryPackage::bin2val<std::string>(data);
    useSCDFiles     = Vishala::BinaryPackage::bin2val<bool       >(data);
    CameraPos[0]    = Vishala::BinaryPackage::bin2val<float      >(data);
    CameraPos[1]    = Vishala::BinaryPackage::bin2val<float      >(data);
    CameraPos[2]    = Vishala::BinaryPackage::bin2val<float      >(data);
    CameraTarget[0] = Vishala::BinaryPackage::bin2val<float      >(data);
    CameraTarget[1] = Vishala::BinaryPackage::bin2val<float      >(data);
    CameraTarget[2] = Vishala::BinaryPackage::bin2val<float      >(data);
  }
}