#pragma once

#include <memory>
#include <functional>
#include <map>

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
  GraphicOptions(std::vector<std::shared_ptr<Ahwassa::Texture>>,std::shared_ptr<Ahwassa::Bloom> bloom,std::function<void()> disableAllCall, Ahwassa::Window* );

  void update();
  void drawUI();

  void setVisible(bool visible);
  bool isVisible();

  std::shared_ptr<Ahwassa::Texture> getCurrentTexture();

private:
  void makeBloomOptions();

  Ahwassa::Window*                               _window;
  std::shared_ptr<Ahwassa::Button>               _showHide;
  bool                                           _visible = false;
  std::function<void()>                          _disableAllCall;
  std::map<std::string,std::shared_ptr<Ahwassa::Texture>> _textures;
  std::shared_ptr<Ahwassa::Texture>              _currentTexture;
  std::shared_ptr<ListSelection>                 _list;
  std::shared_ptr<Ahwassa::ListLayout>           _bloomOptions;
  std::shared_ptr<Ahwassa::Bloom>                _bloom;
};