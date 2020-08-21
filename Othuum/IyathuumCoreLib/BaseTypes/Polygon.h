#pragma once

#include <IyathuumCoreLib/lib/glm/glm.hpp>

namespace Iyathuum
{
  template <size_t Dimension>
  struct Polygon
  {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
    std::vector<vec> points;
  };


}