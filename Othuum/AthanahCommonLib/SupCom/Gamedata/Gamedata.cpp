#include "Gamedata.h"

#include "SupComModelFactory.h"
#include "UiTextureFactory.h"
#include "BlueprintFactory.h"
#include "SkyboxFactory.h"

namespace Athanah {
  Gamedata::Gamedata(std::string supComPath, bool useSCDFiles) {
    std::string assetPath = "Data/";
    useSCDFiles = true;

    std::string modelSCD = supComPath + "/gamedata/units.scd";
    _model = std::make_unique<SupComModelFactory>(useSCDFiles ? modelSCD : assetPath + "units");

    std::string textureSCD = supComPath + "/gamedata/textures.scd";
    _icon = std::make_unique<UiTextureFactory>(useSCDFiles ? textureSCD : assetPath + "textures");

    std::string blueprintSCD = supComPath + "/gamedata/units.scd";
    _blueprint = std::make_unique<BlueprintFactory>(useSCDFiles ? blueprintSCD : assetPath + "units");

    std::string skyboxSCD = supComPath + "/gamedata/textures.scd";
    _skybox = std::make_unique<SkyboxFactory>(useSCDFiles ? skyboxSCD : assetPath + "textures");
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

  SkyboxFactory& Gamedata::skybox() {
    return *_skybox;
  }
}