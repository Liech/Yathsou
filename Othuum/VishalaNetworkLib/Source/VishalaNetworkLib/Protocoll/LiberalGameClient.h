#pragma once

#include <memory>
#include <functional>
#include <iostream>

#include <IyathuumCoreLib/Util/UpdateTimer.h>
#include <IyathuumCoreLib/Util/Scheduler.h>

#include "VishalaNetworkLib/Core/Command.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Protocoll/LiberalMessage.h"

namespace Vishala {

  //Client that assumes send commands are deterministic
  //every client has its own state, the server is only a relay
  template<typename T>
  class LiberalGameClient {
  public:
    LiberalGameClient(std::shared_ptr<T>& data, int ticksPerSecond, int port, int serverPort, std::string serverIP) :
    _data(data){
      _timer      = std::make_unique<Iyathuum::UpdateTimer>([this]() {tick(); }, ticksPerSecond);
      _scheduler  = std::make_unique<Iyathuum::Scheduler>();
      _port       = port;
      _serverPort = serverPort;
      _ip         = serverIP;

      initConnection();
    }

    void update() {     
      _connection->update();
      _timer     ->update();
    }

    void sendCmd(std::shared_ptr<ICommand> cmd) {
      LiberalMessage msg;
      msg.type    = LiberalMessage::Type::Command;
      msg.command = cmd;
      msg.tick    = _tick;
      std::unique_ptr<BinaryPackage> toSend = std::make_unique<BinaryPackage>(msg.toBinary());
      _connection->send(0, 0, std::move(toSend));
    }

    void requestPause() {
      LiberalMessage msg;
      msg.type = LiberalMessage::Type::Pause;
      msg.tick = _tick;
      std::unique_ptr<BinaryPackage> toSend = std::make_unique<BinaryPackage>(msg.toBinary());
      _connection->send(0, 0, std::move(toSend));
    }

    void requestUnpause() {
      LiberalMessage msg;
      msg.type = LiberalMessage::Type::Start;
      msg.tick = _tick;
      std::unique_ptr<BinaryPackage> toSend = std::make_unique<BinaryPackage>(msg.toBinary());
      _connection->send(0, 0, std::move(toSend));
    }

    void addOnUpdate(std::unique_ptr<ICommand> cmd){
      _onUpdate.push_back(std::move(cmd));
    }

  private:
    void tick() {
      if (!_paused) {
        for (auto& t : _onUpdate)
          t->apply(*_data);
        _scheduler->update(_tick);
        _tick++;

        //if (tick % LiberalMessage::clientReportIntervall == 0)
        //  sendClientReport();
      }
    }

    void sendClientReport() {
      LiberalMessage msg;
      msg.type = LiberalMessage::Type::ClientReport;
      msg.tick = _tick;
      std::unique_ptr<BinaryPackage> toSend = std::make_unique<BinaryPackage>(msg.toBinary());
      _connection->send(0, 0, std::move(toSend));
    }

    void scheduleCommand(size_t tick, std::shared_ptr<ICommand> cmd) {
      _scheduler->addToSchedule(tick, [this, cmd]() {
        cmd->apply((Serialization&)(*_data)); 
      });
    }

    void unpause() {
      _paused = false;
    }

    void pause() {
      _paused = true;
    }

    void initialization(size_t tick, ICommand& cmd) {
      _tick = tick;
      Serialization* s = (Serialization*)_data.get();
      cmd.apply(*s);
      LiberalMessage msg;
      msg.type = LiberalMessage::Type::Ready;
      std::unique_ptr<BinaryPackage> toSend = std::make_unique<BinaryPackage>(msg.toBinary());
      _connection->send(0, 0, std::move(toSend));
    }

    void recievePackage(const LiberalMessage& message) {
      if (message.type == LiberalMessage::Type::Command)
        scheduleCommand(message.tick, message.command);
      if (message.type == LiberalMessage::Type::Initialization)
        initialization(message.tick,*message.command);
      else if (message.type == LiberalMessage::Type::Start)
        unpause();
      else if (message.type == LiberalMessage::Type::Pause)
        pause();
    }

    void initConnection() {
      std::cout << "LiberalGameClient::initConnection" << std::endl;
      int port = _port;
      _connection = std::make_unique<Vishala::Connection>();
      _connection->setAcceptConnection(false);
      _connection->setChannelCount(1);
      _connection->setMaximumConnectionCount(1);
      _connection->setPort(port);
      _connection->setConnectionFailedCallback([this](std::string ip, int port) {initConnection(); });
      _connection->setDisconnectCallback([this](size_t client) { initConnection(); });
      _connection->setNewConnectionCallback([this](size_t client, std::string ip, int port) {
        std::cout << "client connected" << std::endl;
      });
      _connection->setRecievedCallback(0, [this](size_t, std::unique_ptr<BinaryPackage> package) {
        LiberalMessage msg;
        msg.fromBinary(*package);
        recievePackage(msg);
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

    std::shared_ptr<T>& _data      ;
    size_t              _tick = 0  ;
    bool                _paused = true;

    int                 _port      ;
    int                 _serverPort;
    std::string         _ip        ;

    std::unique_ptr<Iyathuum::UpdateTimer> _timer     ;
    std::unique_ptr<Iyathuum::Scheduler  > _scheduler ;
    std::unique_ptr<Connection>            _connection;
    std::vector<std::unique_ptr<ICommand>> _onUpdate  ;

  };
}