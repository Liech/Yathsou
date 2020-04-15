#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
#include <fstream>

#include "VishalaNetworkLib/nop/serializer.h"
#include "VishalaNetworkLib/nop/structure.h"
#include "VishalaNetworkLib/nop/utility/stream_writer.h"

namespace Vishala {
  class FileWriter {    
    using Writer = nop::StreamWriter<std::stringstream>;
  public:
     FileWriter(std::string filename);
    ~FileWriter();

    template<typename Type> void write(Type data) {
      _serializer->Write(data);
    }

  private:
    std::string                              _filename  ;
    std::unique_ptr<nop::Serializer<Writer>> _serializer;
  };
}