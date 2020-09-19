#include "UpdateTimer.h"

namespace Iyathuum
{

  UpdateTimer::UpdateTimer(std::function<void()> updateCall, int ticksPerSecond){
    _updateCall       = updateCall;
    _ticksPerSecond   = ticksPerSecond;
    _measurementStart = std::chrono::high_resolution_clock::now();
    _ticksSinceStart  = 0;
    _lastMeasurement = std::chrono::high_resolution_clock::now();
  }

  void UpdateTimer::setStallCall(std::function<void(int)> stallCall){
    _stallCall = stallCall;
  }

  void UpdateTimer::setTicksPerSecond(int ticksPerSecond) {
    _ticksPerSecond   = ticksPerSecond;
    _measurementStart = std::chrono::high_resolution_clock::now();
    _ticksSinceStart  = 0;
  }

  void UpdateTimer::update(){
    auto currentMeasurment = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> ticksDiff = currentMeasurment-_measurementStart;
    long long ticksShouldBe = ticksDiff.count() * _ticksPerSecond;
    long long ticksMissing = ticksShouldBe - _ticksSinceStart;
    if (ticksMissing > _ticksPerSecond * 2)
      _stallCall(ticksMissing);
    if (ticksMissing > 0) {
      _ticksSinceStart++;
      _updateCall();
    }
  }
}