#include "UnitsVisualization.h"

#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AthanahCommonLib/SupCom/Gamedata/SupComModelFactory.h"
#include "AthanahCommonLib/SupCom/SupComModel.h"
#include "AthanahCommonLib/SupCom/SupComMeshRendererDef.h"
#include "AthanahCommonLib/SupCom/Blueprint/BlueprintDisplay.h"

namespace Superb {
  UnitsVisualization::UnitsVisualization(Ahwassa::Window* window, Athanah::Gamedata& gamedata, Units& data) :
    _window(window),
    _units(data),
    _gamedata(gamedata){
    _model = _gamedata.model().loadModel("UEL0201");
    _renderer = std::make_unique<Athanah::SupComMeshRendererDef>(_window->camera());
    auto mesh = std::make_shared<Athanah::SupComMesh>();
    mesh->model = _model;
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
      float unitScale = unit->blueprint->display().scale();
      glm::mat4 mat(1.0);
      mat = glm::translate(mat, unit->agent->getPosition());
      mat = glm::scale(mat, glm::vec3(unitScale, unitScale, unitScale));

      _meshes[i]->model = _model;
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
      _window->renderer().box().drawDot(unit->agent->getPosition(), 0.1f, Iyathuum::Color(255, 128, 30));
    _window->renderer().box().end();
  }
}