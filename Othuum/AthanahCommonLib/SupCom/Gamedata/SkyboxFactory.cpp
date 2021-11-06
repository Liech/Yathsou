#include "SkyboxFactory.h"

#include <regex>

#include "AezeselFileIOLib/SupremeCommander/SCD.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "AhwassaGraphicsLib/Uniforms/CubeTexture.h"
#include "AthanahCommonLib/SkyBox.h"

namespace Athanah {
  SkyboxFactory::SkyboxFactory(const std::string& path) {
    _archive = std::make_unique<Aezesel::SCD>(path);

    for (const auto& name : _archive->getDirectories("environment")) {
      if (name.ends_with(".dds") && Aezesel::ImageIO::isDDSCube(_archive->loadBinaryFile(name))) {
        _allBoxes.push_back(name);
        std::string niceName = std::regex_replace(name, std::regex("SkyCube_"), "");
        niceName = std::regex_replace(niceName, std::regex(".dds"), "");
        _names.push_back(niceName);
      }
    }
  }

  std::shared_ptr<Athanah::SkyBox> SkyboxFactory::load(const std::string& path, std::shared_ptr<Ahwassa::Camera> camera) {
    return std::make_shared<Athanah::SkyBox>(_archive->loadBinaryFile(path),camera);
  }

  std::shared_ptr<Ahwassa::CubeTexture> SkyboxFactory::loadReflectionCube(const std::string& path) {
    auto cube = Aezesel::ImageIO::readDDSCube(Aezesel::ImageIO::Format::DDS, _archive->loadBinaryFile(path));
    return std::make_shared<Ahwassa::CubeTexture>("Reflection", cube);
  }

  std::vector<std::string> SkyboxFactory::getBoxes() {
    return _allBoxes;
  }

  std::vector<std::string> SkyboxFactory::getNames() {
    return _names;
  }

}