#include "SkyBoxSelection.h"

#include <filesystem>
#include <regex>
#include "ListSelection.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AthanahCommonLib/SkyBox.h"
#include "AezeselFileIOLib/ImageIO.h"


SkyBoxSelection::SkyBoxSelection(const std::string& path,Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic){
  _path = path;

  std::string skyFile = "DefaultEnvCube.dds";
  std::vector<std::string> skies;
  std::vector<std::string> niceNames;

  for (const auto& entry : std::filesystem::directory_iterator(_path)) {
    std::string filename = entry.path().string();
    std::string shortName= filename.substr(_path.size()+1);
    if (filename.ends_with(".dds") && Aezesel::ImageIO::isDDSCube(filename)) {
      skies.push_back(shortName);
      
      std::string niceName = std::regex_replace(shortName, std::regex("SkyCube_"), "");
      niceName = std::regex_replace(niceName, std::regex(".dds"), "");
      niceNames.push_back(niceName);
    }
  }

  _list = std::make_unique<ListSelection>(skies,niceNames, area, _graphic.getWindow(), [this](std::string newSky) {
    _graphic._skyBox = std::make_shared<Athanah::SkyBox>(_path + "\\" + newSky, _graphic.getWindow()->camera());
  });
  _list->setVisible(false);
}

void SkyBoxSelection::update() {
  
}

void SkyBoxSelection::draw() {
  _list->draw();
}

void SkyBoxSelection::setVisible(bool value) {
  _list->setVisible(value);
}

bool SkyBoxSelection::isVisible() {
  return _list->isVisible();
}