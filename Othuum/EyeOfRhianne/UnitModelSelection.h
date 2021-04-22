#pragma once

#include <IyathuumCoreLib/lib/glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>
#include <functional>

class ListSelection;
class AnimationSelection;

namespace Ahwassa {
  class Window;
  class Button;
}
namespace Athanah {
  class SupComModelFactory;
  class BlueprintFactory;
  class SupComModel;
}

class UnitModelSelection {
public:
  UnitModelSelection(const std::string path, std::function<void()> disableAllCall, std::function<void(std::string)>, Ahwassa::Window* w);

  void setVisible(bool value);
  bool isVisible();
  void draw();
  void update();

  std::shared_ptr<Athanah::SupComModel> getCurrentModel();

  std::vector<std::string> getNames();
  std::vector<glm::mat4> getAnimation();

private:
  std::unique_ptr<ListSelection>                _list;
  std::string                                   _currentID = "";
  Ahwassa::Window*                              _window    ;
  std::unique_ptr< Ahwassa::Button>             _showHide  ;
  std::unique_ptr< Athanah::SupComModelFactory> _factory   ;
  std::unique_ptr< Athanah::BlueprintFactory  > _blueprints;
  std::shared_ptr<AnimationSelection >          _animations;
  std::function<void(std::string)>              _onUnitChanged;  
  std::function<void()>                         _disableAllCall;

};