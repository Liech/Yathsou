#include "SkyBoxSelection.h"

#include <filesystem>
#include <regex>
#include "ListSelection.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Uniforms/CubeTexture.h"
#include "AthanahCommonLib/SkyBox.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "HaasScriptingLib/ScriptEngine.h"


SkyBoxSelection::SkyBoxSelection(Athanah::SkyboxFactory& factory,Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic), _factory(factory){

  std::string skyFile = "DefaultEnvCube.dds";  
  std::vector<std::string> skies     = factory.getBoxes();
  std::vector<std::string> niceNames = factory.getNames();

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
  _graphic._skyBox = _factory.load(newSky, _graphic.getWindow()->camera());
  _graphic._reflectionTexture = _factory.loadReflectionCube(newSky);
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