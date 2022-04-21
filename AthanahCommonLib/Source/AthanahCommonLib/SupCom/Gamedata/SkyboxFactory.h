#pragma once

#include <string>
#include <memory>
#include <vector>

namespace Aezesel {
  class SCD;
}

namespace Ahwassa {
  class Camera;
  class CubeTexture;
}

namespace Athanah {
  class SkyBox;

  class SkyboxFactory {
  public:
    SkyboxFactory(const std::string& path);
    SkyboxFactory(std::shared_ptr<Aezesel::SCD>);
    virtual ~SkyboxFactory() = default;

    std::vector<std::string>              getBoxes();
    std::string                           getName(const std::string& ID);
    std::shared_ptr<SkyBox>               load(const std::string& path, std::shared_ptr<Ahwassa::Camera>);
    std::shared_ptr<Ahwassa::CubeTexture> loadReflectionCube(const std::string& path);

  private:
    bool _initialized = false;
    void init();

    std::shared_ptr<Aezesel::SCD>    _archive  ;
    std::vector<std::string>         _allBoxes ;
    std::vector<std::string>         _names    ;
  };
}