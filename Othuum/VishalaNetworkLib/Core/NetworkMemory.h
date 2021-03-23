#pragma once

#include <functional>
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Core/ConnectionMultiplexer.h"

//very very simple network class
//keeps serializable intelligently one way synchronized (delta compression & compression)
//limited to small sizes of synchronized stuff.
//i assume bottleneck is creating the delta, but this bug prevents currently performance profiling
//https://developercommunity.visualstudio.com/t/profiling-cpu-still-states-no-user-code-was-runnin/607535
//therefor i will write more complex approaches...

namespace Vishala {
  class BinaryPackage;

  enum class MemoryTransmissionMode {
    full        = 0,
    delta       = 1, 
    compressed  = 2
  };

  template<typename T>
  class NetworkMemoryWriter {
  public:
    NetworkMemoryWriter(size_t channel, std::shared_ptr<Connection> connection) {
      _connection = connection;
      _channel    = channel   ;
    }
    T Data;

    void changed() {//please call when data changes
      _changed = true;
    }; 

    void newTarget(size_t) {
      BinaryPackage package = Data.toBinary();
      package.position = 0;
      BinaryPackage msg;
      int mode = (int)MemoryTransmissionMode::compressed;
      BinaryPackage::val2bin(msg, mode);
      msg.add(package.compress());
      for (auto target : _connection->getAllConnections())
        _connection->send(target, _channel, std::make_unique<BinaryPackage>(msg), true);
      _lastSend = package;
      _lastSend.position = 0;
    }

    void update() {
      if (_changed) {
        BinaryPackage package = Data.toBinary();
        package.position = 0;
        BinaryPackage delta = BinaryPackage::createDelta(_lastSend, package);
        BinaryPackage msg;
        int mode = (int)MemoryTransmissionMode::delta;
        BinaryPackage::val2bin(msg, mode);
        msg.add(delta);
        for(auto target : _connection->getAllConnections())
          _connection->send(target, _channel, std::make_unique<BinaryPackage>(msg), true);
        _changed = false;
        _lastSend = package;
        _lastSend.position = 0;
      }
    }
  private:
    BinaryPackage               _lastSend;
    std::shared_ptr<Connection> _connection;
    bool                        _changed = true;
    size_t                      _channel = 0;
  };

  template<typename T>
  class NetworkMemoryReader {
  public:
    NetworkMemoryReader(size_t player, std::shared_ptr<ConnectionMultiplexer> connection) {
      _connection = connection;
      _player     = player    ;
      _connection->setOnRecievedCall(_player, [this](std::unique_ptr<BinaryPackage> inp) {
        messageRecieved(std::move(inp));
        });        
    }

    const T& Data() { 
      return _currentData;
    }

    void setOnChangedCallback(std::function<void()> onChanged) {
      _onChanged = onChanged;
    }
    
  private:
    void messageRecieved(std::unique_ptr<BinaryPackage> package) {
      MemoryTransmissionMode mode = (MemoryTransmissionMode)BinaryPackage::bin2val<int>(*package);
      if (mode == MemoryTransmissionMode::full) {
        _currentData.fromBinary(*package);
        _lastRecieved = *package;
        _lastRecieved.position = 4;
        _initialized = true;
      }
      else if (mode == MemoryTransmissionMode::delta && _initialized)
      {
        BinaryPackage r = BinaryPackage::applyDelta(_lastRecieved, *package);
        _lastRecieved = r;
        _lastRecieved.position = 0;
        _currentData.fromBinary(r);
      }
      else if (mode == MemoryTransmissionMode::compressed) {
        _lastRecieved = package->decompress();
        _currentData.fromBinary(_lastRecieved);
        _lastRecieved.position = 0;
        _initialized = true;
      }

      _onChanged();
    }

    bool                                   _initialized = false;
    BinaryPackage                          _lastRecieved;
    T                                      _currentData;
    std::function<void()>                  _onChanged = []() {};
    std::shared_ptr<ConnectionMultiplexer> _connection;
    size_t                                 _player;
  };
}