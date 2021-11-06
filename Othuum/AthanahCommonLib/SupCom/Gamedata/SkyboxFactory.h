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
    virtual ~SkyboxFactory() = default;

    std::vector<std::string>              getBoxes();
    std::vector<std::string>              getNames();
    std::shared_ptr<SkyBox>               load(const std::string& path, std::shared_ptr<Ahwassa::Camera>);
    std::shared_ptr<Ahwassa::CubeTexture> loadReflectionCube(const std::string& path);

  private:
    std::unique_ptr<Aezesel::SCD>    _archive  ;
    std::vector<std::string>         _allBoxes ;
    std::vector<std::string>         _names    ;
  };
}