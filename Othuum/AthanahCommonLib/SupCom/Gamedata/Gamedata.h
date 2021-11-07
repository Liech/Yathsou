#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace Aezesel {
  class SCD;
}

namespace Athanah {
  class SupComModelFactory;
  class UiTextureFactory;
  class BlueprintFactory;
  class SkyboxFactory;

  class Gamedata {
  public:
    Gamedata(std::string supComPath, bool useSCDFiles);
    virtual ~Gamedata() = default;

    SupComModelFactory& model    ();
    UiTextureFactory&   icon     ();
    BlueprintFactory&   blueprint();
    SkyboxFactory&      skybox   ();

    std::vector<unsigned char> loadBinary(const std::string& path);

  private:
    std::unique_ptr< SupComModelFactory> _model;
    std::unique_ptr< UiTextureFactory  > _icon;
    std::unique_ptr< BlueprintFactory  > _blueprint;
    std::unique_ptr< SkyboxFactory     > _skybox;

    std::shared_ptr<Aezesel::SCD> _units;
    std::shared_ptr<Aezesel::SCD> _textures;
    std::shared_ptr<Aezesel::SCD> _env;
    std::map<std::string, std::shared_ptr<Aezesel::SCD>> _scdMap;
  };
}