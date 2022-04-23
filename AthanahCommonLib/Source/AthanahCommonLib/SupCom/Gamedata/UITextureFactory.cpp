#include "UiTextureFactory.h"

#include "AezeselFileIOLib/ImageIO.h"
#include "AezeselFileIOLib/SupremeCommander/SCD.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"

namespace Athanah {
  UiTextureFactory::UiTextureFactory(const std::string& path) {
    _archive = std::make_shared<Aezesel::SCD>(path);
  }

  UiTextureFactory::UiTextureFactory(std::shared_ptr<Aezesel::SCD> archive) {
    _archive = archive;
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
      auto ico = loadUnitIcon(iconName + "_icon");
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
    if (_factionIcons.count(p) == 0) {
      auto ico = loadFactionIcon(faction, type);
      _factionIcons[p] = ico;
      return ico;
    }
    return _factionIcons[p];
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::getTierIcon(Faction faction, TechLevel type, SelectableButtonStatus status) {
    auto p = std::make_tuple(faction, type, status);
    if (_tierIcons.count(p) == 0) {
      auto ico = loadTierIcon(faction, type, status);
      _tierIcons[p] = ico;
      return ico;
    }
    return _tierIcons[p];
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::loadTierIcon(Faction faction, TechLevel tier, SelectableButtonStatus status) {
    std::string path = "ui\\";

    if (faction == Faction::Aeon)
      path += "aeon";
    else if (faction == Faction::Cybran)
      path += "cybran";
    else if (faction == Faction::Uef)
      path += "uef";
    else if (faction == Faction::Seraphim)
      path += "seraphim";
    else
      path += "uef";

    path += "\\game\\construct-tech_btn\\";

    if (tier == TechLevel::T0)
      return std::make_shared<Ahwassa::Texture>("TierIcon", 0);
    else if (tier == TechLevel::T1)
      path += "t1";
    else if (tier == TechLevel::T2)
      path += "t2";
    else if (tier == TechLevel::T3)
      path += "t3";
    else if (tier == TechLevel::T4)
      path += "t4";

    if (status == SelectableButtonStatus::Hover)
      path += "_btn_over";
    else if (status == SelectableButtonStatus::Normal)
      path += "_btn_up";
    else if (status == SelectableButtonStatus::SelectedHover)
      path += "_btn_down";
    else
      path += "_btn_selected";

    if (!_archive->fileExists(path + ".dds"))
      return std::make_shared<Ahwassa::Texture>("TierIcon", 0);
    auto img = Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS, _archive->loadBinaryFile(path + ".dds"));
    return std::make_shared<Ahwassa::Texture>("TierIcon", img.get());
  }


  //pause/play: Data\textures\ui\cybran\game\pause_btn
  //diplomacy/menu/objectives: Data\textures\ui\cybran\game\options_tab
  //pin/close/extern: Data\textures\ui\cybran\game\menu-btns

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::loadStrategicIcon(std::string iconName, SelectableButtonStatus status) {
    const std::string basepath = "ui\\common\\game\\strategicicons\\";
    std::string statusPath;
    if (status == SelectableButtonStatus::Hover)
      statusPath = "_over";
    else if (status == SelectableButtonStatus::Normal)
      statusPath = "_rest";
    else if (status == SelectableButtonStatus::SelectedHover)
      statusPath = "_selectedover";
    else
      statusPath = "_selected";
    std::string path = basepath + iconName + statusPath + ".dds";

    if (!_archive->fileExists(path))
      return std::make_shared<Ahwassa::Texture>("StrategicIcon", 0);

    auto img = Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS,_archive->loadBinaryFile(path));
    return std::make_shared<Ahwassa::Texture>("StrategicIcon", img.get());
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::loadUnitIcon(std::string iconName) {
    const std::string basepath = "ui\\common\\icons\\units\\";
    std::string statusPath;
    std::string path = basepath + iconName + ".dds";

    if (!_archive->fileExists(path)) {
      if (iconName == "default_icon")
        return std::make_shared<Ahwassa::Texture>("Icon", 0);
      else
        return loadUnitIcon("default_icon");
    }

    if (!_archive->fileExists(path))
      return std::make_shared<Ahwassa::Texture>("Icon", 0);
    auto img = Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS, _archive->loadBinaryFile(path));
    return std::make_shared<Ahwassa::Texture>("Icon", img.get());
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::loadFactionIcon(Faction faction, FactionIconType type) {
    //Teamcolorable,//Data\textures\ui\common\widgets\faction-icons-alpha_bmp
    //Normal, //Data\textures\ui\common\faction_icon-lg
    //Veteran,////Data\textures\ui\common\icons
    std::string icon = "none.dds";

    if (faction == Faction::Aeon && type == FactionIconType::Normal)
      icon = "ui\\common\\faction_icon-lg\\aeon_ico.dds";
    else if (faction == Faction::Cybran && type == FactionIconType::Normal)
      icon = "ui\\common\\faction_icon-lg\\cybran_ico.dds";
    else if (faction == Faction::Seraphim && type == FactionIconType::Normal)
      icon = "ui\\common\\faction_icon-lg\\seraphim_ico.dds";
    else if (faction == Faction::Uef && type == FactionIconType::Normal)
      icon = "ui\\common\\faction_icon-lg\\uef_ico.dds";
    else if (faction == Faction::Undefined && type == FactionIconType::Normal)
      icon = "ui\\common\\game\\strategicicons\\pause_rest.dds";

    std::string path = icon;
    if (!_archive->fileExists(path)) {
      if (faction == Faction::Undefined && type == FactionIconType::Normal)
        return std::make_shared<Ahwassa::Texture>("Faction", 0);
      else
        return loadFactionIcon(Faction::Undefined,FactionIconType::Normal);
    }
    auto img = Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS, _archive->loadBinaryFile(path));
    return std::make_shared<Ahwassa::Texture>("Faction", img.get());
  }

  std::shared_ptr<Ahwassa::Texture> UiTextureFactory::loadBackgroundIcon(std::string iconName, ButtonStatus status) {
    const std::string basepath = "ui\\common\\icons\\units\\";
    std::string statusPath;
    if (status == ButtonStatus::Hover)
      statusPath = "_over";
    else if (status == ButtonStatus::Normal)
      statusPath = "_up";
    else
      statusPath = "_down";
    std::string path = basepath + iconName + statusPath + ".dds";

    if (!_archive->fileExists(path))
      return std::make_shared<Ahwassa::Texture>("BackgroundIcon", 0);

    auto img = Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS,_archive->loadBinaryFile( path));
    return std::make_shared<Ahwassa::Texture>("BackgroundIcon", img.get());
  }
}