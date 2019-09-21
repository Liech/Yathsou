#pragma once

#include "../OpenGL/Updateable.h"
#include "../structs/Factory.h"
#include <map>
#include <vector>
#include <string>

namespace YolonaOss {
  namespace GL {
    class Camera;
  }
  namespace Camera {
    class Camera;
    class CameraSystem : public GL::Updateable {
      REGISTER(GL::Updateable, CameraSystem, "CameraSystem", { "Main" })
    public:
      virtual void load(GL::DrawSpecification*) override;
      virtual void update() override;

      std::vector<std::string> getAvailableCams(); 
      std::string              getCurrentCam();
      void                     setCurrentCam(std::string name);

    private:
      std::map<std::string, std::shared_ptr<Camera>> _availableCams;
      std::shared_ptr<Camera>                        _currentCam;
      std::string                                    _currentCamName;
    };
  }
}