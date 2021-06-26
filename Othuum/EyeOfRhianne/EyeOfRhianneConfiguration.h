#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

class EyeOfRhianneConfiguration : public Vishala::Serialization{
public:
  const std::string Name() const override { return "EyeOfRhianneConfiguration"; }

  int         ScreenWidth  = 800;
  int         ScreenHeight = 600;
  std::string AssetPath    = "Data";
  bool        ShowFPS      = true;
  std::string SupComPath   = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Supreme Commander Forged Alliance";

  virtual nlohmann::json         toJson()         const              override;
  virtual void                   fromJson(nlohmann::json)            override;
  virtual Vishala::BinaryPackage toBinary()       const              override;
  virtual void                   fromBinary(Vishala::BinaryPackage&) override;
};