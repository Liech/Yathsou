#include "Fervor.h"

#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Background.h"

Fervor::Fervor()
{
  _preDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
  _postDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
  _preDrawables->addDrawable(std::make_shared<YolonaOss::Background>());
  _postDrawables->addDrawable(std::make_shared<YolonaOss::FPS>());
}

void Fervor::load(YolonaOss::GL::DrawSpecification* spec)
{
  _preDrawables ->load(spec);
  _postDrawables->load(spec);
}

void Fervor::update()
{
  _preDrawables ->draw();
  _postDrawables->draw();
}
