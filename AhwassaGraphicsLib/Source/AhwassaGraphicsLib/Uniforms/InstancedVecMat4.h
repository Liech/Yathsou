#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {

  class InstancedVecMat4 : public Uniform {
  public:
    InstancedVecMat4(std::string name, int size);
    ~InstancedVecMat4();
    void  setValue(const std::vector<glm::mat4>& val);
    const std::vector<glm::mat4>& getValue();
    virtual int getNumberOfLocationsUsed() const override;
    virtual std::string getArrayPostfix();

    void bind() override;
    std::string getType() const override;
    virtual bool isAttribute() const override { return true; };

  private:
    std::vector<glm::mat4> _value;
    int _size = 1;
    unsigned int instanceVBO =0;
  };
}