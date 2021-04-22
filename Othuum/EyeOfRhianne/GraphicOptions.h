#pragma once

#include <memory>
#include <functional>
#include <map>

namespace Ahwassa {
  class Window;
  class Button;
  class Texture;
}

class ListSelection;

class GraphicOptions {
public:
  GraphicOptions(std::vector<std::shared_ptr<Ahwassa::Texture>>,std::function<void()> disableAllCall, Ahwassa::Window* );

  void update();
  void drawUI();

  void setVisible(bool visible);
  bool isVisible();

  std::shared_ptr<Ahwassa::Texture> getCurrentTexture();

private:
  Ahwassa::Window*                               _window;
  std::shared_ptr<Ahwassa::Button>               _showHide;
  bool                                           _visible = false;
  std::function<void()>                          _disableAllCall;
  std::map<std::string,std::shared_ptr<Ahwassa::Texture>> _textures;
  std::shared_ptr<Ahwassa::Texture>              _currentTexture;
  std::shared_ptr<ListSelection>                 _list;
};