#pragma once

#include <memory>

namespace Superb {
  class UnitsOld;
  class Physic;
  class Database;

  class Units {
  public:
    Units(Physic&, Database&);
    virtual ~Units() = default;

    void update();

    UnitsOld& units();

  private:
    std::unique_ptr<UnitsOld> _units;
  };
}