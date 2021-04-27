#pragma once

#include <string>
#include <memory>
#include <map>
#include <utility>

#include "SupComEnums.h"


namespace Ahwassa {
  class Texture;
}

namespace Athanah {
  enum class FactionIconType {
    Teamcolorable,//Data\textures\ui\common\widgets\faction-icons-alpha_bmp
    Normal, //Data\textures\ui\common\faction_icon-lg
    Veteran,////Data\textures\ui\common\icons
  };

  class UiTextureFactory {
  public:
    UiTextureFactory(std::string path);

    std::shared_ptr<Ahwassa::Texture> getStrategicIcon (std::string iconName, SelectableButtonStatus status); //Data\textures\ui\common\game\strategicicons
    std::shared_ptr<Ahwassa::Texture> getIcon          (std::string unitName); //Data\textures\ui\common\icons
    std::shared_ptr<Ahwassa::Texture> getBackgroundIcon(std::string iconName, ButtonStatus status); //Data\textures\ui\common\icons
    std::shared_ptr<Ahwassa::Texture> getFactionIcon   (Faction faction, FactionIconType type);
    std::shared_ptr<Ahwassa::Texture> getTierIcons     (Faction faction, TechLevel);

  private:
    std::string _path;

    std::shared_ptr<Ahwassa::Texture> loadStrategicIcon(std::string iconName, SelectableButtonStatus status);
    std::shared_ptr<Ahwassa::Texture> loadIcon(std::string iconName);
    std::shared_ptr<Ahwassa::Texture> loadFactionIcon(Faction faction, FactionIconType type);
    std::shared_ptr<Ahwassa::Texture> loadBackgroundIcon(std::string iconName, ButtonStatus status);


    std::map<std::pair<std::string,SelectableButtonStatus>, std::shared_ptr<Ahwassa::Texture>> _strategicIcons ;
    std::map<std::string, std::shared_ptr<Ahwassa::Texture>> _icons          ;
    std::map<std::pair<std::string,ButtonStatus>, std::shared_ptr<Ahwassa::Texture>> _backgroundIcons;
    std::map<std::pair<Faction,FactionIconType>, std::shared_ptr<Ahwassa::Texture>> _factionIcons;
    std::map<std::string, std::shared_ptr<Ahwassa::Texture>> _tierIcons      ;

  };
}