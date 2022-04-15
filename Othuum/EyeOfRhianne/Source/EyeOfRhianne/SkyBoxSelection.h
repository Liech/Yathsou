#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

#include "Graphic.h"
#include "AthanahCommonLib/SupCom/Gamedata/SkyboxFactory.h"

class ListSelection;

class SkyBoxSelection {
public:
  SkyBoxSelection(Athanah::SkyboxFactory&, Iyathuum::glmAABB<2> area, Graphic&);

  void update();
  void draw();

  void setVisible(bool);
  bool isVisible();
private:
  void initScript();
  void setSkyBox(std::string box);
  void setSkyBox(Iyathuum::Color);

  std::shared_ptr<ListSelection> _list;
  Graphic&                       _graphic;  
  Athanah::SkyboxFactory&        _factory;
  std::string                    _path;
  std::string                    _currentSkybox = "";
  std::vector<std::string>       _allSkyboxes;

  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _setSkyBox     ;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _getSkyBox     ;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _getAllBoxes   ;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _disableSkyBox ;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _setSkyBoxColor;
};