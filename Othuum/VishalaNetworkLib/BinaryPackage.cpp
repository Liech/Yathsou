#include "BinaryPackage.h"

namespace Vishala {
  BinaryPackage::BinaryPackage() {
    _serializer = std::make_unique< nop::Serializer<Writer> >();
  }

  void BinaryPackage::writeBinary(unsigned char* data, size_t length) {
    assert(!_readMode);
    _data.insert(_data.end(), data, data + length);
  }

  void BinaryPackage::writeBinary(std::vector<unsigned char>& data) {
    assert(!_readMode);
    _data.insert(_data.end(), data.begin(), data.end());
  }

  std::vector<unsigned char>& BinaryPackage::getBinary() {
    assert(_readMode);
    return _data;
  }

  void BinaryPackage::startRead() {
    assert(!_readMode);
    _readMode   = true;

    const std::string data = _serializer->writer().stream().str();
    _serializer = nullptr;
    const char* content = data.c_str();
    _data.insert(_data.end(), content, content + data.length() + 1);

    std::stringstream stream;
    stream << _data.data();
    _deserializer = std::make_unique< nop::Deserializer<Reader>>(std::move(stream));
  }
}