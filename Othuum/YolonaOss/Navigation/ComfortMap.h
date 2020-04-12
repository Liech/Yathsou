#pragma once

#include <memory>
#include "NavigationMap.h"
#include "AuraHolder.h"
#include "../Util/Util.h"

namespace YolonaOss {
  template <size_t Dimension>
  class ComfortMap :public NavigationMap<Dimension> {
    using self = typedef ComfortMap<Dimension>;
  public:
    ComfortMap(std::shared_ptr<AuraHolder<Dimension>> grid) {
      _auras = grid;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    virtual vec getDirectionSuggestion(std::shared_ptr<Aura<Dimension>> obj) override {
      auto auras = _auras->findAuras(obj->getPosition(), 3);
      vec avg(0.0);
      for (auto aura : auras) {
        if (obj == aura)
          continue;
        avg += aura->getPosition();
      }
      if (auras.size() == 1) 
        return vec(0.0);
      avg /= (float)auras.size()-1;
      vec result = glm::normalize(avg - obj->getPosition());
      if (std::isnan(result[0]))
        return vec(0.0);

      return result;
    }

  private:

  private:
    std::shared_ptr<AuraHolder<Dimension>> _auras;
    vec                                    _target;
  };
}