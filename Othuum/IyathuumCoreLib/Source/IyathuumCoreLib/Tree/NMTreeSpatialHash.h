#pragma once

#include "SpatialHash.h"
#include "BaseTypes/AABB.h"
#include "NMTree.h"
#include <set>
#include <map>

namespace Iyathuum {
  
  template<size_t Dimension>
  class ObjectWithPosition {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    virtual vec getPosition() = 0;
  };

  template<typename Content, size_t Dimension,  size_t ArraySize = 2>
  class NMTreeSpatialHash : public ObjectWithAABB <Dimension>{
    using vec = glm::vec<Dimension, float, glm::defaultp>;
    using content_ptr = std::shared_ptr<std::set < std::shared_ptr<Content>>>;
    using Tree = NMTree < content_ptr, ArraySize, Dimension, TreeMergeBehavior::Avg, double >;
    
    const int numberOfObjects = 4;
    const int numberOfObjectsTolerance = 1;
  public:

    NMTreeSpatialHash(AABB<Dimension> location) {
      double size = location.getSize()[0];
      for (size_t i = 0; i < Dimension; i++)
        assert(size == location.getSize()[i]);

      std::array<double, Dimension> pos;
      for (size_t i = 0; i < Dimension; i++)
        pos[i] = location.getPosition()[i];

      _tree = std::make_unique<Tree>(nullptr,pos, size);
    }

    virtual AABB<Dimension> getAABB() override {
      return tree2AABB(_tree.get());
    }

    void updateObject(std::shared_ptr<Content > object)  {
      vec p;
      for (size_t i = 0; i < Dimension; i++)
        p[i] = object->getPosition()[i];
      if (_removeMap.count(object) != 0 && tree2AABB(_removeMap[object]).isInside(p))//nullptr
        return;
      removeObject(object);
      addObject(object);
    }

    void addObject(std::shared_ptr<Content > object)  {
      vec p;
      for (size_t i = 0; i < Dimension; i++)
        p[i] = object->getPosition()[i];
      if (tree2AABB(_tree.get()).isInside(p))
        addObject(object, _tree.get());
      if (_removeMap.count(object) == 0) {
        _outer.insert(object);
      }
    }

    void removeObject(std::shared_ptr<Content > object)  {
      if (_removeMap.count(object) == 0) {
        if (_outer.count(object) == 0)
          throw std::runtime_error("Not found");
        _outer.erase(object);
        return;
      }
      Tree* tree = _removeMap[object];
      content_ptr p = tree->getContent();
      p.get()->erase(object);
      _removeMap.erase(object);
      restoreBalance(tree);
    }

    std::set<std::shared_ptr<Content>> findRadius(vec pos, float radius) {
      std::set<std::shared_ptr<Content>> result = findRadius(pos, radius, _tree.get());
      for (auto r : _outer) {
        vec p;
        for (size_t i = 0; i < Dimension; i++)
          p[i] = r->getPosition()[i];
        if (glm::length(pos- p) < radius)
          result.insert(r);
      }
      return result;
    }


  private:

    AABB<Dimension> tree2AABB(Tree* tree) {
      AABB<Dimension> result;
      vec pos;
      auto posPre = tree->getPosition();
      for (size_t i = 0; i < Dimension; i++)
        pos[(int)i] = (float)posPre[(int)i];
      result.setPosition(pos);
      vec siz;
      for (size_t i = 0; i < Dimension; i++)
        siz[i] = tree->getSize();
      result.setSize(siz);
      return result;
    }

    std::set<std::shared_ptr<Content>> findRadius(vec pos, float radius, Tree* current) {
      AABB<Dimension> currentLocation = tree2AABB(current);
      bool intersects = currentLocation.intersectsCircle(pos, radius);
      if (!intersects)
        return {};
      else {
        if (current->isLeaf()) {
          if (current->getContent() == nullptr) 
            return {};
          else {
            std::set<std::shared_ptr<Content>> result;
            for (auto s : *current->getContent()) {
              vec p;
              for(size_t i = 0;i < Dimension;i++)
                p[i] = s->getPosition()[i];
              if (glm::length(pos-p) < radius)
                result.insert(s);
            }
            return result;
          }
        }
        else {
          std::set<std::shared_ptr<Content>> result;
          for (auto c : current->getAllChilds()) {
            auto subResult = findRadius(pos, radius, c);
            if(subResult.size() != 0)
              result.insert(subResult.begin(), subResult.end());
          }
          return result;
        }
      }
    }

    void restoreBalance(Tree* current) {      
      Tree* parent = current->getParent();
      if (parent == nullptr)
        return;
      std::vector<Tree::Leaf> leaves = parent->getLeafs();
      content_ptr all = std::make_shared<std::set<std::shared_ptr<Content>>>();
      for (auto leaf : leaves) {        
        if (leaf.link->getContent() == nullptr)
          continue;
        for (auto f : *leaf.link->getContent()) {
          all->insert(f);
        }
      }
      if (all->size() < numberOfObjects - numberOfObjectsTolerance) {
        parent->killChildren();
        parent->setContent(all);
        for (auto a : *all) {
          _removeMap[a] = parent;
        }
        restoreBalance(parent);
      }
    }    

    void addObject(std::shared_ptr<Content> object, Tree* current) {
      if (current->isLeaf()) {
        if (current->getContent() == nullptr) { //not used yet
          content_ptr ptr = std::make_shared < std::set<std::shared_ptr<Content>> >();
          current->setContent(ptr);
          current->getContent()->insert(object);
          assert(_removeMap.count(object) == 0);
          _removeMap[object] = current;
        }
        else if (current->getContent()->size() > numberOfObjects + numberOfObjectsTolerance && current->getSize() > 1e-5) { //full
          current->getContent()->insert(object);
          current->createChildren();
          auto toReassign = current->getContent();
          current->setContent(nullptr);
          for (auto c : current->getAllChilds())
            c->setContent(nullptr);
          for (auto s : *toReassign) {
            _removeMap.erase(s);
            vec p;
            for (size_t i = 0; i < Dimension; i++)
              p[i] = s->getPosition()[i];
            if (!tree2AABB(current).isInside(p))
              addObject(s);         //state is not uptodate
            else
              addObject(s, current);//state is uptodate
          }
          return;
        }
        else { //ok
          current->getContent()->insert(object);
          assert(_removeMap.count(object) == 0);
          _removeMap[object] = current;
        }
      }
      else { // is node
        vec p;
        for (size_t i = 0; i < Dimension; i++) {
          p[i] = object->getPosition()[i];
        }

        auto next = current->getLeaf(p);
        addObject(object, next);
      }
    }

    std::unique_ptr < Tree >                             _tree     ;
    std::map< std::shared_ptr<Content>, Tree*>           _removeMap;
    std::set < std::shared_ptr<Content>>                 _outer    ;
  };
}