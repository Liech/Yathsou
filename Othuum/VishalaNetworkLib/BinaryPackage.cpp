#include "BinaryPackage.h"

namespace Vishala {
  void BinaryPackage::writeBinary(char* data, size_t length) {
    assert(!_readMode);
    _data.insert(_data.end(), data, data + length);
  }

  void BinaryPackage::writeBinary(std::vector<char>& data) {
    assert(!_readMode);
    _data.insert(_data.end(), data.begin(), data.end());
  }

  std::vector<char> BinaryPackage::getBinary() {
    assert(_readMode);
    return _data;
  }

  void BinaryPackage::startRead() {
    assert(!_readMode);
    _readMode   = true;
    _serializer = std::make_unique< nop::Serializer<Writer> >();
  }
}