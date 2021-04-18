#pragma once

#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {
  class Texture : public Uniform {
  public:
    Texture(std::string name, Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>* tex);
    Texture(std::string name, int width, int height);
    Texture(std::string name, unsigned int tex);
    virtual ~Texture() override;

    virtual bool isTexture()      override;
    virtual std::string getType() override;

    void         setTextureID(unsigned int tex);
    unsigned int getTextureID() const;

    void bind() override;
    void release();
  private:
    unsigned int _texture;
    bool   _released = false;
  };
}