#include "UnitsVisualization.h"

#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AthanahCommonLib/SupCom/Gamedata/SupComModelFactory.h"
#include "AthanahCommonLib/SupCom/SupComModel.h"
#include "AthanahCommonLib/SupCom/SupComMeshRendererDef.h"
#include "AthanahCommonLib/SupCom/Blueprint/BlueprintDisplay.h"
#include "AthanahCommonLib/SupCom/Blueprint/BlueprintGeneral.h"
#include "AthanahCommonLib/SupCom/Blueprint/BlueprintPhysic.h"
#include "AthanahCommonLib/Physic/BoxVisualization.h"
#include "AthanahCommonLib/SupCom/Blueprint/Blueprint.h"
#include "AthanahCommonLib/SupCom/Blueprint/BlueprintDisplay.h"
#include "SuthanusPhysicsLib/Objects/Box.h"

namespace Superb {
  UnitsVisualization::UnitsVisualization(Ahwassa::Window* window, Athanah::Gamedata& gamedata, UnitsOld& data) :
    _window(window),
    _units(data),
    _gamedata(gamedata){
    _renderer = std::make_unique<Athanah::SupComMeshRendererDef>(_window->camera());
    auto mesh = std::make_shared<Athanah::SupComMesh>();
    mesh->teamColor = Iyathuum::Color(255,255,255,255);
    mesh->transformation = glm::mat4(1.0);
    _meshes.push_back(mesh);
  }

  void UnitsVisualization::draw() {
    _meshes.resize(_units.getUnits().size());
    size_t i = 0;
    for (auto unit : _units.getUnits()) {      
      bool addIt = false;
      if (_meshes[i] == nullptr) {
        _meshes[i] = std::make_shared<Athanah::SupComMesh>();
        addIt = true;
      }
      float unitScale = unit->getBlueprint()->display().scale();
      glm::mat4 mat = unit->getTransformation();      
      mat = glm::translate(mat, glm::vec3(0, -unit->getBlueprint()->physic().meshExtents()[1]/2.0f, 0));
      mat = glm::scale(mat, glm::vec3(unitScale, unitScale, unitScale));

      _meshes[i]->model = _gamedata.model().loadModel(unit->getID());
      _meshes[i]->teamColor = Iyathuum::Color(255, 255, 255, 255);
      _meshes[i]->transformation = mat;
      _meshes[i]->animation = { glm::mat4(1.0),glm::mat4(1.0),glm::mat4(1.0),glm::mat4(1.0),
      glm::mat4(1.0), glm::mat4(1.0), glm::mat4(1.0), glm::mat4(1.0),
      glm::mat4(1.0), glm::mat4(1.0), glm::mat4(1.0), glm::mat4(1.0),
      glm::mat4(1.0), glm::mat4(1.0), glm::mat4(1.0), glm::mat4(1.0) };
      if (addIt)
        _renderer->addMesh(_meshes[i]);
      i++;
    }
    _renderer->draw();

  }

  void UnitsVisualization::debugDraw() {
    _window->renderer().box().start();
    for (auto unit : _units.getUnits())
    {
      auto pos = unit->getPosition();
      Athanah::BoxVisualization::draw(unit->getPhysic(), Iyathuum::Color(255, 128, 30), _window);
    }
    _window->renderer().box().end();
  }
}