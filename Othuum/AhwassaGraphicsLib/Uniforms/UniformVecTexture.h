#pragma once

#include <memory>
#include <vector>
#include "AhwassaGraphicsLib/Uniforms/Uniform.h"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class Texture;

  class UniformVecTexture : public Uniform {
  public:
    UniformVecTexture(std::string name, std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>>&);
    ~UniformVecTexture();

    void  setValue(const std::vector<std::shared_ptr<Ahwassa::Texture>>& val);
    const std::vector<std::shared_ptr<Ahwassa::Texture>>& getValue();
    virtual int getNumberOfLocationsUsed() override { return 1; }
    virtual std::string getArrayPostfix();

    void bind() override;
    std::string getType() override { return "sampler2DArray"; }
    virtual bool isTexture() override { return true; }

  private:
    unsigned int _id;
    int _width;
    int _height;
    int _size;
  };
}