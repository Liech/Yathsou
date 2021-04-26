#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"

#include <vector>
#include <string>

namespace Ahwassa {
  class SSBOvec4 : public Uniform {
  public:
    SSBOvec4(const std::string& name, const std::vector<glm::vec4>& content);
    SSBOvec4(const std::string& name, size_t amount);
    virtual ~SSBOvec4();

    virtual std::string toGLSL() override;
    virtual void bind() override;
    virtual std::string getType() override { return "vec4"; }
    void setData(const std::vector<glm::vec4>& content);

    virtual bool isBuffer() override { return true; }

  private:
    unsigned int _ssbo;
  };
}