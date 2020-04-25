#include "LobbyChaperone.h"

#include "Connection.h"
#include "Serializable/LobbyBriefing.h"

namespace Vishala {
  LobbyChaperone::LobbyChaperone(std::string ip, int port, std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection)
    : Protocoll(nextProtocollInvoked,std::move(connection)){
    _ip = ip;
    connect(port, ip);
  }

  void LobbyChaperone::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
  {

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