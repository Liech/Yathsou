#include "AnimationSelection.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "AthanahCommonLib/SupComModel.h"
#include "AezeselFileIOLib/STLWriter.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "ListSelection.h"


AnimationSelection::AnimationSelection(Ahwassa::Window* w) {
  _window = w;
  _save = std::make_unique<Ahwassa::Button>("Save",
    Iyathuum::glmAABB<2>(glm::vec2(300, w->getHeight() - 50), glm::vec2(150, 50)) , [&]() {
    save();
  }, w);
  _save->setVisible(false);
}

void AnimationSelection::setModel(std::shared_ptr<Athanah::SupComModel> newModel) {
  _model = newModel;
  _time = 0;
  _currentAnimation = "None";  

  std::vector<std::string> available = _model->availableAnimations();
  std::vector<std::string> anims;
  anims.push_back("None");
  anims.insert(anims.begin(), available.begin(), available.end());
  if (anims.size() > 1) {
    _list = std::make_unique<ListSelection>(anims, anims, Iyathuum::glmAABB<2>(glm::vec2(300, 0), glm::vec2(300, _window->getHeight() / 4)), _window, [&](std::string u) {
      _currentAnimation = u;
      _time = 0;
    });
    _pause = std::make_unique<Ahwassa::Button>("Pause", Iyathuum::glmAABB<2>(glm::vec2(450, _window->getHeight() - 50), glm::vec2(150, 50)), [&]() {
      _play = !_play;
      if (_play)
        _pause->setText("Pause");
      else
        _pause->setText("Play");
    }, _window);
  }
  else {
    _list = nullptr;
    _pause = nullptr;
  }
  _save->setVisible(true);
}

void AnimationSelection::update() {
  if (_play)
    _time = std::fmod(_time + 0.01f, 1);
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
    auto v1 = _model->scm().vertecies[_model->scm().indices[i].a];
    auto v2 = _model->scm().vertecies[_model->scm().indices[i].b];
    auto v3 = _model->scm().vertecies[_model->scm().indices[i].c];
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