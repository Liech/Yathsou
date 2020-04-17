
#include "enetTest.h"

#include "enet/enet.h"

#include <iostream>

void enetTest::work() {
  if (enet_initialize() != 0)
  {
    std::cout<<"An error occurred while initializing ENet."<<std::endl;
  }
  atexit(enet_deinitialize);
}