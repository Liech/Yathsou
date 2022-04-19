#include "UniformFloat.h"

#include "glad/glad.h"

namespace Ahwassa {
  float UniformFloat::getValue() const {
    return _value;
  }

  void UniformFloat::setValue(float val) {
    _value = val;
  }

  void UniformFloat::bind() {
    glUniform1f(getLocation(), _value);
  }
}