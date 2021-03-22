#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

class ClientConfiguration : public Vishala::Serialization {
public:
  std::string        playerName          = "Unnamed";
  std::array<int, 3> playerColor         = {255,255,255};
  std::array<int, 2> resolution          = std::array<int, 2> {1024,600};
  int                hostPort            = 6115; 
  std::string        lastGameName        = "Setons";
  std::string        lobbyServerAdress   = "localhost";
  int                lobbyServerMyPort   = 6114;
  int                lobbyServerTheirPort= 6112;
  int                gameServerPort      = 6113;
  int                myGameClientPort    = 6110;

  virtual nlohmann::json             toJson()                            override;
  virtual void                       fromJson(nlohmann::json)            override;
  virtual Vishala::BinaryPackage     toBinary()                          override;
  virtual void                       fromBinary(Vishala::BinaryPackage&) override;
};