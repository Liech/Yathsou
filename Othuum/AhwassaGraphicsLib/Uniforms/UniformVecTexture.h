#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class UniformVecTexture : public Uniform {
  public:
    UniformVecTexture(std::string name, int size) : Uniform(name) { _value.resize(size); _size = size; };
    void  setValue(const std::vector<int>& val);
    const std::vector<int>& getValue();
    virtual int getNumberOfLocationsUsed() override { return _size; }
    virtual std::string getArrayPostfix() { return "[" + std::to_string(_size) + "]"; }

    void bind() override;
    std::string getType() override { return "sampler2D"; }

  private:
    std::vector<int> _value;
    int _size = 1;
  };
}