#include "NetworkGameSeed.h"

#include <iostream>

namespace Vishala {
  NetworkGameSeed::NetworkGameSeed(NetworkGameSeedInput input) {
    _input = input;
    initConnection();
    initTargets();
  }

  void NetworkGameSeed::initTargets() {
    _targets.clear();

    for (auto target : _input.targets) {
      Target t;
      t.port = target.port;
      t.ip   = target.IP;
      t.id   = _targetIDCounter;
      _targets.push_back(t);
      _targetIDCounter++;
      _connection->connect(t.port, t.ip);
    }
  }

  void NetworkGameSeed::initConnection(){
    _connection = std::make_unique<Connection>();

    _connection->setChannelCount(_input.numberOfChannels+1);
    _connection->setMaximumConnectionCount(512);
    _connection->setAcceptConnection(true);
    _connection->setPort(_input.ownPort);

    _connection->setNewConnectionCallback([this](size_t clientnumber, std::string ip, int port) {
      newConnection(clientnumber, ip, port); 
      });
    _connection->setConnectionFailedCallback([this](std::string ip, int port) {
      connectionFailed(ip,port); 
      });
    _connection->setDisconnectCallback([this](size_t clientNumber) { 
      disconnect(clientNumber); 
      });

    _connection->setRecievedCallback(0, [this](size_t clientNumber, std::unique_ptr<BinaryPackage> p) {
      controlMessageRecived(clientNumber, std::move(p));
      });
    for(int i = 1;i < _input.numberOfChannels+1;i++)
      _connection->setRecievedCallback(i, [this,i](size_t clientNumber, std::unique_ptr<BinaryPackage> p) {
      messageRecived(i - 1, clientNumber, std::move(p)); 
        });

    _connection->start();
    for (auto s : _targets)
      _targetMap[std::make_pair(s.ip, s.port)] = &s;
    for (auto s : _targets)
      _connection->connectNonblocking(s.port, s.ip);    
  }

  void NetworkGameSeed::update() {
    _connection->update();
  }

  void NetworkGameSeed::newConnection(size_t clientnumber, std::string ip, int port) {
    auto hash = std::make_pair(ip,port);
    if (_targetMap.count(hash) == 0)
      return;
    auto target = _targetMap[hash];
    target->status = Target::status::connected;
    target->clientNumber = clientnumber;

  }

  void NetworkGameSeed::connectionFailed(std::string ip, int port) {    
    auto hash = std::make_pair(ip, port);
    if (_targetMap.count(hash) == 0)
      return;
    auto target = _targetMap[hash];
    target->status = Target::status::unconnected;
    _connection->connectNonblocking(target->port, target->ip);
  }

  void NetworkGameSeed::disconnect(size_t clientnumber) {
    if (_targetMap2.count(clientnumber) == 0)
      return;
    auto target = _targetMap2[clientnumber];
    target->status = Target::status::unconnected;
    _connection->connectNonblocking(target->port, target->ip);
  }

  void NetworkGameSeed::printStatus(){
    for (auto t : _targets)
      if (t.status != Target::status::connected)
        std::cout << "X";
      else
        std::cout << "O";
    std::cout << std::endl;
  }

  bool NetworkGameSeed::isReady()
  {
    for (auto t : _targets)
      if (t.status != Target::status::connected)
        return false;
    return true;
  }

  void NetworkGameSeed::messageRecived(size_t channel, size_t clientNumber, std::unique_ptr<BinaryPackage> package) {

  }

  void NetworkGameSeed::controlMessageRecived(size_t clientNumber, std::unique_ptr<BinaryPackage> package) {

  }

}