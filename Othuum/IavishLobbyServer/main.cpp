
#include <iostream>
#include <memory>

#include "ServerConfiguration.h"
#include "VishalaNetworkLib/Connection.h"
#include "VishalaNetworkLib/Serializable/Message.h"
#include "ConnectionTest.h"

Vishala::Connection c;
class s {
public:
  void connect(size_t clientnumber) {
    std::cout << "Client Connect: " << clientnumber << std::endl;
  }

  void disconnect(size_t clientnumber) {
    std::cout << "Client Disconnect: " << clientnumber << std::endl;
  }

  void message(size_t clientNumber, std::unique_ptr<Vishala::BinaryPackage> package) {
    Vishala::Message msg;
    msg.fromBinary(package->data, package->position);
    std::cout << "Client Message: " << clientNumber << " - " << std::endl;
    c.send(0, 0, std::move(package));
  }
};

int main() {
  Iavish::ConnectionTest c;
  c.work();
  //std::cout << "IAVISH LOBBY SERVER" << std::endl;
  //Iavish::ServerConfiguration config;
  //config.fromJsonFile("ServerConfiguration.json");
  //s msg;
  //c.setPort(config.port);
  //c.setNewConnectionCallback([&msg](size_t clientnumber) {msg.connect(clientnumber); });
  //c.setDisconnectCallback([&msg](size_t clientnumber) {msg.disconnect(clientnumber); });
  //c.setRecievedCallback(0,[&msg](size_t clientNumber, std::unique_ptr<Vishala::BinaryPackage> package) {msg.message(clientNumber, std::move(package)); });
  //c.start();

  //while (true);

}