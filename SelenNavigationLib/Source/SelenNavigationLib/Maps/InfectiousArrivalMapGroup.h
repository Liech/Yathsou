#pragma once

#include <glm/glm.hpp>
#include "MapGroup.h"

namespace Selen {

  //only asks submaps for guidance when the unit is not yet arrived
  //if a unit is near enough to the target it is marked as arrived
  //if a unit is near an unit of this map that has arrived it is marked as arrived too
  template <size_t Dimension>
  class InfectiousArrivalMapGroup : public MapGroup<Dimension> {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    InfectiousArrivalMapGroup(std::shared_ptr<NavigationAgentManager<Dimension>> agents) : MapGroup<Dimension>(){
      _agents = agents;
    }

    virtual void setTarget(const vec target) override
    {
      MapGroup<Dimension>::setTarget(target);
      _arrivedUnits.clear();
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      if (_arrivedUnits.count(obj)) {
        return -obj->getVelocity();
      }
      else if (glm::length(MapGroup<Dimension>::_target - obj->getPosition()) < 0.5f) {
        _arrivedUnits.insert(obj);
        return -obj->getVelocity();
      }
      else {
        const float radius = 1;
        auto agents = _agents->findAgents(obj->getPosition(), radius);
        for (auto a : agents)
          if (isArrived(a.get())) {
            _arrivedUnits.insert(obj);
            return -obj->getVelocity();
          }
      }

      return MapGroup<Dimension>::getVelocitySuggestion(obj);
    }

    bool isArrived(NavigationAgent<Dimension>* obj) {
      return _arrivedUnits.count(obj) != 0;
    }

  private:
    std::set<NavigationAgent<Dimension>*>               _arrivedUnits;
    std::shared_ptr<NavigationAgentManager<Dimension>>  _agents      ;
  };
}