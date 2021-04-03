#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class UniformVec2 : public Uniform {
  public:
    UniformVec2(std::string name) : Uniform(name) {};
    void  setValue(glm::vec2 val);
    glm::vec2 getValue();

    void bind() override;
    std::string getType() override { return "vec2"; }

  private:
    glm::vec2 _value = glm::vec2(0, 0);
  };
}