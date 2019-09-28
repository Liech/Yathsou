#pragma once

#include "../OpenGL/Updateable.h"
#include "../structs/Factory.h"
#include <map>
#include <vector>
#include <string>

namespace YolonaOss {
  namespace Camera {
    class CameraMode;
    class CameraSystem : public GL::Updateable {
      REGISTER(GL::Updateable, CameraSystem, "CameraSystem", { "Main" })
    public:
      virtual void load(GL::DrawSpecification*) override;
      virtual void update() override;

      std::vector<std::string> getAvailableCams(); 
      std::string              getCurrentCam();
      void                     setCurrentCam(std::string name);

    private:
      std::map<std::string, std::shared_ptr<CameraMode>> _availableCams;
      std::shared_ptr<CameraMode>                        _currentCam;
      std::string                                        _currentCamName;
      GL::DrawSpecification*                             _spec = nullptr;
        
    };
  }
}