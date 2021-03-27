#include "UpdateTimer.h"

#include <iostream>

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
    if (ticksMissing > 0) {
      for (int i = 0; i < ticksMissing; i++) {
        _ticksSinceStart++;
        _updateCall();
      }
    }
    if (ticksMissing > _ticksPerSecond / 10.0f) {
      _stallCall(ticksMissing);
      std::cout << "stall call" << std::endl;
      setTicksPerSecond(_ticksPerSecond);
    }
  }
}