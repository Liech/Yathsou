#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

class ClientConfiguration : public Vishala::Serialization {
public:
  std::string        playerName = "Unnamed";
  std::array<int, 2> resolution = std::array<int, 2> {1024,600};

  virtual nlohmann::json             toJson()                   override;
  virtual void                       fromJson(nlohmann::json)   override;
  virtual Vishala::BinaryPackage     toBinary()                 override;
  virtual void                       fromBinary(Vishala::BinaryPackage&) override;
};