#include "ContentLoader.h"
#include <stdexcept>

namespace Iyathuum{

  ContentLoader::~ContentLoader() {
    _isAborted = true;
    _threadFuture.wait();
  }

  void ContentLoader::addPackage(std::function<void()> toLoad, bool synchronous){
    if (_started)
      throw std::runtime_error("Content Loader: Package cannot be added when loading already started");
    if (synchronous)
      _toLoadSynchronous.push_back(toLoad);
    else
      _toLoad.push_back(toLoad);
  }

  void ContentLoader::start() {
    if (_started)
      throw std::runtime_error("Content Loader: can only be started once");
    _started = true;
    _threadFuture = std::async([this]() {
      while (!_isAborted && _asyncPosition < _toLoad.size()) {
        _toLoad[_asyncPosition]();
        _asyncPosition++;
        increaseProgression();
      }
      });
  }

  void ContentLoader::abort() {
    _isAborted = true;
  }

  void ContentLoader::update() {
    if (!_started || _isAborted)
      return;

    if (_syncPosition < _toLoadSynchronous.size()){
      _toLoadSynchronous[_syncPosition]();
      _syncPosition++;
      increaseProgression();
    }

    if (_workDone == _toLoad.size() + _toLoadSynchronous.size())
      _isFinished = true;
  }

  bool ContentLoader::isFinished() {
    return _isFinished;
  }

  bool ContentLoader::isStarted() {
    return _started;
  }

  float ContentLoader::getProgression() {
    return (float)_workDone / (_toLoad.size() + _toLoadSynchronous.size());
  }

  void ContentLoader::increaseProgression() {
    const std::lock_guard<std::mutex> lock(_workDoneMutex);
    _workDone++;
  }

}