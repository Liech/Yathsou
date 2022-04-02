#pragma once

#include <functional>
#include <vector>
#include <mutex>
#include <future>

namespace Iyathuum{
  class ContentLoader{
  public:
    ~ContentLoader();

    void  addPackage(std::function<void()> toLoad, bool synchronous);
    void  start();
    void  update();
    float getProgression(); //returns 0.0-1.0
    bool  isFinished();
    bool  isStarted();
    void  abort();

  private:
    void increaseProgression(); //thread safe

    bool _started    = false;
    bool _isFinished = false;
    bool _isAborted  = false;

    size_t            _workDone      = 0;
    std::mutex        _workDoneMutex    ;
    size_t            _syncPosition  = 0;
    size_t            _asyncPosition = 0;
    std::future<void> _threadFuture     ;

    std::vector<std::function<void()>> _toLoad           ;
    std::vector<std::function<void()>> _toLoadSynchronous;
    
  };
}