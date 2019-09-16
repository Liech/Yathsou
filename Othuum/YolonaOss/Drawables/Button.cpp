#include "Button.h"

#include "glad/glad.h"


Button::Button()
{
}


Button::~Button()
{
}

void Button::load(DrawSpecification*)
{
}

void Button::draw()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
