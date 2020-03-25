#pragma once

#include "../OpenGL/Drawable.h"
#include "../structs/MultiDimensionalArray.h"
#include "../structs/NMTree.h"
#include "../structs/NMTreeNeighbourIndex.h"
#include "../structs/NMTreeDijkstra.h"
#include <memory>
#include "../Navigation/NavigationAgent.h"
#include "../RTSComponents/Landscape.h"
#include "../RTSComponents/Unit.h"

namespace YolonaOss {
  template<size_t Dimension> class DijkstraMap;
  template<size_t Dimension> class GradientGridMap;
  template<size_t Dimension> class MapGroup;
  namespace GL {
    class DrawSpecification;
  }
  using Tree = NMTree<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>;
  using TreeI = NMTreeNeighbourIndex<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>;

  class Texture2Tree : public GL::Drawable {
    // Geerbt �ber Drawable
  public:
    Texture2Tree();
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    std::unique_ptr<Landscape<2>>                     _landscape;
    std::unique_ptr<Unit<2>>                          _unit;


    GL::DrawSpecification*                          _spec;
    std::function<void(double, double)>             _mouseClick;


    void renderDiscomfort();
    void mouseClick(double x, double y);
    glm::vec3 metaPos = glm::vec3(0, 0, 0);
  };
}