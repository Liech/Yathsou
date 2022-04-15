#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <functional>

#include "Graphic.h"

class ListSelection;

class RendererSelection {
public:
  RendererSelection(Iyathuum::glmAABB<2> area, Graphic&);

  void update();
  void draw();

  void setVisible(bool);
  bool isVisible();
private:
  void initScript();

  std::shared_ptr<ListSelection> _list;
  Graphic& _graphic;
  std::map<std::string, int> _textures;
  std::vector<std::string> _options;

  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _setRenderer;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _getRenderer;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _getAllRenderer;
};