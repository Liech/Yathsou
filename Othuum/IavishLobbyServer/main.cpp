#include "VishalaNetworkLib/enetTest.h"
#include "json.hpp"

#include "ServerConfiguration.h"
#include "VishalaNetworkLib/Server.h"

int main() {
  Iavish::ServerConfiguration config;
  config.fromFile("ServerConfiguration.json");

  Vishala::Server server;


}