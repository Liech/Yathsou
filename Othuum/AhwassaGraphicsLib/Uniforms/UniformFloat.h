#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {
  class UniformFloat : public Uniform {
  public:
    UniformFloat(std::string name) : Uniform(name) {};
    void  setValue(float val);
    float getValue();

    void bind() override;
    std::string getType() override { return "float"; }

  private:
    float _value = 0;
  };
}