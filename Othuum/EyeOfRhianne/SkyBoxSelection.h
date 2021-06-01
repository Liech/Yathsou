#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include <memory>
#include <string>
#include "HaasScriptingLib/lib/json.hpp"

#include "Graphic.h"

class ListSelection;

class SkyBoxSelection {
public:
  SkyBoxSelection(const std::string& path, Iyathuum::glmAABB<2> area, Graphic&);

  void update();
  void draw();

  void setVisible(bool);
  bool isVisible();
private:
  void initScript();
  void setSkyBox(std::string box);

  std::shared_ptr<ListSelection> _list;
  Graphic&                       _graphic;  
  std::string                    _path;
  std::string                    _currentSkybox = "";
  std::vector<std::string>       _allSkyboxes;

  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _setSkyBox  ;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _getSkyBox  ;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _getAllBoxes;
};