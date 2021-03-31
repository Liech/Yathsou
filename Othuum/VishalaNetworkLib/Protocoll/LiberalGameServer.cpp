#include "LiberalGameServer.h"

#include <iostream>

#include "IyathuumCoreLib/Util/UpdateTimer.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Protocoll/LiberalMessage.h"
#include "VishalaNetworkLib/Protocoll/LiberalMessage.h"
#include "VishalaNetworkLib/Protocoll/InitializeCmd.h"

namespace Vishala {
  LiberalGameServer::LiberalGameServer(std::unique_ptr<Serialization> data, int port, int ticksPerSecond) {
    _data = std::move(data);
    _timer = std::make_unique<Iyathuum::UpdateTimer>([this]() {nextTick(); }, ticksPerSecond);
    _timer->setStallCall([](int) {std::cout << "GameServer stall" << std::endl; });
    initConnection(port);
  }

  void LiberalGameServer::addOnUpdate(std::unique_ptr<ICommand> cmd) {
    _onUpdate.push_back(std::move(cmd));
  }
  
  void LiberalGameServer::update() {
    _timer->update();
  }

  void LiberalGameServer::initConnection(int port) {
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

  void LiberalGameServer::nextTick() {

  }

  void LiberalGameServer::newConnection(size_t player) {
    if (_tick != 0)
      throw std::runtime_error("Runtime joining not implemented yet");
    _reportedTicks[player] = 0;
    LiberalMessage msg;
    msg.type = LiberalMessage::Type::Initialization;
    std::shared_ptr<InitializeCmd> cmd = std::make_shared<InitializeCmd>();
    cmd->data = std::make_shared<InitializeCmd>(*_data);
    msg.command = cmd;
    msg.tick = 0;
    _connection->send(player, 0, std::make_unique<BinaryPackage>(msg.toBinary()));
  }

  void LiberalGameServer::commandRecived(const LiberalMessage&) {

  }

  void LiberalGameServer::recived(size_t player, std::unique_ptr<BinaryPackage> package) {
    LiberalMessage msg;
    msg.fromBinary(*package);
    if (msg.type == LiberalMessage::Type::Command)
      commandRecived(msg);
    else if (msg.type == LiberalMessage::Type::ClientReport)
      std::cout << "Wub" << std::endl;
    else if (msg.type == LiberalMessage::Type::Pause)
      std::cout << "Pause" << std::endl;
    else if (msg.type == LiberalMessage::Type::Start)
      std::cout << "Start" << std::endl;
      //msg.tick = _tick + _RTTinTicks;
    //msg.type = LiberalMessage::Type::Command;
    //for (auto target : _connection->getAllConnections()) {
    //
    //  _connection->send(target, 0, std::move(msg));
    //}
  }
}