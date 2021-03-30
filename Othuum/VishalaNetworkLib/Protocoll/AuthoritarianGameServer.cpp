#include "AuthoritarianGameServer.h"

#include <iostream>

#include "IyathuumCoreLib/Util/UpdateTimer.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Core/NetworkMemory.h"

namespace Vishala {
  AuthoritarianGameServer::AuthoritarianGameServer(std::unique_ptr<Serialization> data, int port, int ticksPerSecond) {
    _data = std::move(data);
    _timer = std::make_unique<Iyathuum::UpdateTimer>([this]() {nextTick(); }, ticksPerSecond);
    _timer->setStallCall([](int) {std::cout << "GameServer stall" << std::endl; });
    initConnection(port);
    _writer = std::make_unique<NetworkMemoryWriter>(*_data,0,*_connection);
  }

  void AuthoritarianGameServer::addOnUpdate(std::unique_ptr<ICommand> cmd) {
    _onUpdate.push_back(std::move(cmd));
  }

  void AuthoritarianGameServer::newConnection(size_t player) {
    _writer->newTarget(player);
  }

  void AuthoritarianGameServer::recived(size_t player, std::unique_ptr<BinaryPackage> package) {
    std::shared_ptr<ICommand> cmd = Serialization::deserializeCast<ICommand>(*package);
    cmd->apply(*_data);
    _writer->changed();
  }

  void AuthoritarianGameServer::nextTick() {
    _connection->update();
    _tick++;
    for (auto& t : _onUpdate)
      t->apply(*_data);
    _writer->changed();
    _writer->update();
  }

  void AuthoritarianGameServer::update() {
    _timer->update();    
  }

  void AuthoritarianGameServer::initConnection(int port) {
    _connection = std::make_unique<Vishala::Connection>();
    _connection->setAcceptConnection(true);
    _connection->setChannelCount(1);
    _connection->setMaximumConnectionCount(64);
    _connection->setPort(port);
    _connection->setConnectionFailedCallback([this](std::string ip, int port) {});
    _connection->setDisconnectCallback([this](size_t client) {});
    _connection->setRecievedCallback(0, [this](size_t client, std::unique_ptr<Vishala::BinaryPackage> package) {
      recived(client, std::move(package)); 
    });
    _connection->setNewConnectionCallback([this](size_t client, std::string ip, int port) {
      newConnection(client);
    });
    bool ok = _connection->start();
    if (!ok)
      throw std::runtime_error("Port used");
  }

}