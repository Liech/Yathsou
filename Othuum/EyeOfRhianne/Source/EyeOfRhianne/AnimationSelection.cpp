#include "AnimationSelection.h"

#include <glm/gtc/matrix_transform.hpp>
#include <AthanahCommonLib/SupCom/SupComModel.h>
#include "AezeselFileIOLib/STLWriter.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "ListSelection.h"
#include "Graphic.h"

AnimationSelection::AnimationSelection(Iyathuum::glmAABB<2> area,Graphic& graphic):_graphic(graphic){
  _area = area;
  _save = std::make_shared<Ahwassa::Button>("Save",
    Iyathuum::glmAABB<2>(area.getPosition(), glm::vec2(300, 50)) , [&]() {
    save();
  }, graphic.getWindow());
  _save->setVisible(false);
}

void AnimationSelection::setVisible(bool value) {
  _visible = value;
  if (_model)
    _save->setVisible(value);
  if (_list) {
    _list->setVisible(value);
    _pause->setVisible(value);
  }
}

bool AnimationSelection::isVisible() {
  return _visible;
}

void AnimationSelection::update() {
  if (_play)
    _time = std::fmod(_time + 0.01f, 1);

  if (_graphic._model != _model) {
    _time = 0;
    _model = _graphic._model;
    _currentAnimation = "None";
    std::vector<std::string> available =  _graphic._model->availableAnimations();

    std::vector<std::string> anims;
    anims.push_back("None");
    anims.insert(anims.begin(), available.begin(), available.end());
    if (anims.size() > 1) {
      _list = std::make_unique<ListSelection>(anims, anims, Iyathuum::glmAABB<2>(_area.getPosition() + glm::vec2(0,100), _area.getSize() - glm::vec2(0,100)), _graphic.getWindow(), [&](std::string u) {
        _currentAnimation = u;
        _time = 0;
      });
      _pause = std::make_shared<Ahwassa::Button>("Pause", Iyathuum::glmAABB<2>(_area.getPosition() + glm::vec2(0, 50), glm::vec2(300, 50)), [&]() {
        _play = !_play;
        if (_play)
          _pause->setText("Pause");
        else
          _pause->setText("Play");
      }, _graphic.getWindow());
    }
    else {
      _list = nullptr;
      _pause = nullptr;
    }
    if(_list) _list->setVisible(_visible);
    if (_pause) _pause->setVisible(_visible);
  }

  if (_graphic._mesh)
    _graphic._mesh->animation = getAnimation();
}

void AnimationSelection::draw() {
  if (_save)
    _save->draw();
  if (_list) {
    _list->draw();
    _pause->draw();
  }
}

std::vector<glm::mat4> AnimationSelection::getAnimation() {
  if (_currentAnimation == "None" || !_model)
    return std::vector<glm::mat4>();
  return _model->getAnimation(_currentAnimation, _model->getAnimationLength(_currentAnimation) * _time);
}

void AnimationSelection::save() {
  std::vector<glm::vec3> data;
  data.resize(_model->scm().indices.size() * 3);
  auto anim = getAnimation();
  for (size_t i = 0; i < _model->scm().indices.size(); i++) {
    const auto& v1 = _model->scm().vertecies[_model->scm().indices[i].a];
    const auto& v2 = _model->scm().vertecies[_model->scm().indices[i].b];
    const auto& v3 = _model->scm().vertecies[_model->scm().indices[i].c];
    auto mat1 = glm::mat4(1.0);
    auto mat2 = glm::mat4(1.0);
    auto mat3 = glm::mat4(1.0);

    if (_currentAnimation != "None") {
      mat1 = anim[v1.boneIndex[0]];
      mat2 = anim[v2.boneIndex[0]];
      mat3 = anim[v3.boneIndex[0]];
    }

    data[i * 3 + 0] = mat1 * glm::vec4(v1.position, 1);
    data[i * 3 + 1] = mat2 * glm::vec4(v2.position, 1);
    data[i * 3 + 2] = mat3 * glm::vec4(v3.position, 1);
  }
  Aezesel::STLWriter::write("Output.stl", data);
}