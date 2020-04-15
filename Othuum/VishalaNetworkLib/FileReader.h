#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
#include <fstream>

#include "VishalaNetworkLib/nop/serializer.h"
#include "VishalaNetworkLib/nop/structure.h"
#include "VishalaNetworkLib/nop/utility/stream_reader.h"
#include "VishalaNetworkLib/nop/utility/die.h"

namespace Vishala {
  class FileReader {
    using Reader = nop::StreamReader<std::stringstream>;
  public:
    FileReader(std::string filename);
    ~FileReader();

    auto Die() { return nop::Die(std::cerr); }

    template<typename Type> Type read() {
      Type result;
      _deserializer->Read(&result) || Die();
      return result;
    }

  private:
    std::unique_ptr<nop::Deserializer<Reader>>  _deserializer;
  };
}