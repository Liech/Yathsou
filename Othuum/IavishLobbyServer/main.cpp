
#include <iostream>

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

  void message(size_t clientNumber, uint8_t* package, size_t length) {
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
  c.setRecievedCallback(0,[&msg](size_t clientNumber, uint8_t* package, size_t length) {msg.message(clientNumber,package,length); });
  c.start();

  while (true) c.update();

}