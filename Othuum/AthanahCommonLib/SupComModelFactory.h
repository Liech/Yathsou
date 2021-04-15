#pragma once

#include <string>
#include <memory>

namespace Aezesel {
  class ZIP;
}

namespace Athanah {
  class SupComModelFactory {
  public:
    SupComModelFactory(const std::string& unitsFile);

  private:
    std::string                   _unityPath;
    std::unique_ptr<Aezesel::ZIP> _zip;
  };
}