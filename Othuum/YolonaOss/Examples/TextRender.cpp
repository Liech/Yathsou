#include "TextRender.h"
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <filesystem>
#include <iostream>
#include <map>
#include "../Renderer/TextRenderer.h"
#include "..//Renderer/RectangleRenderer.h"

TextRender::TextRender()
{
}


TextRender::~TextRender()
{
}

void TextRender::load(DrawSpecification*) {

}

void TextRender::draw() {
  RectangleRenderer::startTextRender();
  RectangleRenderer::drawRectangle(glm::vec2(50, 50), glm::vec2(50, 100), glm::vec3(255, 0, 0));
  RectangleRenderer::endTextRender();
}