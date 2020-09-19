#pragma once

#include <functional>

namespace Iyathuum
{
  /// <summary>
  /// update as often as you draw.
  /// updateCall is invoked ticksPerSecond times
  /// if the second is not enough for the number of ticks stallcall is invoked with the ticks behind
  /// </summary>
  class UpdateTimer
  {
  public:
    UpdateTimer(std::function<void()> updateCall, int ticksPerSecond);

    void setStallCall(std::function<void(int)>);
    void setTicksPerSecond(int ticksPerSecond);
    void update(); //call as often as you like

  private:
    std::function<void()>    _updateCall    ;
    std::function<void(int)> _stallCall     = [](int) {};
    int                      _ticksPerSecond;
  };
}