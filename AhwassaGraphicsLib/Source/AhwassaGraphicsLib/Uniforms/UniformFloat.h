#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {
  class UniformFloat : public Uniform {
  public:
    UniformFloat(const std::string& name) : Uniform(name) {};
    void  setValue(float val);
    float getValue();

    void bind() override;
    std::string getType() const override { return "float"; }

  private:
    float _value = 0;
  };
}