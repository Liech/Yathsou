#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"
#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace Ahwassa {
  class SSBOvec4 : public Uniform {
  public:
    SSBOvec4(const std::string& name, const std::vector<glm::vec4>& content);
    SSBOvec4(const std::string& name, size_t amount);
    virtual ~SSBOvec4();

    virtual std::string toGLSL() const override;
    virtual void bind() override;
    virtual std::string getType() const override { return "vec4"; }
    void setData(const std::vector<glm::vec4>& content);

    virtual bool isBuffer() const override { return true; }

  private:
    unsigned int _ssbo;
  };
}