#pragma once

#include <IyathuumCoreLib/lib/glm/glm.hpp>

namespace Iyathuum
{
  template <size_t Dimension>
  struct Line
  {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
    vec start;
    vec end;
  };
}