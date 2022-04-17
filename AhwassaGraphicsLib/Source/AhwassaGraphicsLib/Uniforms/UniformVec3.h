#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class UniformVec3 : public Uniform {
  public:
    UniformVec3(const std::string& name) : Uniform(name) {};
    void  setValue(const glm::vec3& val);
    glm::vec3 getValue();

    void bind() override;
    std::string getType() override { return "vec3"; }

  private:
    glm::vec3 _value = glm::vec3(0, 0, 0);
  };
}