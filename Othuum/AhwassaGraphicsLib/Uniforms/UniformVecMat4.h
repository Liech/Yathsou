#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class UniformVecMat4 : public Uniform {
  public:
    UniformVecMat4(std::string name, int size) : Uniform(name) { _value.resize(size); _size = size; };
    void  setValue(const std::vector<glm::mat4> val);
    const std::vector<glm::mat4>& getValue();
    virtual int getNumberOfLocationsUsed() override { return _size; }
    virtual std::string getArrayPostfix() { return "[" + std::to_string(_size) + "]"; }

    void bind() override;
    std::string getType() override { return "mat4"; }//[" + std::to_string(_size) + "]"; }

  private:
    std::vector<glm::mat4> _value;
    int _size = 1;
  };
}