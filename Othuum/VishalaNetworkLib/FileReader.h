#pragma once

#include "Serialization.h"

namespace Vishala {
  class FileReader {
  public:
    FileReader(std::string filename);
    ~FileReader();


    template<typename Type> Type read() {
      Type result;

      _deserializer->Read(&result) || Die();
      return result;
    }

  private:
  };
}