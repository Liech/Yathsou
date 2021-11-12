#include "BlueprintPhysic.h"

namespace Athanah {
  BlueprintPhysic::BlueprintPhysic(const nlohmann::json& input) {
    _bankingSlope          = read<float>("BankingSlope"          , input, 0   );
    _dragCoefficient       = read<float>("DragCoefficient"       , input, 0.2f);
    _maxAcceleratin        = read<float>("MaxAcceleratin "       , input, 3.4f);
    _maxBreak              = read<float>("MaxBreak"              , input, 3.4f);
    _maxSpeed              = read<float>("MaxSpeed"              , input, 3.4f);
    _maxSpeedReverse       = read<float>("MaxSpeedReverse"       , input, 0   );
    _maxSteerForce         = read<float>("MaxSteerForce"         , input, 10  );
    _minSpeedPercent       = read<float>("MinSpeedPercent"       , input, 0   );
    _meshExtents[0]        = read<float>("MeshExtentsX"          , input, 1   );
    _meshExtents[1]        = read<float>("MeshExtentsY"          , input, 1   );
    _meshExtents[2]        = read<float>("MeshExtentsZ"          , input, 1   );
    _rotateOnSpot          = readBool("RotateOnSpot"      , input, false);
    _rotateOnSpotThreshold = read<float>("RotateOnSpotThreshold" , input, 0.1f );
    _turnRadius            = read<float>("TurnRadius"            , input, 0    );
    _turnRate              = read<float>("TurnRate"              , input, 90   );
  }

  float          BlueprintPhysic::bankingSlope         () const{return _bankingSlope         ;}
  float          BlueprintPhysic::dragCoefficient      () const{return _dragCoefficient      ;}
  float          BlueprintPhysic::maxAcceleratin       () const{return _maxAcceleratin       ;}
  float          BlueprintPhysic::maxBreak             () const{return _maxBreak             ;}
  float          BlueprintPhysic::maxSpeed             () const{return _maxSpeed             ;}
  float          BlueprintPhysic::maxSpeedReverse      () const{return _maxSpeedReverse      ;}
  float          BlueprintPhysic::maxSteerForce        () const{return _maxSteerForce        ;}
  float          BlueprintPhysic::minSpeedPercent      () const{return _minSpeedPercent      ;}
  float          BlueprintPhysic::rotateOnSpotThreshold() const{return _rotateOnSpotThreshold;}
  float          BlueprintPhysic::turnRadius           () const{return _turnRadius           ;}
  float          BlueprintPhysic::turnRate             () const{return _turnRate             ;}
  bool           BlueprintPhysic::rotateOnSpot         () const{return _rotateOnSpot         ;}
  UnitMotionType BlueprintPhysic::motionType           () const{return _motionType           ;}
  glm::vec3      BlueprintPhysic::meshExtents          () const{return _meshExtents          ;}
}