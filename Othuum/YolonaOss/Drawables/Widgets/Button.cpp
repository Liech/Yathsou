#include "Button.h"

#include "glad/glad.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"

Button::Button()
{
  _position = glm::vec2(0, 0);
  _size = glm::vec2(100, 100);
  _name = "Def";
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
  RectangleRenderer::drawRectangle(_position,_size, _hovered? glm::vec3(0.8f, 0.8f, 0.8f): glm::vec3(0.4f, 0.4f,0.4f));
  RectangleRenderer::endTextRender();
  glm::vec2 textSize = TextRenderer::getTextSize(_name, 1);
  glm::vec2 spacing = (_size - textSize) / 2.0f;
  TextRenderer::startTextRender();
  TextRenderer::drawText(_name, _position + spacing , 1, glm::vec3(255, 255, 255));
  TextRenderer::endTextRender();  
}

void Button::mouseEnter() {
  _hovered = true;
};

void Button::mouseLeave() {
  _hovered = false;
};

void Button::mouseClick(glm::vec2 position, MouseKey k) {
  _clickedFunction();
};