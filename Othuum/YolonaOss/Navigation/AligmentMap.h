#pragma once

#include <memory>
#include "NavigationMap.h"
#include "AuraHolder.h"
#include "../Util/Util.h"

namespace YolonaOss {
  template <size_t Dimension>
  class AligmentMap :public NavigationMap<Dimension> {
    using self = typedef DiscomfortMap<Dimension>;
  public:
    AligmentMap(std::shared_ptr<AuraHolder<Dimension>> grid) {
      _auras = grid;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    virtual vec getDirectionSuggestion(const vec currentPosition) override {     
      auto auras = _auras->findAuras(currentPosition, 2);
      vec avg(0.0);
      for (auto aura : auras) {
        avg += glm::normalize(aura->getOrientation());
      }

      return glm::normalize(avg);
    }
  private:

  private:
    std::shared_ptr<AuraHolder<Dimension>>     _auras  ;
    vec                                        _target;
  };
}