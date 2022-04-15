#include "Graphic.h"

#include <filesystem>
#include <glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Uniforms/CubeTexture.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
#include "AhwassaGraphicsLib/PostProcessing/AdditiveComposer.h"
#include "AhwassaGraphicsLib/PostProcessing/Bloom.h"
#include "AhwassaGraphicsLib/PostProcessing/CubeReflection.h"
#include "AhwassaGraphicsLib/Renderer/BoxRenderer.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"

#include "HaasScriptingLib/ScriptEngine.h"
#include "AhwassaGraphicsLib/Renderer/BasicTexture2DRenderer.h"
#include "AthanahCommonLib/SupCom/SupComMeshRendererDef.h"
#include "AthanahCommonLib/SkyBox.h"
#include "AthanahCommonLib/Map/MapRenderer.h"

Graphic::Graphic(Ahwassa::Window* window) {
  _window         = window;
  _scripts = std::make_shared<Haas::ScriptEngine>();
  _composer       = std::make_shared<Ahwassa::DeferredComposer>(_window, _window->getWidth(), _window->getHeight());
  _bloom          = std::make_shared<Ahwassa::Bloom>(_window, _window->getWidth(), _window->getHeight());
  _cubeReflection = std::make_shared<Ahwassa::CubeReflection  >(_window, _window->getWidth(), _window->getHeight());
  _renderer       = std::make_shared<Athanah::SupComMeshRendererDef>(_window->camera());
  _reflectionTexture = std::make_shared<Ahwassa::CubeTexture>("Reflection", 0);


  _textures.push_back(_bloom->getResult());
  _textures.push_back(_cubeReflection->getResult());
  _textures.push_back(_composer->getResult());
  for (auto x : _composer->getRawTextures())
    _textures.push_back(x);
  _textures.push_back(_composer->getDepth());
}

void Graphic::draw() {
  //if (_mesh)
  //  _mesh->transformation = glm::rotate(_mesh->transformation, 0.001f, glm::vec3(0, 1, 0));

  drawScene();
  _window->renderer().texture().start();
  _window->renderer().texture().draw(*_textures[_renderedTexture], Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(_window->getWidth(), _window->getHeight())), true);
  _window->renderer().texture().end();

}

void Graphic::drawScene() {
  _composer->start();
  if (_skyBox)
    _skyBox->draw();
  if (_mapRenderer)
    _mapRenderer->draw(*_mapMesh);
  _renderer->draw();
  getWindow()->renderer().draw();
  _composer->end();
  _cubeReflection->setTexture(_reflectionTexture);
  _cubeReflection->draw(_window->camera()->getPosition(), _composer->getResult(), _composer->getRawTextures()[3], _composer->getRawTextures()[0], _composer->getRawTextures()[1], 0);
  if (_bloomEnabled)
    _bloom->draw(_cubeReflection->getResult(), _composer->getRawTextures()[3], 1);
}

std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> Graphic::screenshot() {
  _window->renderer().texture().start();
  _window->renderer().texture().draw(*_textures[_renderedTexture], Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(_window->getWidth(), _window->getHeight())), true);
  _window->renderer().texture().end();

  return _textures[_renderedTexture]->getImage();
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