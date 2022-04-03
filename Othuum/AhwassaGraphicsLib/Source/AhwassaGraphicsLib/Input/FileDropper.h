#pragma once

#include "UIElement.h"
#include <functional>

namespace Ahwassa {
  class FileDropper : public UIElement {
  public:
    FileDropper(std::function<void(const std::string& path)>);
    bool dropEvent(const std::string& filePath) override;
  private:
    std::function<void(const std::string& path)> _callback;
  };
}