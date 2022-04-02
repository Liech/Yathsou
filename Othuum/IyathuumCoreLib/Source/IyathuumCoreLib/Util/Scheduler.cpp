#include "Scheduler.h"

#include <stdexcept>

namespace Iyathuum {
  void Scheduler::addToSchedule(size_t tick, std::function<void()> f) {
    if (_schedule.count(tick) == 0)
      _schedule[tick] = std::vector<std::function<void()>>();
    _schedule[tick].push_back(f);
  }

  void Scheduler::update(size_t tick) {
    if (tick < _latestTick)
      throw std::runtime_error("Tick lies in the past");
    _latestTick = tick;
    if (_schedule.count(tick) == 0)
      return;
    for (auto f : _schedule[tick])
      f();
    _schedule.erase(tick);
  }

}