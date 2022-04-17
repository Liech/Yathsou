#pragma once

#include <vector>
#include "SCA.h"
#include "SCM.h"
#include <glm/glm.hpp>

namespace Aezesel {
  class SupremeCommanderAnimator {
    //this class prefers readabillity and dependentlessness over performance (i hope it is readable though)
  public:
    SupremeCommanderAnimator(const SCA::data&, const SCM::data&);

    //usage:
    //multiply the result on each scm vertex according to their bone index
    //getMatrices(1)[SCM::data::vertecies::boneIndex[0]] * SCM::data::vertecies::position
    std::vector<glm::mat4> getMatrices(float time);
    float                  getDuration();
  private:
    std::vector<std::vector<int>> _parentChain;
    std::map<int, int>            _animMap;
    std::vector<glm::mat4>        _inverse;
    std::vector<glm::mat4>        _forward;

    const SCA::data& _animation;
    const SCM::data& _model    ;
  };
}