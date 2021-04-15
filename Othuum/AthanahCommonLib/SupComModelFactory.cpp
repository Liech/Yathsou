#include "SupComModelFactory.h"

#include "AezeselFileIOLib/ZIP.h"

namespace Athanah {
  SupComModelFactory::SupComModelFactory(const std::string& unitsFile) {
    _zip = std::make_unique<Aezesel::ZIP>(unitsFile);
  }
}