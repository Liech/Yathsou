#pragma once

#include <vector>
#include <set>
#include <memory>

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

namespace Iyathuum {
  class glmOctreeObject {
  public:
    glmOctreeObject(glm::vec3 p) : pos(p) {}
    virtual const glm::vec3& glmPosition() const { return pos; }
  private:
    glm::vec3 pos;
  };

  class glmOctree{
  public:
    const unsigned int MaxContentAmount = 9;
    const unsigned int MinContentAmount = 3;

    glmOctree(const glmAABB<3>& volume, glmOctree* parent = nullptr);
    ~glmOctree();

    glmAABB<3> aabb() const;
    std::vector<glmAABB<3>> dumpAABB();
    std::set<std::shared_ptr<glmOctreeObject>>  dumpObj();

    void add(std::shared_ptr<glmOctreeObject>);
    void remove(std::shared_ptr<glmOctreeObject>);

    std::set<std::shared_ptr<glmOctreeObject>> findSphere(const glm::vec3& pos, float radius) const;

  private:    
    void       split();
    void       merge();
    glmOctree* getLeaf(glm::vec3 position);
    void       createChildren();
    void       killChildren();
    bool       hasChildren() const;
    glmAABB<3> subVolume(unsigned char childID);
    size_t     contentCount();

    void       dumpHelper(std::vector<glmAABB<3>>&);

    glmOctree*                                    _parent = nullptr;
    glmOctree*                                    _children[8];
    glmAABB<3>                                    _volume     ;
    std::set<std::shared_ptr<glmOctreeObject>>    _content    ;
  };
}