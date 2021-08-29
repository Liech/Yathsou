#include "glmOctree.h"

namespace Iyathuum {
  glmOctree::glmOctree(const glmAABB<3>& volume, glmOctree* parent) {
    _parent = parent;
    _volume = volume;
    for (int i = 0; i < 8; i++)
      _children[i] = nullptr;
  }

  glmOctree::~glmOctree() {
    for (int i = 0; i < 8; i++)
      if (_children[i] != nullptr)
        delete _children[i];
  }

  glmAABB<3> glmOctree::subVolume(unsigned char childID) {    
    bool X = childID & 1;
    bool Y = (childID & 2) >> 1;
    bool Z = (childID & 4) >> 2;
    glm::vec3 pos  = _volume.getPosition();
    glm::vec3 size = _volume.getSize() / 2.0f;
    pos[0] = X ? pos[0] + size[0] : pos[0];
    pos[1] = Y ? pos[1] + size[1] : pos[1];
    pos[2] = Z ? pos[2] + size[2] : pos[2];
    return glmAABB<3>(pos, size);
  }

  std::vector<glmAABB<3>> glmOctree::dumpAABB() {
    std::vector<glmAABB<3>> result;
    dumpHelper(result);
    return result;
  }

  void glmOctree::dumpHelper(std::vector<glmAABB<3>>& result) {
    result.push_back(_volume);
    for (int i = 0; i < 8; i++)
      if (_children[i] != 0)
        _children[i]->dumpHelper(result);
  }

  
  std::set<std::shared_ptr<glmOctreeObject>> glmOctree::dumpObj() {
    std::set<std::shared_ptr<glmOctreeObject>> result;
    result = _content;
    for (int i = 0; i < 8; i++)
      if (_children[i] != 0) {
        auto sub = _children[i]->dumpObj();
        result.insert(sub.begin(), sub.end());
      }
    return result;  
  }

  void glmOctree::createChildren() {
    for (int i = 0; i < 8; i++)
      _children[i] = new glmOctree(subVolume(i),this);
  }

  void glmOctree::killChildren() {
    for (int i = 0; i < 8; i++)
      delete _children[i];
  }
  
  bool glmOctree::hasChildren() {
    return _children[0] != nullptr;
  }

  glmOctree* glmOctree::getLeaf(glm::vec3 position) {
    if (!hasChildren())
      return this;
    glm::vec3 center = _volume.getCenter();
    bool X = position[0] > center[0];
    bool Y = position[1] > center[1];
    bool Z = position[2] > center[2];

    int ix = (X?1:0) + (Y?2:0) + (Z?4:0);
    return _children[ix]->getLeaf(position);
  }

  void glmOctree::split() {
    createChildren();
    for (auto item : _content){
      glmOctree* tree = getLeaf(item->glmPosition());
      tree->_content.insert(item);
    }
    _content.clear();
  }

  void glmOctree::merge() {
    if (!hasChildren())
      return;

    for (auto& child : _children) {
      child->merge();
      _content.insert(child->_content.begin(), child->_content.end());
    }
    killChildren();
  }

  size_t glmOctree::contentCount() {
    size_t result = _content.size();
    if (hasChildren())
      for (int i = 0; i < 8; i++)
        result += _children[i]->contentCount();
    return result;
  }

  void glmOctree::add(std::shared_ptr<glmOctreeObject> obj) {
    glmOctree* tree = getLeaf(obj->glmPosition());
    tree->_content.insert(obj);
    if (tree->_content.size() > MaxContentAmount)
      tree->split();
  }

  void glmOctree::remove(std::shared_ptr<glmOctreeObject> obj) {
    glmOctree* tree = getLeaf(obj->glmPosition());
    tree->_content.erase(obj);
    if (tree->_parent && tree->_parent->contentCount() < MinContentAmount) {
      tree->_parent->merge();
    }
  }

  std::set<std::shared_ptr<glmOctreeObject>> glmOctree::findSphere(glm::vec3 pos, float radius) {
    std::set<std::shared_ptr<glmOctreeObject>> result;
    if (!hasChildren()) {
      for (auto x : _content) {
        glm::vec3 a = x->glmPosition();
        float dist = glm::distance(a,pos);
        if (dist <= radius)
          result.insert(x);
      }
    }
    else {
      for (int i = 0; i < 8; i++) {
        if (_children[i]->_volume.intersectsSphere(pos, radius)) {
          auto subResult = _children[i]->findSphere(pos, radius);
          result.insert(subResult.begin(), subResult.end());
        }
      }
    }
    return result;
  }

  glmAABB<3> glmOctree::aabb() const {
    return _volume;
  }

}