#include "Gamedata.h"

#include "SupComModelFactory.h"
#include "UiTextureFactory.h"
#include "BlueprintFactory.h"
#include "SkyboxFactory.h"
#include "AezeselFileIOLib/SupremeCommander/SCD.h"

namespace Athanah {
  Gamedata::Gamedata(std::string supComPath, bool useSCDFiles) {
    std::string assetPath = "Data/";
    useSCDFiles = true;

    std::string modelSCD = supComPath + "/gamedata/units.scd";
    std::shared_ptr<Aezesel::SCD> units = std::make_shared<Aezesel::SCD>(useSCDFiles ? modelSCD : assetPath + "units");
    std::string textureSCD = supComPath + "/gamedata/textures.scd";
    std::shared_ptr<Aezesel::SCD> textures = std::make_shared<Aezesel::SCD>(useSCDFiles ? textureSCD : assetPath + "textures");

    _icon      = std::make_unique<UiTextureFactory  >(textures);
    _skybox    = std::make_unique<SkyboxFactory     >(textures);
    _model     = std::make_unique<SupComModelFactory>(units   );
    _blueprint = std::make_unique<BlueprintFactory  >(units   );
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