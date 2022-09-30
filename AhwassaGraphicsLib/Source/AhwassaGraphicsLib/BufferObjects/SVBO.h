#pragma once

#include <vector>

#include "IVBO.h"
#include "AhwassaGraphicsLib/Core/AttributeDescription.h"

namespace Ahwassa {
  struct AttributeDescription;

  class SVBO : public IVBO{ //Soft VBO Or Scripting VBO im not sure
  public:
    SVBO(size_t size, const void* pos, const std::vector<AttributeDescription>&);
    virtual ~SVBO();

    virtual std::vector<AttributeDescription> getBinding() const override;

  private:
    int getStructSize();

    std::vector<AttributeDescription> description;
  };
}