#include "CameraSystem.h"

#include "../OpenGL/DrawSpecification.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "Camera.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"
#include "../OpenGL/Window.h"

namespace YolonaOss {
  namespace Camera {
    void CameraSystem::load(GL::DrawSpecification* spec)
    {
      _spec = spec;
      std::set<std::string> camNames = Iyathuum::Factory<CameraMode>::getNamesByTag("Camera");
      for (auto name : camNames) {
        std::shared_ptr<CameraMode> cam = Iyathuum::Factory<CameraMode>::make(name);
        _availableCams[name] = cam;
        //cam->load(spec->getCam(), spec->getWindow());
      }
      _currentCam = _availableCams["RTSCamera"];
      _currentCamName = "RTSCamera";
      _currentCam->load(spec->getCam(), spec->getWindow());
    }

    void CameraSystem::update()
    {
      if (_currentCam)
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
      if (name == "None") {
        _currentCam = nullptr;
        _currentCamName = "None";
        _spec->getWindow()->setCursorStatus(Iyathuum::CursorStatus::NORMAL);
        return;
      }
      if (!_availableCams.count(name))
        throw std::runtime_error("cam not found");
      _currentCam = _availableCams[name];
      _currentCamName = name;
      _currentCam->load(_spec->getCam(),_spec->getWindow());
    }
  }
}