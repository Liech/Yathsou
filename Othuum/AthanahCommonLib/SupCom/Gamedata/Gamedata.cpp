#include "Gamedata.h"

#include "SupComModelFactory.h"
#include "UiTextureFactory.h"
#include "BlueprintFactory.h"

namespace Athanah {
  Gamedata::Gamedata(std::string supComPath, bool useSCDFiles) {
    std::string assetPath = "Data/";

    std::string modelSCD = supComPath + "/gamedata/units.scd";
    _model = std::make_unique<SupComModelFactory>(useSCDFiles ? modelSCD : assetPath + "units");

    std::string textureSCD = supComPath + "/gamedata/textures.scd";
    _icon = std::make_unique<UiTextureFactory>(useSCDFiles ? modelSCD : assetPath);

    std::string blueprintSCD = supComPath + "/gamedata/units.scd";
    _blueprint = std::make_unique<BlueprintFactory>(useSCDFiles ? modelSCD : assetPath + "units");
  }

  BlueprintFactory& Gamedata::blueprint() {
    return *_blueprint;
  }

  SupComModelFactory& Gamedata::model() {
    return *_model;
  }

  UiTextureFactory& Gamedata::icon() {
    return *_icon;
  }

}