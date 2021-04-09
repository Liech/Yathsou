//#pragma once
//
//#include <memory>
//#include <vector>
//#include <set>
//
//#include "YolonaOss/OpenGL/Drawable.h"
//#include "YolonaOss/OpenGL/Updateable.h"
//#include "IyathuumCoreLib/lib/glm/vec3.hpp"
//#include "YolonaOss/Util/getPosition.h"
//
//namespace Suthanus
//{
//  class Vehicle;
//  class Sphere;
//}
//#include "YolonaOss/Camera/CameraSystem.h"
//
//namespace Fatboy
//{
//  class TankTower;
//  class Unit;
//  class Context;
//
//  class Protagonist : public YolonaOss::GL::Updateable, public YolonaOss::GetPosition
//  {
//  public:
//    Protagonist(std::shared_ptr<Context>, bool*, std::shared_ptr < YolonaOss::Camera::CameraSystem> cam);
//
//    virtual void load(YolonaOss::GL::DrawSpecification*) override;
//    virtual void update()                                override;
//
//    glm::vec3 getPosition();
//
//  private:
//    glm::vec3 getStartPos() { return glm::vec3(0, 2, 0); }
//    void handleInput();
//    void handlePicking();
//
//    YolonaOss::GL::DrawSpecification*           _spec    ;
//    std::shared_ptr<Context>                    _context ;
//    std::shared_ptr<Unit>                       _tank    ;
//    glm::vec3 _lastPickedPosition;
//    bool* _drawDebug;
//    std::shared_ptr<YolonaOss::Camera::CameraSystem> _cam;
//
//    bool _pressed = false;
//  };
//}