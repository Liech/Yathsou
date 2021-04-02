#pragma once

#include "Uniform.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"

#include <vector>
#include <string>

namespace Ahwassa {
  class SSBOuint : public Uniform {
  public:
    SSBOuint(std::string name, std::vector<unsigned int> content);
    virtual ~SSBOuint();

    virtual std::string toGLSL() override;
    virtual void bind() override;
    virtual std::string getType() override { return "uint"; }
    void setData(std::vector<unsigned int> content);

    virtual bool isBuffer() override { return true; }

  private:
    unsigned int _ssbo;
  };
}