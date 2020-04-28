#include "LobbyChaperone.h"

#include "Connection.h"
#include "Serializable/LobbyBriefing.h"
#include "Serializable/SelfBriefing.h"

#include <iostream>

namespace Vishala {
  LobbyChaperone::LobbyChaperone(std::string ip, int port, std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection)
    : Protocoll(nextProtocollInvoked,std::move(connection)){
    _ip = ip;
    std::cout << "LobbyChaperone: connect: " << ip << ":" << port << std::endl;
    connect(port, ip);
  }

  void LobbyChaperone::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
  {
    if (_state == LobbyChaperone::state::HeIsUnkown) {
      SelfBriefing description;
      description.fromBinary(*package);
      _state = LobbyChaperone::state::HeIsKnown;
      std::cout << "He Is Known Now"<<std::endl;
    }
  }

  void LobbyChaperone::newConnection(size_t clientnumber, std::string ip, int port)
  {
    if (ip != _ip)
      throw std::runtime_error("Unexpected IP " + ip);
    _connected = true;
    LobbyBriefing briefing;
    auto packet = briefing.toBinary();
    std::unique_ptr<BinaryPackage> p = std::make_unique<BinaryPackage>(packet);    
    sendMessage(0,0,std::move(p));
  }

  void LobbyChaperone::connectionFailed(std::string name)
  {
    handOver(nullptr);
  }

  void LobbyChaperone::disconnect(size_t clientnumber)
  {
    handOver(nullptr);
  }

  void LobbyChaperone::update()
  {
    Protocoll::update();
  }
}