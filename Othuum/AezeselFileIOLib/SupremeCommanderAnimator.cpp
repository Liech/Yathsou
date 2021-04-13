#include "SupremeCommanderAnimator.h"

namespace Aezesel {
  SupremeCommanderAnimator::SupremeCommanderAnimator(const SCA::data& animation, const SCM::data& model) : _model(model), _animation(animation){

    _inverse.resize(_model.bones.size());
    _forward.resize(_model.bones.size());
    for (int i = 0; i < _inverse.size(); i++) {
      _inverse[i] = _model.bones[i].relativeInverseMatrix;
      _forward[i] = glm::inverse(_model.bones[i].relativeInverseMatrix);
    }

    for (int i = 0; i < _model.bones.size(); i++) {
      std::vector<int> chain;
      chain.push_back(i);

      while (_model.bones[chain.back()].parentIndex != -1)
        chain.push_back(_model.bones[chain.back()].parentIndex);
      _parentChain.push_back(chain);
    }

    std::map<std::string, int> preMap;
    for (int i = 0; i < _animation.boneNames.size(); i++)
      preMap[_animation.boneNames[i]] = i;
    for (int i = 0; i < _model.boneNames.size(); i++)
    {
      if (preMap.count(_model.bones[i].name) != 0)
        _animMap[i] = preMap[_model.bones[i].name] + 1;
      else
        _animMap[i] = 0;
    }
  }


  std::vector<glm::mat4> SupremeCommanderAnimator::getMatrices(float time) {
    //this function is not really fast. But somewhat correct.
    //faster things could be developed based on this.

    std::map<int, int>& animMap = _animMap;
    std::vector<glm::mat4>& inverse = _inverse;
    std::vector<glm::mat4>& forward = _forward;
    std::vector<std::vector<int>>& parentChain = _parentChain;

    int frameno = (int)((time / _animation.duration) * (_animation.animation.size() - 1)) + 1;
    const Aezesel::SCA::frame& frame = _animation.animation[frameno];

    std::vector<glm::mat4> rotation;
    rotation.resize(frame.bones.size());
    for (int i = 0; i < frame.bones.size(); i++)
    {
      glm::quat iden = glm::identity<glm::quat>();
      glm::quat rot = glm::normalize(frame.bones[i].rotation);
      glm::mat4 sub = Aezesel::SCA::QuatToMat(rot);
      rotation[i] = sub;
    }

    std::vector<glm::mat4> translation;
    translation.resize(frame.bones.size());
    for (int i = 0; i < frame.bones.size(); i++)
    {
      glm::mat4 sub = glm::mat4(1.0);
      sub = glm::translate(sub, frame.bones[i].position);
      translation[i] = sub;
    }

    auto r = [&](int x) {
      if (rotation.size() <= x)
        return glm::mat4(1);
      if (animMap[x] >= rotation.size())
        return glm::mat4(1);
      return translation[animMap[x]] * rotation[animMap[x]];
    };

    std::vector<glm::mat4> result;
    result.resize(_model.bones.size());

    for (int i = 0; i < result.size(); i++) {
      glm::mat4 fwd = inverse[i];
      for (int chainIndex = 0; chainIndex < parentChain[i].size(); chainIndex++) {
        int p = parentChain[i][chainIndex];
        fwd = r(p) * fwd;
      }
      result[i] = fwd;
    }

    return result;
  }

  float SupremeCommanderAnimator::getDuration() {
    return _animation.duration;
  }
}