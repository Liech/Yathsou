#include "TextRender.h"
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <filesystem>
#include <iostream>
#include <map>
#include "../Renderer/TextRenderer.h"


TextRender::TextRender()
{
}


TextRender::~TextRender()
{
}

void TextRender::load(DrawSpecification*) {

}

void TextRender::draw() {
  TextRenderer::startTextRender();
  TextRenderer::drawText("Hello World", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
  TextRenderer::drawText("Yathsou", 1820.0f, 1060.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
  TextRenderer::endTextRender();
}