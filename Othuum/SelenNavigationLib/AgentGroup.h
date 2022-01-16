//#pragma once
//
//#include "AgentMovementInterface.h"
//
//namespace Selen {
//  template <size_t Dimension>
//  class AgentGroup {
//  public:
//    using vec = glm::vec<Dimension, float, glm::defaultp>;
//
//    AgentGroup() {
//
//    }
//    virtual ~AgentGroup() = default;
//
//    void setDimensionMask(const std::array<bool, Dimension>& mask) {
//      _dimensionMask = mask;
//    }
//    
//    void setDestination(const vec& destination) {
//      _destination = destination;
//    }
//
//    void addMember(std::shared_ptr < AgentMovementInterface<Dimension> member) {
//      _members.insert(member);
//    }
//
//
//  private:
//    std::set<std::shared_ptr<AgentMovementInterface<Dimension>>> _members;
//
//    vec _destination;
//
//    using vec = glm::vec<Dimension, float, glm::defaultp>;
//    //determines which dimension is navigatable by the units
//    std::array<bool, Dimension> _dimensionMask = std::numeric_limits<unsigned int>::max();
//  };
//}