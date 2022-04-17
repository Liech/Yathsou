#include "Gamedata.h"

#include <iostream>

#include "SupComModelFactory.h"
#include "UiTextureFactory.h"
#include "BlueprintFactory.h"
#include "SkyboxFactory.h"
#include "AezeselFileIOLib/SupremeCommander/SCD.h"

namespace Athanah {
  Gamedata::Gamedata(std::string supComPath, bool useSCDFiles) {
    std::string assetPath = "Data/";

    std::cout << "Loading Gamedata:" << std::endl;
    
    if (useSCDFiles)
    {
        std::cout << "Loading Data from SCD files..." << std::endl;
        std::cout << "Hint: " << std::endl;
        std::cout << "  Loading times are faster when extracting SCD files with 7z in to the Data Folder" << std::endl;
        std::cout << "  SCD File Location: Steam\\steamapps\\common\\Supreme Commander Forged Alliance\\gamedata" << std::endl;
    }
    std::cout << "...Loading Units Archive" << std::endl;
    std::string modelSCD = supComPath + "/gamedata/units.scd";
    _units = std::make_shared<Aezesel::SCD>(useSCDFiles ? modelSCD : assetPath + "units");
    _scdMap["units"] = _units;

    std::cout << "...Loading Textures Archive" << std::endl;
    std::string textureSCD = supComPath + "/gamedata/textures.scd";
    _textures = std::make_shared<Aezesel::SCD>(useSCDFiles ? textureSCD : assetPath + "textures");
    _scdMap["textures"] = _textures;

    std::cout << "...Loading Env Archive" << std::endl;
    std::string envSCD = supComPath + "/gamedata/env.scd";
    _env = std::make_shared<Aezesel::SCD>(useSCDFiles ? envSCD : assetPath + "env");
    _scdMap["env"] = _env;

    std::cout << "...Loading UI Factory" << std::endl;
    _icon      = std::make_unique<UiTextureFactory  >(_textures);
    std::cout << "...Loading Skybox Factory" << std::endl;
    _skybox    = std::make_unique<SkyboxFactory     >(_textures);
    std::cout << "...Loading Model Factory" << std::endl;
    _model     = std::make_unique<SupComModelFactory>(_units   );
    std::cout << "...Loading Blueprint Factory" << std::endl;
    _blueprint = std::make_unique<BlueprintFactory  >(_units   );
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

  std::vector<unsigned char> Gamedata::loadBinary(const std::string& path) {
    std::string p = path;
    std::replace(p.begin(), p.end(), '\\', '/');
    size_t firstSlash = path.find_first_of('/');
    std::string key = p.substr(0, firstSlash);
    std::shared_ptr<Aezesel::SCD> archive = _scdMap[key];
    std::string archivePath = p.substr(firstSlash + 1);
    return archive->loadBinaryFile(archivePath);
  }

}