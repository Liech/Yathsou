#pragma once

#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {
  enum class CubeTextureReleaseBehavior {
    DeleteOnDeconstructor, KeepTextureOnDeconstructor
  };

  class CubeTexture : public Uniform {
  public:
    CubeTexture(const std::string& name, std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>>& tex);
    CubeTexture(const std::string& name, int width, int height);
    CubeTexture(const std::string& name, unsigned int tex, CubeTextureReleaseBehavior released = CubeTextureReleaseBehavior::KeepTextureOnDeconstructor);
    virtual ~CubeTexture() override;

    virtual bool isTexture()      const override;
    virtual std::string getType() const override;

    void         setTextureID(unsigned int tex);
    unsigned int getTextureID() const;

    void bind() override;
    void release();
  private:
    unsigned int _texture;
    bool   _released = false;
  };
}