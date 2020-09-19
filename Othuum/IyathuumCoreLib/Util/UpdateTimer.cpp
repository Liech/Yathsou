#include "UpdateTimer.h"

namespace Iyathuum
{

  UpdateTimer::UpdateTimer(std::function<void()> updateCall, int ticksPerSecond){
    _updateCall = updateCall;
    _ticksPerSecond = ticksPerSecond;
  }

  void UpdateTimer::setStallCall(std::function<void(int)> stallCall){
    _stallCall = stallCall;
  }

  void UpdateTimer::setTicksPerSecond(int ticksPerSecond) {
    _ticksPerSecond = ticksPerSecond;
  }

  void UpdateTimer::update(){
    _updateCall();
  }
}