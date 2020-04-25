#pragma once

#include <vector>

namespace Vishala {
  struct BinaryPackage {
    std::vector<unsigned char> data;
    size_t                     position = 0;

    void add(BinaryPackage p);
  };
}