#include "AuthoritarianGameClient.h"

#include <iostream>

#include "VishalaNetworkLib/Core/Command.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Core/NetworkMemory.h"
#include "IyathuumCoreLib/Util/UpdateTimer.h"

namespace Vishala {
  AuthoritarianGameClient::AuthoritarianGameClient(std::shared_ptr<Serialization>& data,int ticksPerSecond, int port, int serverPort,std::string serverIP)
    : _data(data) {
    _ip   = serverIP;
    _port = port    ;
    _serverPort = serverPort;

    _timer = std::make_unique<Iyathuum::UpdateTimer>([this]() {nextTick(); }, ticksPerSecond);
    _timer->setStallCall([](int) {std::cout << "GameServer stall" << std::endl; });
  }

  void AuthoritarianGameClient::update() {
    _timer->update();
  }

  void AuthoritarianGameClient::nextTick() {
    _connection->update();
  }

  void AuthoritarianGameClient::sendCmd(const ICommand& cmd) {
    std::unique_ptr<BinaryPackage> toSend = std::make_unique<BinaryPackage>(cmd.serialize());
    _connection->send(0, 0, std::move(toSend));
  }

  void AuthoritarianGameClient::initConnection() {
    std::cout << "AuthoritarianGameClient::initConnection" << std::endl;
    int port = _port;
    _connection = std::make_unique<Vishala::Connection>();
    _connection->setAcceptConnection(false);
    _connection->setChannelCount(3);
    _connection->setMaximumConnectionCount(1);
    _connection->setPort(port);
    _connection->setConnectionFailedCallback([this](std::string ip, int port) {initConnection(); });
    _connection->setDisconnectCallback([this](size_t client) { initConnection(); });
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
    _reader = std::make_unique<NetworkMemoryReader>(_data, 0, *_connection);

    _connection->connectNonblocking(_serverPort, _ip);
  }
}