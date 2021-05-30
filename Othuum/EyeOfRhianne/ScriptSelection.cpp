#include "ScriptSelection.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTextRenderer.h"
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
