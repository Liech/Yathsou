#pragma once

#include "UIElement.h"
#include <functional>

namespace Ahwassa {
  class FileDropper : public UIElement {
  public:
    FileDropper(std::function<void(const std::string& path)>);
    bool dropEvent(const std::string& filePath) override;
    virtual bool wantFocus() override { return false; }
  private:
    std::function<void(const std::string& path)> _callback;
  };
}