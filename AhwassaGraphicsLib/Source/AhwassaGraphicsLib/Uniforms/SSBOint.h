#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"
#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace Ahwassa {
  class SSBOuint : public Uniform {
  public:
    SSBOuint(const std::string& name, const std::vector<unsigned int>& content);
    virtual ~SSBOuint();

    virtual std::string toGLSL() const override;
    virtual void bind() override;
    virtual std::string getType() const override { return "uint"; }
    void setData(const std::vector<unsigned int>& content);

    virtual bool isBuffer() const override { return true; }

  private:
    unsigned int _ssbo;
  };
}