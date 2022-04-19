#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class UniformVecVec3 : public Uniform {
  public:
    UniformVecVec3(std::string name, int size) : Uniform(name) { _value.resize(size); _size = size; };
    void  setValue(const std::vector<glm::vec3>& val);
    const std::vector<glm::vec3>& getValue() const;
    virtual int getNumberOfLocationsUsed() const override { return _size; }
    virtual std::string getArrayPostfix() const { return "[" + std::to_string(_size) + "]"; }

    void bind() override;
    std::string getType() const override { return "vec3"; }

  private:
    std::vector<glm::vec3> _value;
    int _size = 1;
  };
}