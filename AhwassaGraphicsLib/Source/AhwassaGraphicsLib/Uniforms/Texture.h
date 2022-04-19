#pragma once

#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {
  enum class ReleaseBehavior {
    DeleteOnDeconstructor, KeepTextureOnDeconstructor
  };
  enum class TextureFormat {
    RGBA, RGBA32
  };

  class Texture : public Uniform {
  public:
    Texture(const std::string& name, Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>* tex, TextureFormat format = TextureFormat::RGBA);
    Texture(const std::string& name, const glm::ivec2& resolution, TextureFormat format = TextureFormat::RGBA);
    Texture(const std::string& name, unsigned int tex, ReleaseBehavior released = ReleaseBehavior::KeepTextureOnDeconstructor);
    virtual ~Texture() override;

    virtual bool isTexture()      const override;
    virtual std::string getType() const override;

    void         setTextureID(unsigned int tex);
    unsigned int getTextureID() const;

    std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> getImage();

    void bind() override;
    void release();
  private:
    unsigned int _texture;
    bool   _released = false;
  };
}