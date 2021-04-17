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
  ListSelection(const std::vector<std::string>& options,Iyathuum::glmAABB<2> loc,Ahwassa::Window*, std::function<void(std::string)> onClick);
  void draw();

private:
  std::function<void(std::string)>     _onClick;
  std::vector<std::string>             _options;
  Ahwassa::Window*                     _window;
  std::shared_ptr<Ahwassa::ListLayout> _layout;
};