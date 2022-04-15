#pragma once

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "Graphic.h"
#include <nlohmann/json.hpp>

class ListSelection;

namespace Ahwassa {
  class Button;
  class Texture;
  class Window;
}

class ScriptSelection {
public:
  ScriptSelection(Iyathuum::glmAABB<2> area, Graphic&);

  void update();
  void draw();

  void setVisible(bool value);
  bool isVisible();

  void executeScript(std::string filename);

private:
  void initScript();

  std::string scriptFolder = "Data\\scripts\\";
  Graphic&                             _graphic;
  std::unique_ptr<ListSelection  >     _list = nullptr;
  Iyathuum::glmAABB<2>                 _area   ;


  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _makeScreenshot;
};