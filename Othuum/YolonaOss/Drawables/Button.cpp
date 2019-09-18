#include "Button.h"

#include "glad/glad.h"
#include "../Renderer/RectangleRenderer.h"
#include "../Renderer/TextRenderer.h"

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
  RectangleRenderer::startTextRender();
  RectangleRenderer::drawRectangle(_position,_size, glm::vec3(128, 128, 128));
  RectangleRenderer::endTextRender();
  TextRenderer::startTextRender();
  TextRenderer::drawText(_name, _position[0], _position[1], 1, glm::vec3(255, 255, 255));
  TextRenderer::endTextRender();  
}
