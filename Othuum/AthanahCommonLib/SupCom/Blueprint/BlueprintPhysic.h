#pragma once

#include "BlueprintBase.h"

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <memory>

namespace Athanah {
  enum class UnitMotionType
  {
    Land
  };

  class BlueprintPhysic : public BlueprintBase {
  public:
    BlueprintPhysic(const nlohmann::json& input);
    virtual ~BlueprintPhysic() = default;
  private:
    float _bankingSlope    = 0   ;
    float _dragCoefficient = 0.2f;
    float _maxAcceleratin  = 3.4f;
    float _maxBreak        = 3.4f;
    float _maxSpeed        = 3.4f;
    float _maxSpeedReverse = 0   ;
    float _maxSteerForce   = 10  ;
    float _minSpeedPercent = 0   ;

    glm::vec3      _meshExtents           = glm::vec3(0.5,0.5,0.5);
    UnitMotionType _motionType            = UnitMotionType::Land;
    bool           _rotateOnSpot          = false;
    float          _rotateOnSpotThreshold = 0.1f ;
    float          _turnRadius            = 0    ;
    float          _turnRate              = 90   ;
  };
}