#include "Graphic.h"

#include <filesystem>
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
#include "AhwassaGraphicsLib/PostProcessing/Bloom.h"

#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AthanahCommonLib/SupComMeshRendererDef.h"
#include "AthanahCommonLib/SkyBox.h"

Graphic::Graphic(Ahwassa::Window* window) {
  _window   = window;
  _composer = std::make_shared<Ahwassa::DeferredComposer>(_window, _window->getWidth(), _window->getHeight());
  _bloom    = std::make_shared<Ahwassa::Bloom>(_window, _window->getWidth(), _window->getHeight());
  _renderer = std::make_shared<Athanah::SupComMeshRendererDef>(_window->camera());

  _textures.push_back(_bloom->getResult());
  _textures.push_back(_composer->getResult());
  for (auto x : _composer->getRawTextures())
    _textures.push_back(x);
  _textures.push_back(_composer->getDepth());
}

void Graphic::draw() {
  _composer->start();
  if (_skyBox)
    _skyBox->draw();
  _renderer->draw();
  _composer->end();
  _bloom->draw(_composer->getResult(), _composer->getRawTextures()[3], 1);

  _window->renderer().texture().start();
  _window->renderer().texture().draw(*_textures[_renderedTexture], Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(_window->getWidth(), _window->getHeight())), true);
  _window->renderer().texture().end();
}

Ahwassa::Window* Graphic::getWindow() {
  return _window;
}

void Graphic::setModel(std::shared_ptr<Athanah::SupComModel> model) {
  _model = model;
  _mesh = std::make_shared<Athanah::SupComMesh>();
  _mesh->model = model;
  _mesh->teamColor = Iyathuum::Color(rand() % 255, rand() % 255, rand() % 255);
  _mesh->transformation = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
  _renderer->addMesh(_mesh);
}