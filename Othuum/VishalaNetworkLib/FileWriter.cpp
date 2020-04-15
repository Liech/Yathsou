#include "FileWriter.h"



namespace Vishala {
  FileWriter::FileWriter(std::string filename) {
    _filename   = filename;
    _serializer = std::make_unique< nop::Serializer<Writer>>();
  }

  FileWriter::~FileWriter() {
    std::ofstream stream;
    stream.open(_filename);
    const std::string data = _serializer->writer().stream().str();
    stream << data;
    stream.close();
  }
}