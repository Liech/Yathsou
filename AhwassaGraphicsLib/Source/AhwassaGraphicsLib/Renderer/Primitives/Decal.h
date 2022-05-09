#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Renderer/Primitives/IBox.h"

namespace Ahwassa {
  class Decal {
  public:
    Decal(const glm::mat4&, const Iyathuum::Color&);

    void setMatrix(const glm::mat4&);
    glm::mat4 getMatrix() const;

    void setColor(const Iyathuum::Color&);
    Iyathuum::Color getColor() const;

    void setTextureID(int textureID);
    int  textureID() const;

    glm::mat4 matrix() const;
  private:
    glm::mat4       _matrix;
    Iyathuum::Color _color;
    int             _textureID;
  };
}