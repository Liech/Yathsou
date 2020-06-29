#include "NetworkGameSeed.h"

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
      _targets.insert(t);
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
    _connection->setConnectionFailedCallback([this](std::string name) {
      connectionFailed(name); 
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
  }

  void NetworkGameSeed::update() {
    _connection->update();
  }

  void NetworkGameSeed::newConnection(size_t clientnumber, std::string ip, int port) {

  }

  void NetworkGameSeed::connectionFailed(std::string name) {
    

  }

  void NetworkGameSeed::disconnect(size_t clientnumber) {

  }

  void NetworkGameSeed::messageRecived(size_t channel, size_t clientNumber, std::unique_ptr<BinaryPackage> package) {

  }

  void NetworkGameSeed::controlMessageRecived(size_t clientNumber, std::unique_ptr<BinaryPackage> package) {

  }

}