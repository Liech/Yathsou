#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class UniformVecMat4 : public Uniform {
  public:
    UniformVecMat4(const std::string& name, int size) : Uniform(name) { _value.resize(size); _size = size; };
    void  setValue(const std::vector<glm::mat4>& val);
    const std::vector<glm::mat4>& getValue() const;
    virtual int getNumberOfLocationsUsed() const override { return _size; }
    virtual std::string getArrayPostfix() const  { return "[" + std::to_string(_size) + "]"; }

    void bind() override;
    std::string getType() const override { return "mat4"; }//[" + std::to_string(_size) + "]"; }

  private:
    std::vector<glm::mat4> _value;
    int _size = 1;
  };
}