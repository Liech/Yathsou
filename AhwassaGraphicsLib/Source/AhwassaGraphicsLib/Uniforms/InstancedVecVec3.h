#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class InstancedVecVec3 : public Uniform {
  public:
    InstancedVecVec3(const std::string& name, int size);
    ~InstancedVecVec3();
    void  setValue(const std::vector<glm::vec3>& val);
    const std::vector<glm::vec3>& getValue() const;
    virtual int getNumberOfLocationsUsed() const override { return 1; }
    virtual std::string getArrayPostfix() { return ""; }

    void bind() override;
    std::string getType() const override { return "vec3"; }
    virtual bool isAttribute() const override { return true; };

  private:
    std::vector<glm::vec3> _value;
    int _size = 1;
    unsigned int instanceVBO = 0;
  };
}