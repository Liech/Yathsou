#pragma once

#include "VishalaNetworkLib/nop/serializer.h"
#include "VishalaNetworkLib/nop/structure.h"
#include "VishalaNetworkLib/nop/utility/die.h"
#include "VishalaNetworkLib/nop/utility/stream_reader.h"
#include "VishalaNetworkLib/nop/utility/stream_writer.h"

#include <iostream>
#include <queue>
#include <cassert>
#include <sstream>

namespace Vishala {
  class BinaryPackage {
    using Writer = nop::StreamWriter<std::stringstream>;
  public:
    void startRead();

    template<typename Type> Type read() {
      assert(_readMode);
      Type result;
      //_deserializer->Read(&result) || Die();
      return result;
    }

    template<typename Type> void write(Type data) {
      assert(!_readMode);
      //_serializer->Write(data);
    }

    void writeBinary(char* data, size_t length);
    void writeBinary(std::vector<char>& data);
    std::vector<char> getBinary();

  private:
    auto Die() { return nop::Die(std::cerr); }
    
    std::vector<char>                        _data                ;
    bool                                     _readMode   = false  ;
    std::unique_ptr<nop::Serializer<Writer>> _serializer = nullptr;
  };
}