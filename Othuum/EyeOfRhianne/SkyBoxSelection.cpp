#include "SkyBoxSelection.h"

#include <filesystem>
#include <regex>
#include "ListSelection.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Uniforms/CubeTexture.h"
#include "AthanahCommonLib/SkyBox.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "HaasScriptingLib/ScriptEngine.h"


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
    setSkyBox(newSky);
  });
  _list->setVisible(false);

  if (skies.size() > 2) { 
    setSkyBox(skies[2]);
  }
  _allSkyboxes = skies;
  initScript();
}

void SkyBoxSelection::setSkyBox(std::string newSky) {
  _graphic._skyBox = std::make_shared<Athanah::SkyBox>(_path + "\\" + newSky, _graphic.getWindow()->camera());
  auto img = Aezesel::ImageIO::readDDSCube(_path + "\\" + newSky);
  _graphic._reflectionTexture = std::make_shared<Ahwassa::CubeTexture>("Reflection", img);
  _currentSkybox = newSky;
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

void SkyBoxSelection::initScript() {
  _setSkyBox = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    std::string name = input;
    setSkyBox(name);
    return 1;
  }
  );
  _getAllBoxes = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    return _allSkyboxes;
  }
  );
  _getSkyBox = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    return _currentSkybox;
  }
  );
  _disableSkyBox = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    _graphic._skyBox = nullptr;
    return 1;
  }
  );
  _setSkyBoxColor = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>> boxTexture;
    for (int i = 0; i < 6; i++) {
      auto texture = std::make_unique< Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>(1,1);
      texture->get_linearRef(0) = Iyathuum::Color(input[0],input[1],input[2],input[3]);
      boxTexture.push_back(std::move(texture));
    }
    _graphic._skyBox = std::make_shared<Athanah::SkyBox>(boxTexture, _graphic.getWindow()->camera());
    return 1;
  }
  );
  _graphic._scripts->registerFunction("eyeSetSkyBox"      , _setSkyBox     );
  _graphic._scripts->registerFunction("eyeGetAllSkyBox"   , _getAllBoxes   );
  _graphic._scripts->registerFunction("eyeGetSkyBox"      , _getSkyBox     );
  _graphic._scripts->registerFunction("eyeDisableSkyBox"  , _disableSkyBox );
  _graphic._scripts->registerFunction("eyeSetSkyBoxColor" , _setSkyBoxColor);

}