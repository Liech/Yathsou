#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
#include <fstream>
#include <cassert>

#include "VishalaNetworkLib/nop/serializer.h"
#include "VishalaNetworkLib/nop/structure.h"
#include "VishalaNetworkLib/nop/utility/die.h"
#include "VishalaNetworkLib/nop/utility/stream_reader.h"
#include "VishalaNetworkLib/nop/utility/stream_writer.h"


namespace Vishala {
  class BinaryPackage {
    using Writer = nop::StreamWriter<std::stringstream>;
    using Reader = nop::StreamReader<std::stringstream>;
  public:
    BinaryPackage(); 

    void startRead();

    template<typename Type> Type read() {
      assert(_readMode);
      Type result;
      _deserializer->Read(&result) || Die();
      return result;
    }

    template<typename Type> void write(Type data) {
      assert(!_readMode);
      _serializer->Write(data);
    }

    void writeBinary(unsigned char* data, size_t length);
    void writeBinary(std::vector<unsigned char>& data);
    std::vector<unsigned char>& getBinary();

  private:
    auto Die() { return nop::Die(std::cerr); }
    
    std::vector<unsigned char>                 _data                  ;
    bool                                       _readMode     = false  ;
    std::unique_ptr<nop::Serializer<Writer>>   _serializer   = nullptr;
    std::unique_ptr<nop::Deserializer<Reader>> _deserializer = nullptr;
  };
}