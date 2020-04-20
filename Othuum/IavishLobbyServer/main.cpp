
#include <iostream>
#include <memory>

#include "VishalaNetworkLib/BinaryPackage.h"
#include "ServerConfiguration.h"
#include "VishalaNetworkLib/Connection.h"

class s {
public:
  void connect(size_t clientnumber) {
    std::cout << "Client Connect: " << clientnumber << std::endl;
  }

  void disconnect(size_t clientnumber) {
    std::cout << "Client Disconnect: " << clientnumber << std::endl;
  }

  void message(size_t clientNumber, std::unique_ptr<Vishala::BinaryPackage> package) {
    std::cout << "Client Message: " << clientNumber << " - " << std::endl;
  }
};

int main() {
  Iavish::ServerConfiguration config;
  config.fromFile("ServerConfiguration.json");
  s msg;
  Vishala::Connection c;
  c.setPort(config.port);
  c.setNewConnectionCallback([&msg](size_t clientnumber) {msg.connect(clientnumber); });
  c.setDisconnectCallback([&msg](size_t clientnumber) {msg.disconnect(clientnumber); });
  c.setRecievedCallback(0,[&msg](size_t clientNumber, std::unique_ptr<Vishala::BinaryPackage> package) {msg.message(clientNumber, std::move(package)); });
  c.start();

  while (true) c.update();

}