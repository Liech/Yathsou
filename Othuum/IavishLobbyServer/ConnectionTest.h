#pragma once

#include <future>
#include "VishalaNetworkLib/Connection.h"
#include "VishalaNetworkLib/lib/concurrentqueue.h"

namespace Iavish {
  class ConnectionTest {
  public:
    std::string a(); 
    std::string b();
    std::future<std::string> A;
    std::future<std::string> B; 
    moodycamel::ConcurrentQueue<Vishala::BinaryPackage> qASend;
    moodycamel::ConcurrentQueue<Vishala::BinaryPackage> qBSend;
    void work();
  };
}