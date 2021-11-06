#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"
#include <IyathuumCoreLib/lib/glm/glm.hpp>

namespace Superb {
  class Config : public Vishala::Serialization {
  public:
    const std::string Name() const override { return "Config"; }

    int         ScreenWidth  = 800;
    int         ScreenHeight = 600;
    glm::vec3   CameraPos    = glm::vec3(4, 3, 3);
    glm::vec3   CameraTarget = glm::vec3(0,0,0);
    std::string SupComPath   = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Supreme Commander Forged Alliance";
    bool        useSCDFiles  = false;

    virtual nlohmann::json         toJson()         const              override;
    virtual void                   fromJson(nlohmann::json)            override;
    virtual Vishala::BinaryPackage toBinary()       const              override;
    virtual void                   fromBinary(Vishala::BinaryPackage&) override;
  };
}