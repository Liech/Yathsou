#include "GraphicOptions.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "ListSelection.h"
#include "AhwassaGraphicsLib/Widgets/Slider.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"
#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/PostProcessing/Bloom.h"
#include "HaasScriptingLib/ScriptEngine.h"

GraphicOptions::GraphicOptions(std::function<void()> disableAllCall, Graphic& graphic): _graphic(graphic){
  _disableAllCall = disableAllCall;

  _showHide = std::make_shared<Ahwassa::Button>("Graphic", Iyathuum::glmAABB<2>(glm::vec2(300, _graphic.getWindow()->getHeight() - 50), glm::vec2(300, 50)), [this]() {
    _disableAllCall();
    setVisible(!isVisible());
  }, _graphic.getWindow());

  std::vector<std::string> textureNames;
  for (int i = 0; i < _graphic._textures.size(); i++){
    _textures[_graphic._textures[i]->getName()] = i;
    textureNames.push_back(_graphic._textures[i]->getName());
  }
  _currentTexture = _graphic._textures[0];

  makeBloomOptions();
  setVisible(false);
  initScript();
}

void GraphicOptions::makeBloomOptions() {
  _bloomOptions = std::make_shared<Ahwassa::ListLayout>(Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(300, _graphic.getWindow()->getHeight() - 50)), _graphic.getWindow());
  _bloomOptions->addLabel("Bloom Options:");
  _bloomOptions->addLabel("Size");
  _bloomOptions->addSlider(8, 0, 50, [this](float value) {_graphic._bloom->setSize(value); });
  _bloomOptions->addLabel("Directions");
  _bloomOptions->addSlider(16, 0, 100, [this](float value) {_graphic._bloom->setDirections(value); });
  _bloomOptions->addLabel("Intensity");
  _bloomOptions->addSlider(8, 0, 50, [this](float value) {_graphic._bloom->setIntensity(value); });
  _bloomOptions->addLabel("Quality");
  _bloomOptions->addSlider(3, 0, 20, [this](float value) {_graphic._bloom->setQuality(value); });
  _bloomOptions->adjustSize();
}

void GraphicOptions::drawUI() {
  _showHide->draw();
  _bloomOptions->adjustSize();
  _bloomOptions->draw();
}

void GraphicOptions::update() {

}

void GraphicOptions::setVisible(bool visible) {
  _visible = visible;
  _bloomOptions->setVisible(isVisible());  
}

bool GraphicOptions::isVisible() {
  return _visible;
}

std::shared_ptr<Ahwassa::Texture> GraphicOptions::getCurrentTexture() {
  return _currentTexture;
}

void GraphicOptions::initScript() {
  _setBloomQuality = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    _graphic._bloom->setQuality(input);
    return 1;
  }
  );
  _graphic._scripts->registerFunction("eyeSetBloomQuality", _setBloomQuality);

  _setBloomSize = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    _graphic._bloom->setSize(input);
    return 1;
  }
  );
  _graphic._scripts->registerFunction("eyeSetBloomSize", _setBloomSize);


  _setBloomDirections = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    _graphic._bloom->setDirections(input);
    return 1;
  }
  );
  _graphic._scripts->registerFunction("eyeSetBloomDirections", _setBloomDirections);


  _setBloomIntensity = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    _graphic._bloom->setIntensity(input);
    return 1;
  }
  );
  _graphic._scripts->registerFunction("eyeSetBloomIntensity", _setBloomIntensity);
}