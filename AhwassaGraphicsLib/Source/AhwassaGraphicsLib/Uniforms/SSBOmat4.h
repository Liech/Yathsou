#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"
#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace Ahwassa {
  class SSBOmat4 : public Uniform {
  public:
    SSBOmat4(const std::string& name, const std::vector<glm::mat4>& content);
    SSBOmat4(const std::string& name, size_t amount);
    virtual ~SSBOmat4();

    virtual std::string toGLSL() const override;
    virtual void bind() override;
    virtual std::string getType() const override { return "mat4"; }
    void setData(const std::vector<glm::mat4>& content);

    virtual bool isBuffer() const override { return true; }

  private:
    unsigned int _ssbo;
  };
}