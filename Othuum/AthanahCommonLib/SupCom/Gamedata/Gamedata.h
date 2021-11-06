#pragma once

#include <string>
#include <memory>

namespace Athanah {
  class SupComModelFactory;
  class UiTextureFactory;
  class BlueprintFactory;

  class Gamedata {
  public:
    Gamedata(std::string supComPath, bool useSCDFiles);
    virtual ~Gamedata() = default;

    SupComModelFactory& model    ();
    UiTextureFactory&   icon     ();
    BlueprintFactory&   blueprint();

  private:
    std::unique_ptr< SupComModelFactory> _model;
    std::unique_ptr< UiTextureFactory  > _icon;
    std::unique_ptr< BlueprintFactory  > _blueprint;
  };
}