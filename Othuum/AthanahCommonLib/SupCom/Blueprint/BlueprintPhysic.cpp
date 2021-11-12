#include "BlueprintPhysic.h"

namespace Athanah {
  BlueprintPhysic::BlueprintPhysic(const nlohmann::json& input) {
    _bankingSlope          = read("BankingSlope"          , input, 0   );
    _dragCoefficient       = read("DragCoefficient"       , input, 0.2f);
    _maxAcceleratin        = read("MaxAcceleratin "       , input, 3.4f);
    _maxBreak              = read("MaxBreak"              , input, 3.4f);
    _maxSpeed              = read("MaxSpeed"              , input, 3.4f);
    _maxSpeedReverse       = read("MaxSpeedReverse"       , input, 0   );
    _maxSteerForce         = read("MaxSteerForce"         , input, 10  );
    _minSpeedPercent       = read("MinSpeedPercent"       , input, 0   );
    _meshExtents[0]        = read("MeshExtentsX"          , input, 1   );
    _meshExtents[1]        = read("MeshExtentsY"          , input, 1   );
    _meshExtents[2]        = read("MeshExtentsZ"          , input, 1   );
    _rotateOnSpot          = readBool("RotateOnSpot"      , input, false);
    _rotateOnSpotThreshold = read("RotateOnSpotThreshold" , input, 0.1f );
    _turnRadius            = read("TurnRadius"            , input, 0    );
    _turnRate              = read("TurnRate"              , input, 90   );
  }
}