#pragma once

#include <functional>
#include <chrono>

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

    std::chrono::time_point<std::chrono::steady_clock> _lastMeasurement;
    double                                             _averageDrawTime = 0;//time needed between update calls
    double                                             _averageUpdateTime = 0;
    std::chrono::time_point<std::chrono::steady_clock> _measurementStart;
    long long                                          _ticksSinceStart = 0;
  };
}