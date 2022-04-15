#include "ScriptSelection.h"

#include <glm/gtc/matrix_transform.hpp>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Renderer/BasicRectangleRenderer.h"
#include "AhwassaGraphicsLib/Renderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/Renderer/BasicTextRenderer.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"

#include "ListSelection.h"
#include "Graphic.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "HaasScriptingLib/ScriptEngine.h"

ScriptSelection::ScriptSelection(Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic) {
  _area = area;


  std::vector<std::string> names;

  for (const auto& entry : std::filesystem::directory_iterator(scriptFolder)) {
    std::string path = entry.path().string();
    path = path.substr(scriptFolder.size());
    if (!path.ends_with(".lua"))
      continue;

    names.push_back(path);
  }

  _list = std::make_unique<ListSelection>(names, names, area, _graphic.getWindow(), [this](std::string scriptFile) {
    executeScript(scriptFolder + scriptFile);
  });
  _list->setVisible(false);
  initScript();
}

void ScriptSelection::executeScript(std::string filename) {
  std::string pwd = std::filesystem::current_path().string();
  std::cout << "++++++++++++++++" << std::endl;
  std::cout << "Running Script " << filename << std::endl;
  std::cout << "PWD: " << pwd << std::endl;
  std::cout << "++++++++++++++++" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::string fullPath = pwd + "\\" + filename;
  try {
    _graphic._scripts->executeFile(fullPath);
  }
  catch(const std::runtime_error& error) {
    std::cout << "ERROR: " << error.what() << std::endl;
  }
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "++++++++++++++++" << std::endl;
  std::cout << "Finished Script " << filename << std::endl;
  std::cout << "++++++++++++++++" << std::endl;
}

void ScriptSelection::setVisible(bool value) {
  _list->setVisible(value);
}

bool ScriptSelection::isVisible() {
  return _list->isVisible();
}

void ScriptSelection::update() {

}

void ScriptSelection::draw() {
  _list->draw();
}

void ScriptSelection::initScript() {
  _makeScreenshot = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    _graphic.getWindow()->frame();
    _graphic.getWindow()->frame();
    _graphic.getWindow()->frame();
    auto screenshot = _graphic.screenshot();
    std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> mirrored = std::make_unique<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>(screenshot->getDimensionVector());
    mirrored->apply([&screenshot](const std::array<size_t, 2>& pos, Iyathuum::Color& val) {
      val = screenshot->getVal({ pos[0],screenshot->getDimension(1) - pos[1] - 1});
    });
    Aezesel::ImageIO::writeImage(input, *mirrored);
    return "";
  }
  );
  _graphic._scripts->registerFunction("eyeSaveScreenshot", _makeScreenshot);
}