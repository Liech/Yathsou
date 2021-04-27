#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

namespace Ahwassa {
  class Window;
  class ListLayout;
  class Slider;
}

class ListSelection {
public:
  ListSelection(const std::vector<std::string>& options, const std::vector<std::string>& names, Iyathuum::glmAABB<2> loc, Ahwassa::Window*, std::function<void(std::string)> onClick);
  ListSelection(const std::vector<std::string>& options, const std::vector<std::string>& names, Iyathuum::glmAABB<2> loc, Ahwassa::Window*, std::function<void(std::string)> onClick, std::function<void(Iyathuum::glmAABB<2>, std::string,bool)>);


  void draw();
  void setVisible(bool visible);
  bool isVisible();

private:
  void init();

  Iyathuum::glmAABB<2>                 _location;
  std::function<void(std::string)>     _onClick;
  std::vector<std::string>             _options;
  std::vector<std::string>             _names;
  Ahwassa::Window*                     _window;
  std::shared_ptr<Ahwassa::ListLayout> _layout;

  bool _overrideEnabled = false;
  std::function<void(Iyathuum::glmAABB<2>, std::string, bool)> _overrideDraw;
};