#include "SVBO.h"

#include "glad/glad.h"

namespace Ahwassa {
  SVBO::SVBO(size_t size, const void* pos, const std::vector<AttributeDescription>& desc) : description(desc), IVBO(size, getStructSize(), pos) {

  }

  SVBO::~SVBO() {
   
  }

  int SVBO::getStructSize() {
    size_t result = 0;
    for (auto& x : description)
      result += x.getSize();
    return result;
  }

  std::vector<AttributeDescription> SVBO::getBinding() const {
    return description;
  }
}