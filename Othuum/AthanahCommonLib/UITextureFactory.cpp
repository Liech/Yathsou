#include "UiTextureFactory.h"

#include <filesystem>

#include "AezeselFileIOLib/ImageIO.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"

namespace Athanah {
  UiTextureFactory::UiTextureFactory(std::string path) {
    _path = path;
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::getStrategicIcon(std::string iconName, SelectableButtonStatus status) {
    auto p = std::make_pair(iconName, status);
    if (_strategicIcons.count(p) == 0)
    {
      auto ico = loadStrategicIcon(iconName , status);
      _strategicIcons[p] = ico;
      return ico;
    }
    return _strategicIcons[p];
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::getIcon(std::string iconName) {
    if (_icons.count(iconName) == 0)
    {
      auto ico = loadIcon(iconName + "_icon");
      _icons[iconName] = ico;
      return ico;
    }
    return _icons[iconName];
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::getBackgroundIcon(std::string iconName, ButtonStatus status) {
    auto p = std::make_pair(iconName, status);
    if (_backgroundIcons.count(p) == 0)
    {
      auto ico = loadBackgroundIcon(iconName, status);
      _backgroundIcons[p] = ico;
      return ico;
    }
    return _backgroundIcons[p];
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::getFactionIcon(Faction faction, FactionIconType type) {
    auto p = std::make_pair(faction, type);
    if (_factionIcons.count(p) == 0)
    {
      auto ico = loadFactionIcon(faction, type);
      _factionIcons[p] = ico;
      return ico;
    }
    return _factionIcons[p];
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::getTierIcons(Faction faction, TechLevel) {
    //Data\textures\ui\cybran\game\avatar - engineers - panel
    return std::make_shared<Ahwassa::Texture>("Icon", 0);
  }


  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::loadStrategicIcon(std::string iconName, SelectableButtonStatus status) {
    const std::string basepath = "\\textures\\ui\\common\\game\\strategicicons\\";
    std::string statusPath;
    if (status == SelectableButtonStatus::Hover)
      statusPath = "_over";
    else if (status == SelectableButtonStatus::Normal)
      statusPath = "_rest";
    else if (status == SelectableButtonStatus::SelectedHover)
      statusPath = "_selectedover";
    else
      statusPath = "_selected";
    std::string path = _path + basepath + iconName + statusPath + ".dds";

    if (!std::filesystem::exists(path))
      return std::make_shared<Ahwassa::Texture>("StrategicIcon", 0);

    auto img = Aezesel::ImageIO::readImage(path);
    return std::make_shared<Ahwassa::Texture>("StrategicIcon", img.get());
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::loadIcon(std::string iconName) {
    const std::string basepath = "\\textures\\ui\\common\\icons\\units\\";
    std::string statusPath;
    std::string path = _path + basepath + iconName + ".dds";

    if (!std::filesystem::exists(path)) {
      if (iconName == "default_icon")
        return std::make_shared<Ahwassa::Texture>("Icon", 0);
      else
        return loadIcon("default_icon");
    }

    auto img = Aezesel::ImageIO::readImage(path);
    return std::make_shared<Ahwassa::Texture>("Icon", img.get());
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::loadFactionIcon(Faction faction, FactionIconType type) {
    //Teamcolorable,//Data\textures\ui\common\widgets\faction-icons-alpha_bmp
    //Normal, //Data\textures\ui\common\faction_icon-lg
    //Veteran,////Data\textures\ui\common\icons
    std::string icon = "none.dds";

    if (faction == Faction::Aeon && type == FactionIconType::Normal)
      icon = "\\textures\\ui\\common\\faction_icon-lg\\aeon_ico.dds";
    else if (faction == Faction::Cybran && type == FactionIconType::Normal)
      icon = "\\textures\\ui\\common\\faction_icon-lg\\cybran_ico.dds";
    else if (faction == Faction::Seraphim && type == FactionIconType::Normal)
      icon = "\\textures\\ui\\common\\faction_icon-lg\\seraphim_ico.dds";
    else if (faction == Faction::Uef && type == FactionIconType::Normal)
      icon = "\\textures\\ui\\common\\faction_icon-lg\\uef_ico.dds";
    else if (faction == Faction::Undefined && type == FactionIconType::Normal)
      icon = "\\textures\\ui\\common\\game\\strategicicons\\pause_rest.dds";

    std::string path = _path + icon;
    if (!std::filesystem::exists(path)) {
      if (faction == Faction::Undefined && type == FactionIconType::Normal)
        return std::make_shared<Ahwassa::Texture>("Faction", 0);
      else
        return loadFactionIcon(Faction::Undefined,FactionIconType::Normal);
    }
    auto img = Aezesel::ImageIO::readImage(path);
    return std::make_shared<Ahwassa::Texture>("Faction", img.get());
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::loadBackgroundIcon(std::string iconName, ButtonStatus status) {
    const std::string basepath = "\\textures\\ui\\common\\icons\\units\\";
    std::string statusPath;
    if (status == ButtonStatus::Hover)
      statusPath = "_over";
    else if (status == ButtonStatus::Normal)
      statusPath = "_up";
    else
      statusPath = "_down";
    std::string path = _path + basepath + iconName + statusPath + ".dds";

    if (!std::filesystem::exists(path))
      return std::make_shared<Ahwassa::Texture>("BackgroundIcon", 0);

    auto img = Aezesel::ImageIO::readImage(path);
    return std::make_shared<Ahwassa::Texture>("BackgroundIcon", img.get());
  }
}