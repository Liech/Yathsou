#pragma once

#include "../OpenGL/Drawable.h"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/Tree/NMTree.h"
#include "IyathuumCoreLib/Tree/NMTreeNeighbourIndex.h"
#include "IyathuumCoreLib/Tree/NMTreeDijkstra.h"
#include <memory>
#include "SelenNavigationLib/NavigationAgent.h"
#include "SelenNavigationLib/NavigationMap.h"
#include "../RTSComponents/Landscape.h"
#include "../RTSComponents/Unit.h"
#include "../OpenGL/DrawableList.h"
#include "../Drawables/Widgets/ListLayout.h"
#include "VishalaNetworkLib/Protocoll/Client/LobbyConnector.h"

namespace YolonaOss {
  template<size_t Dimension> class DijkstraMap;
  template<size_t Dimension> class GradientGridMap;
  template<size_t Dimension> class MapGroup; 
  namespace GL {
    class DrawSpecification;
  }
  namespace Widgets {
    class Slider;
  }
  using Tree =  Iyathuum::NMTree<bool, 2, 2, Iyathuum::TreeMergeBehavior::Max>;
  using TreeI = Iyathuum::NMTreeNeighbourIndex<bool, 2, 2, Iyathuum::TreeMergeBehavior::Max>;

  class Texture2Tree : public GL::Drawable {
    // Geerbt über Drawable
  public:
    Texture2Tree();
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    std::unique_ptr<Landscape<2>>                     _landscape;
    std::vector<std::shared_ptr<Unit<2>>>             _unit     ; 
    std::vector < std::shared_ptr<Selen::NavigationMap<2>>> _mapsForSlider;

    std::shared_ptr<Vishala::Client::LobbyConnector> _connector;
    std::unique_ptr<Vishala::Connection>             _connection = nullptr;
                                                     
                                                     
    GL::DrawSpecification*                           _spec = nullptr;
    std::function<bool(double, double)>              _mouseClick;
    GL::DrawableList                                 _drawableList;
    std::shared_ptr<Widgets::ListLayout>             _layout;

    void renderDiscomfort();
    void mouseClick(double x, double y);
    std::shared_ptr<Widgets::Slider> addSlider(std::string text, int id, double min, double max);
    glm::vec3 metaPos = glm::vec3(0, 0, 0);
    std::array<float, 20> _config;
  };
}