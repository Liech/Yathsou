#pragma once

#include "SpatialHash.h"
#include "AABB.h"
#include "NMTree.h"
#include <set>
#include "../Util/Util.h"

namespace YolonaOss {
  
  template<size_t Dimension>
  class ObjectWithPosition {
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
  public:
    virtual vec getPosition() = 0;
  };

  template<typename Content, size_t Dimension,  size_t ArraySize = 2>
  class NMTreeSpatialHash : public ObjectWithAABB <Dimension>{
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    using content_ptr = std::shared_ptr<std::set < std::shared_ptr<Content>>>;
    using Tree = NMTree < content_ptr, ArraySize, Dimension, TreeMergeBehavior::Avg, double >;
    const size_t numberOfObjects = 10;
  public:

    virtual AABB<Dimension> getAABB() override {
      AABB<Dimension> result;
      result.setPosition(_position);
      result.setSize(vec(1.0f) * (float)_tree->getSize() * _scale);
      return result;
    }

    virtual void updateObject(std::shared_ptr<Content > object)  {
      removeObject(object);
      addObject(object);
    }

    virtual void addObject(std::shared_ptr<Content > object)  {
      addObject(object, _tree.get());
    }

    virtual void removeObject(std::shared_ptr<Content > object)  {
      assert(_removeMap.count(object) != 0);
      for (auto s : _removeMap[object]){
        content_ptr p = s->getContent();
        p.get()->erase(object);
        restoreBalance(s); 
        _removeMap.erase(object);
      }
    }

    virtual std::set<content_ptr> findObjects(vec  position)  {
      return {};
    }

    virtual std::set<content_ptr> findObjects(AABB<Dimension> position)  {
      return {};
    }

  private:
    void restoreBalance(Tree* current) {
       
    }

    void addObject(std::shared_ptr<Content> object, Tree* current) {
      if (current->isLeaf()) {
        if (current->getContent() == nullptr) {
          content_ptr ptr = std::make_shared < std::set<std::shared_ptr<Content>> >();
          current->setContent(ptr);
        }
        else if (current->getContent()->size() > numberOfObjects) {
          current->getContent()->insert(object);
          current->createChildren();
          for (auto s : *current->getContent())
            addObject(s, current);
          current->setContent(nullptr);          
          return;
        }
        current->getContent()->insert(object);
        _removeMap[object].insert(current);
      }
      else {
        vec p = object->getPosition();
        std::array<double, Dimension> v;
        for (size_t i = 0; i < Dimension; i++)
          v[i] = p[i];
        current = current->getLeaf(v);
        addObject(object, current);
      }
    }

    vec                                                  _position ;
    float                                                _scale    ;
    std::unique_ptr < Tree >                             _tree     ;
    std::map< std::shared_ptr<Content>, std::set<Tree*>> _removeMap;
  };
}