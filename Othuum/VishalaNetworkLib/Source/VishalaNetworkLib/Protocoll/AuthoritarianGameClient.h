#pragma once

#include <memory>
#include <functional>
#include <iostream>

#include "Core/Serialization.h"
#include "Core/NetworkMemory.h"

#include "Core/Command.h"
#include "Core/Connection.h"
#include "Core/NetworkMemory.h"
#include <IyathuumCoreLib/Util/UpdateTimer.h>

namespace Vishala {
  //gets exact server state from server. Sends cmds to server and recives newly streamed state
  //cpu bound, bad for big synchronization objects, simple, can't desync
  template<typename T>
  class AuthoritarianGameClient {
  public:
    AuthoritarianGameClient(std::shared_ptr<T>& data,int ticksPerSecond, int port, int serverPort, std::string serverIP)
    : _data(data) {
      _ip = serverIP;
      _port = port;
      _serverPort = serverPort;

      _timer = std::make_unique<Iyathuum::UpdateTimer>([this]() {nextTick(); }, ticksPerSecond);
      _timer->setStallCall([](int) {std::cout << "GameServer stall" << std::endl; });

      initConnection();
    }


    void update() {
      _timer->update();
    }

    void sendCmd(const ICommand& cmd) {
      std::unique_ptr<BinaryPackage> toSend = std::make_unique<BinaryPackage>(cmd.serialize());
      _connection->send(0, 0, std::move(toSend));
    }
    

  private:
    void nextTick() {
      _connection->update();
    }
    void initConnection() {
      std::cout << "AuthoritarianGameClient::initConnection" << std::endl;
      int port = _port;
      _connection = std::make_unique<Vishala::Connection>();
      _connection->setAcceptConnection(false);
      _connection->setChannelCount(1);
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
      _reader = std::make_unique<NetworkMemoryReader<T>>(_data, 0, *_connection);

      _connection->connectNonblocking(_serverPort, _ip);
    }

  private:
    std::shared_ptr<T>& _data;
    int            _port;
    int            _serverPort;
    std::string    _ip  ;

    std::unique_ptr<Iyathuum::UpdateTimer>  _timer     ;
    std::unique_ptr<NetworkMemoryReader<T>> _reader    ;
    std::unique_ptr<Connection>             _connection;
  };
}