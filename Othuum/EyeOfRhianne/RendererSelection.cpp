#include "RendererSelection.h"

#include "ListSelection.h"
#include "Graphic.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "HaasScriptingLib/ScriptEngine.h"

RendererSelection::RendererSelection(Iyathuum::glmAABB<2> area,Graphic& graphic) : _graphic(graphic){
  for (int i = 0; i < _graphic._textures.size(); i++) {
    _textures[_graphic._textures[i]->getName()] = i;
    _options.push_back(_graphic._textures[i]->getName());
  }

  _list = std::make_unique<ListSelection>(_options, _options,area, _graphic.getWindow(), [this](std::string newTexture) {
    _graphic._renderedTexture = _textures[newTexture];
  });
  _list->setVisible(false);
  initScript();
}

void RendererSelection::setVisible(bool value) {
  _list->setVisible(value);
}

bool RendererSelection::isVisible() {
  return _list->isVisible();
}

void RendererSelection::update() {

}

void RendererSelection::draw() {
  _list->draw();
}

void RendererSelection::initScript() {
  _setRenderer = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    std::string name = input;
    _graphic._renderedTexture = _textures[name];
    return 1;
  }
  );
  _getAllRenderer = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    return _options;
  }
  );
  _getRenderer = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    return _graphic._textures[_graphic._renderedTexture]->getName();
  }
  );
  _graphic._scripts->registerFunction("eyeSetRenderer"   , _setRenderer   );
  _graphic._scripts->registerFunction("eyeGetAllRenderer", _getAllRenderer);
  _graphic._scripts->registerFunction("eyeGetRenderer"   , _getRenderer   );

}