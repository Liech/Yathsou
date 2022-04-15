#pragma once

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "Graphic.h"

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
  AnimationSelection(Iyathuum::glmAABB<2> area,Graphic&);

  void update();
  void draw();

  void setVisible(bool value);
  bool isVisible();

private:
  void save();
  std::vector<glm::mat4> getAnimation();


  std::string                           _currentAnimation = "None";
  bool                                  _play = true;
  float                                 _time = 0;
  Graphic&                               _graphic;
  std::unique_ptr<ListSelection  >      _list = nullptr;
  std::shared_ptr<Athanah::SupComModel>  _model;
  std::shared_ptr<Ahwassa::Button>      _pause;
  std::shared_ptr<Ahwassa::Button>      _save = nullptr;
  Iyathuum::glmAABB<2>                  _area;
  bool                                  _visible = false;
};