#pragma once

#include <IyathuumCoreLib/lib/glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>

class ListSelection;

namespace Ahwassa {
  class Button;
  class Window;
}
namespace Athanah {
  class SupComModel;
}

class AnimationSelection {
public:
  AnimationSelection(Ahwassa::Window* w);

  void update();
  void draw();
  void setModel(std::shared_ptr<Athanah::SupComModel>);
  std::vector<glm::mat4> getAnimation();

private:
  void save();

  std::string                           _currentAnimation = "None";
  bool                                  _play = true;
  float                                 _time = 0;
  Ahwassa::Window*                      _window;
  std::shared_ptr<Athanah::SupComModel> _model;
  std::unique_ptr<ListSelection  >      _list = nullptr;
  std::unique_ptr<Ahwassa::Button>      _pause;
  std::unique_ptr<Ahwassa::Button>      _save = nullptr;
};