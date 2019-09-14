#include "DrawableList.h"



DrawableList::DrawableList()
{
}


DrawableList::~DrawableList()
{
}

void DrawableList::addDrawable(std::shared_ptr<Drawable> drawable) {
  _drawables.push_back(drawable);
}

void DrawableList::load(DrawSpecification* d)
{
  for (int i = 0; i < _drawables.size(); i++) 
    _drawables[i]->load(d);
}

void DrawableList::draw()
{
  for (int i = 0; i < _drawables.size(); i++)
    _drawables[i]->draw();
}
