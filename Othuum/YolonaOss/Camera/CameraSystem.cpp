#include "CameraSystem.h"

#include "../OpenGL/DrawSpecification.h"
#include "../structs/Database.h"
#include "Camera.h"

namespace YolonaOss {
  namespace Camera {
    void CameraSystem::load(GL::DrawSpecification* spec)
    {
      _spec = spec;
      std::set<std::string> camNames = Factory<CameraMode>::getNamesByTag("Camera");
      for (auto name : camNames) {
        std::shared_ptr<CameraMode> cam = Factory<CameraMode>::make(name);
        _availableCams[name] = cam;
        //cam->load(spec->getCam(), spec->getWindow());
      }
      _currentCam = _availableCams["RTSCamera"];
      _currentCamName = "RTSCamera";
      _currentCam->load(spec->getCam(), spec->getWindow());
    }

    void CameraSystem::update()
    {
      _currentCam->update();
    }

    std::vector<std::string> CameraSystem::getAvailableCams() {
      std::vector<std::string> result;
      for (auto s : _availableCams)
        result.push_back(s.first);
      return result;
    }

    std::string CameraSystem::getCurrentCam() {
      return _currentCamName;
    }

    void CameraSystem::setCurrentCam(std::string name) {
      if (!_availableCams.count(name))
        throw std::runtime_error("cam not found");
      _currentCam = _availableCams[name];
      _currentCamName = name;
      _currentCam->load(_spec->getCam(),_spec->getWindow());
    }
  }
}