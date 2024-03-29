#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class UniformVec4 : public Uniform {
  public:
    UniformVec4(const std::string& name) : Uniform(name) {};
    void  setValue(const glm::vec4& val);
    glm::vec4 getValue() const;

    void bind() override;
    std::string getType() const override { return "vec4"; }

  private:
    glm::vec4 _value = glm::vec4(0, 0, 0, 0);
  };
}