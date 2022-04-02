#pragma once

#include <map>
#include <vector>
#include <functional>

namespace Iyathuum {
  class Scheduler {
  public:
    void addToSchedule(size_t tick, std::function<void()>);
    void update(size_t tick);
  private:
    std::map<size_t, std::vector<std::function<void()>>> _schedule;
    size_t                                               _latestTick = 0;
  };
}