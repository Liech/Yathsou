#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"
#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace Ahwassa {
  class SSBOvec3 : public Uniform {
  public:
    SSBOvec3(const std::string& name, const std::vector<glm::vec3>& content);
    SSBOvec3(const std::string& name, size_t amount);
    virtual ~SSBOvec3();

    virtual std::string toGLSL() override;
    virtual void bind() override;
    virtual std::string getType() override { return "vec3"; }
    void setData(const std::vector<glm::vec3>& content);

    virtual bool isBuffer() override { return true; }

  private:
    unsigned int _ssbo;
  };
}