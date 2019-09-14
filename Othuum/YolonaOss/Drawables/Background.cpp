#include "Background.h"

#include "glad/glad.h"


Background::Background()
{
}


Background::~Background()
{
}

void Background::load(DrawSpecification*)
{
}

void Background::draw()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
