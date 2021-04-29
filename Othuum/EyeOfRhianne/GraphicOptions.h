#pragma once

#include <memory>
#include <functional>
#include <map>
#include "Graphic.h"

namespace Ahwassa {
  class Window;
  class Button;
  class Texture;
  class Slider;
  class Label;
  class ListLayout;
  class Bloom;
}

class ListSelection;

class GraphicOptions {
public:
  GraphicOptions(std::function<void()> disableAllCall, Graphic& graphic);

  void update();
  void drawUI();

  void setVisible(bool visible);
  bool isVisible();

  std::shared_ptr<Ahwassa::Texture> getCurrentTexture();

private:
  void makeBloomOptions();

  std::shared_ptr<Ahwassa::Button>               _showHide;
  bool                                           _visible = false;
  std::function<void()>                          _disableAllCall;
  std::map<std::string,int> _textures;
  std::shared_ptr<Ahwassa::Texture>              _currentTexture;
  std::shared_ptr<Ahwassa::ListLayout>           _bloomOptions;
  Graphic& _graphic;
};