#include "ConnectionTest.h"

#include <iostream>
#include <chrono>
#include <thread>
#include "VishalaNetworkLib/Serializable/Message.h"

namespace Iavish {

  void ConnectionTest::work() {
    A = std::async(std::launch::async, [this]() {return a();});
    B = std::async(std::launch::async, [this]() {return b();});
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    //welcome->data = {'a','b','c','d'};
    Vishala::BinaryPackage connect;
    connect.position = 1;
    qASend.enqueue(connect);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Vishala::BinaryPackage huhu;
    huhu.position = 0;
    huhu.data = {'a','b','c','d'};
    qASend.enqueue(huhu);
    while (true) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }

  std::string ConnectionTest::a() {
    Vishala::Connection c;
    c.setAcceptConnection(true);
    c.setPort(6556);
    c.setChannelCount(1);
    c.setDisconnectCallback([](size_t number) {std::cout << "DISCONNECT A" << std::endl; });
    c.setNewConnectionCallback([](size_t number, std::string ip, int port) {std::cout << "CONNECT A "<< ip <<":" <<port << std::endl; });
    c.setRecievedCallback(0, [this](size_t number, std::unique_ptr<Vishala::BinaryPackage> package) { 
      std::cout << "RECIEVE A" << std::endl;
      Vishala::BinaryPackage ptr = *package;
      qASend.enqueue(ptr);
      });
    c.start();
    while (true) {
      Vishala::BinaryPackage ptr;
      if (qASend.try_dequeue(ptr)) {
        
        if (ptr.position == 1)
          c.connect(6557,"localhost");
        else {
          std::unique_ptr<Vishala::BinaryPackage> pck = std::make_unique<Vishala::BinaryPackage>(ptr);
          c.send(0, 0, std::move(pck));
        }
      }
      c.update();
    }
    return "OK";
  }

  std::string ConnectionTest::b() {
    Vishala::Connection c;
    c.setAcceptConnection(true);
    c.setPort(6557);
    c.setChannelCount(1);
    c.setDisconnectCallback([](size_t number) {std::cout << "DISCONNECT B" << std::endl; });
    c.setNewConnectionCallback([](size_t number, std::string ip, int port) {std::cout << "CONNECT B" << ip << ":" << port << std::endl; });
    c.setRecievedCallback(0, [this](size_t number, std::unique_ptr<Vishala::BinaryPackage> package) {
      Vishala::BinaryPackage ptr = *package;
      std::cout << "RECIEVE B" << std::endl; 
      qBSend.enqueue(ptr);
    });
    c.start();
    while (true) {
      Vishala::BinaryPackage ptr;
      if (qBSend.try_dequeue(ptr)) {
        if (ptr.position == 1)
          c.connect(6556, "localhost");
        else {
          std::unique_ptr<Vishala::BinaryPackage> pck = std::make_unique<Vishala::BinaryPackage>(ptr);
          c.send(0, 0, std::move(pck));
        }
      }
      c.update();
    }
    return "OK";
  }
}