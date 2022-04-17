#pragma once

namespace Iyathuum {
  class Command {
  public:
    virtual bool isFullfilled() const = 0;
    virtual void update()             = 0;
    virtual void cleanup()            = 0;
  };
}