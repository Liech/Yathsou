#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  class ICommand : public Vishala::Serialization {
  public:
    virtual void apply(Serialization&) = 0;
  };

  template<typename T>
  class Command : public ICommand {
  public:
    virtual void apply(Serialization& s) {
      _apply(static_cast<T&>(s));
    }
    virtual void _apply(T&) = 0;
  };
}