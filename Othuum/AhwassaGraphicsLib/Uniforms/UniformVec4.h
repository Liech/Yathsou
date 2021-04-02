#pragma once

#include "Uniform.h"

namespace Ahwassa {

  class UniformVec4 : public Uniform {
  public:
    UniformVec4(std::string name) : Uniform(name) {};
    void  setValue(glm::vec4 val);
    glm::vec4 getValue();

    void bind() override;
    std::string getType() override { return "vec4"; }

  private:
    glm::vec4 _value = glm::vec4(0, 0, 0, 0);
  };
}