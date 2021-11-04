#include "UnitsVisualization.h"

#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AthanahCommonLib/SupCom/SupComModelFactory.h"
#include "AthanahCommonLib/SupCom/SupComModel.h"

namespace Superb {
  UnitsVisualization::UnitsVisualization(Ahwassa::Window* window, Units& data) : 
    _window(window),
    _units(data) {
    //_models = std::make_shared<Athanah::SupComModelFactory>(data.getUnitFolder());
  }

  void UnitsVisualization::draw() {

  }

  void UnitsVisualization::debugDraw() {
    _window->renderer().box().start();
    for (auto unit : _units.getUnits())
      _window->renderer().box().drawDot(unit->agent->getPosition(), 0.5f, Iyathuum::Color(255, 128, 30));
    _window->renderer().box().end();
  }
}