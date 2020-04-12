#pragma once

#include <memory>
#include "NavigationMap.h"
#include "AuraHolder.h"
#include "../Util/Util.h"

namespace YolonaOss {
  template <size_t Dimension>
  class DiscomfortMap :public NavigationMap<Dimension> {
    using self = typedef DiscomfortMap<Dimension>;
  public:
    DiscomfortMap(std::shared_ptr<AuraHolder<Dimension>> grid) {
      _auras   = grid   ;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    virtual vec getDirectionSuggestion(std::shared_ptr<Aura<Dimension>> obj) override {
      const float radius = 4;
      auto auras = _auras->findAuras(obj->getPosition(), radius);
      vec result(0.0);
      for (auto aura : auras) {
        if (aura == obj)
          continue;
        result += aura->getPosition() - obj->getPosition();
      }
      result /= auras.size()-1;
      result /= radius;
      
      float len = 1.0 - glm::length(result);
      len *= len;
      if (std::isnan(glm::normalize(result)[0]))
        return vec(0.0);
      result = glm::normalize(result) * len;
      
      return -result*2.0f;
    }
  private:

  private:
    std::shared_ptr<AuraHolder<Dimension>>     _auras  ;
    vec                                        _target ;
  };
}