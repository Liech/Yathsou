#include "AuthoritarianGameClient.h"

#include <iostream>

#include "VishalaNetworkLib/Core/Command.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Core/NetworkMemory.h"
#include "IyathuumCoreLib/Util/UpdateTimer.h"

namespace Vishala {
  AuthoritarianGameClient::AuthoritarianGameClient(Serialization& data,int ticksPerSecond, int port, int serverPort,std::string serverIP)
    : _data(data) {
    _ip   = serverIP;
    _port = port    ;
    _serverPort = serverPort;

    _timer = std::make_unique<Iyathuum::UpdateTimer>([this]() {nextTick(); }, ticksPerSecond);
    _timer->setStallCall([](int) {std::cout << "GameServer stall" << std::endl; });
    //_reader = std::make_unique<NetworkMemoryReader>();
  }

  void AuthoritarianGameClient::update() {
    _timer->update();
  }

  void AuthoritarianGameClient::nextTick() {
    _connection->update();
  }

  void AuthoritarianGameClient::recived(size_t player, std::unique_ptr<BinaryPackage> package) {
    //_data.ID() == Vishala::BinaryPackage::bin2val<size_t>(package);
  }

  void AuthoritarianGameClient::initConnection() {
    int port = _port;
    _connection = std::make_unique<Vishala::Connection>();
    _connection->setAcceptConnection(false);
    _connection->setChannelCount(3);
    _connection->setMaximumConnectionCount(1);
    _connection->setPort(port);
    _connection->setConnectionFailedCallback([this](std::string ip, int port) {initConnection(); });
    _connection->setDisconnectCallback([this](size_t client) { initConnection(); });
    _connection->setRecievedCallback(0, [this](size_t client, std::unique_ptr<Vishala::BinaryPackage> package) {
      recived(client, std::move(package));
    });
    _connection->setNewConnectionCallback([this](size_t client, std::string ip, int port) {
    });

    bool ok = _connection->start();
    int tests = 50;
    while (!ok && tests > 0) {
      port++;
      tests--;
      _connection->setPort(port);
      ok = _connection->start();
    }
    if (!ok)
      throw std::runtime_error("Could not find free port");

    _connection->connectNonblocking(_serverPort, _ip);
  }
}