#pragma once

#include "../OpenGL/Drawable.h"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/Tree/NMTree.h"
#include "IyathuumCoreLib/Tree/NMTreeNeighbourIndex.h"
#include "IyathuumCoreLib/Tree/NMTreeDijkstra.h"
#include <memory>
#include "../Navigation/NavigationAgent.h"
#include "../RTSComponents/Landscape.h"
#include "../RTSComponents/Unit.h"
#include "../OpenGL/DrawableList.h"
#include "../Drawables/Widgets/ListLayout.h"

namespace YolonaOss {
  template<size_t Dimension> class DijkstraMap;
  template<size_t Dimension> class GradientGridMap;
  template<size_t Dimension> class MapGroup; 
  namespace GL {
    class DrawSpecification;
  }
  using Tree =  Iyathuum::NMTree<bool, 2, 2, Iyathuum::TreeMergeBehavior::Max>;
  using TreeI = Iyathuum::NMTreeNeighbourIndex<bool, 2, 2, Iyathuum::TreeMergeBehavior::Max>;

  class Texture2Tree : public GL::Drawable {
    // Geerbt �ber Drawable
  public:
    Texture2Tree();
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    std::unique_ptr<Landscape<2>>                     _landscape;
    std::vector<std::shared_ptr<Unit<2>>>             _unit     ; 


    GL::DrawSpecification*                          _spec = nullptr;
    std::function<bool(double, double)>             _mouseClick;
    GL::DrawableList                                _drawableList;
    std::shared_ptr<Widgets::ListLayout>            _layout;

    void renderDiscomfort();
    void mouseClick(double x, double y);
    void addSlider(std::string text, int id, double min, double max);
    glm::vec3 metaPos = glm::vec3(0, 0, 0);
    std::array<float, 20> _config;
  };
}