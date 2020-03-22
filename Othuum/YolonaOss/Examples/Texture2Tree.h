#pragma once

#include "../OpenGL/Drawable.h"
#include "../structs/MultiDimensionalArray.h"
#include "../structs/NMTree.h"
#include "../structs/NMTreeNeighbourIndex.h"
#include "../structs/NMTreeDijkstra.h"
#include <memory>
#include "../Navigation/NavigationAgent.h"

namespace YolonaOss {
  template<size_t Dimension> class DijkstraMap;

  namespace GL {
    class DrawSpecification;
  }
  using Tree = NMTree<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>;
  using TreeI = NMTreeNeighbourIndex<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>;

  class Texture2Tree : public GL::Drawable {
    // Geerbt über Drawable
  public:
    Texture2Tree();
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    std::shared_ptr<MultiDimensionalArray<bool, 2>> _map;
    std::shared_ptr<Tree>                           _tree;
    std::shared_ptr<TreeI>                          _index;
    std::shared_ptr < DijkstraI<2>>                 _path = nullptr;
    std::shared_ptr< DijkstraMap<2> >               _agentMap;
    

    GL::DrawSpecification*                          _spec;
    std::function<void(double, double)>             _mouseClick;
    NavigationAgent<2>                              _agent;

    void mouseClick(double x, double y);
    glm::vec3 metaPos = glm::vec3(0, 0, 0);
  };
}