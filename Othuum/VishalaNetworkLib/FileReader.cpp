#include "FileReader.h"

namespace Vishala {
  FileReader::FileReader(std::string filename){
    
    std::ifstream t(filename);
    std::stringstream stream;
    stream<< t.rdbuf();
    _deserializer = std::make_unique< nop::Deserializer<Reader>>(std::move(stream));
  }

  FileReader::~FileReader() {
  }
}
