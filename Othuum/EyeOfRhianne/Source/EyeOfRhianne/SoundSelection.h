#pragma once

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "Graphic.h"

class ListSelection;

namespace Ahwassa {
  class Button;
  class Texture;
  class Window;
  class SoundEngine;
  class SoundHandler;
}

namespace Aezesel {
  class SoundFactory;
}

class SoundSelection {
public:
  SoundSelection(std::string soundPath, Iyathuum::glmAABB<2> area, Graphic&);

  void update();
  void draw();

  void setVisible(bool value);
  bool isVisible();

private:
                                      
  Graphic&                               _graphic;
  std::shared_ptr<Aezesel::SoundFactory> _factory;
  std::shared_ptr<Ahwassa::SoundEngine > _soundEngine;
  std::shared_ptr<Ahwassa::SoundHandler> _currentHandler = nullptr;
  std::unique_ptr<ListSelection  >       _bankList = nullptr;
  std::unique_ptr<ListSelection  >       _soundList = nullptr;
  Iyathuum::glmAABB<2>                   _area   ;
};