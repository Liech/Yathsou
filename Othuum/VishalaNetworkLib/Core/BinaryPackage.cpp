#include "BinaryPackage.h"


namespace Vishala {
  void BinaryPackage::add(BinaryPackage package) {
    data.insert(data.end(), package.data.begin(), package.data.end());
  }
}