#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class UniformMat4 : public Uniform {
  public:
    UniformMat4(const std::string& name) : Uniform(name) {};
    void  setValue(const glm::mat4& val);
    glm::mat4 getValue();

    void bind() override;
    std::string getType() override { return "mat4"; }

  private:
    glm::mat4 _value = glm::mat4(1.0);
  };
}