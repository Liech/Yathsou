#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class UniformVecVec2 : public Uniform {
  public:
    UniformVecVec2(std::string name, int size) : Uniform(name) { _value.resize(size); _size = size; };
    void  setValue(const std::vector<glm::vec2>& val);
    const std::vector<glm::vec2>& getValue();
    virtual int getNumberOfLocationsUsed() override { return _size; }
    virtual std::string getArrayPostfix() { return "[" + std::to_string(_size) + "]"; }

    void bind() override;
    std::string getType() override { return "vec2"; }

  private:
    std::vector<glm::vec2> _value;
    int _size = 1;
  };
}