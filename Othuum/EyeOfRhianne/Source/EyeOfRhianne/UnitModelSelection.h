#pragma once

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "AthanahCommonLib/SupCom/SupComEnums.h"
#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"
#include <nlohmann/json.hpp>

class ListSelection;
class AnimationSelection;

namespace Ahwassa {
  class Window;
  class Button;
  class Texture;
}
namespace Athanah {
  class SupComModel;
}

class Graphic;

class UnitModelSelection {
public:
  UnitModelSelection(Athanah::Gamedata& gamedata, Iyathuum::glmAABB<2> area,std::function<void()> disableAllCall, Graphic&);
  virtual ~UnitModelSelection() = default;

  void setVisible(bool value);
  bool isVisible();
  void draw();
  void update();

  std::shared_ptr<Athanah::SupComModel> getCurrentModel();

  std::pair<std::vector<std::string>,std::vector<std::string>> getNames(std::string category);

private:
  void initScript();
  void setModel(std::string id);
  void drawIcons(Iyathuum::glmAABB<2>,std::string name, bool hovered);
  std::shared_ptr<Ahwassa::Texture> getFaction(std::string);
  int                               getNumber(std::string);

  std::unique_ptr<ListSelection>                _categories;
  std::vector<std::unique_ptr<ListSelection>>   _lists     ;

  int                                           _currentList = 0;
  Graphic&                                      _graphic        ;
  Athanah::Gamedata&                            _gamedata       ;
  std::string                                   _currentID = "" ;
  std::function<void()>                         _disableAllCall ;
  std::vector<std::string>                      _names          ;


  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _setUnit;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _setUnitColor;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _getUnit    ;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _getBlueprint;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _getAllUnits;

};