#include "MainCharacterVisualization.h"
#include "MainCharacter.h"

#include "YolonaOss/Renderer/RectangleRenderer.h"

MainCharacterVisualization::MainCharacterVisualization(const MainCharacter& target)
  : _target(target)
{

}

void MainCharacterVisualization::load(YolonaOss::GL::DrawSpecification*)
{
}

void MainCharacterVisualization::draw()
{
  YolonaOss::RectangleRenderer::start();
  YolonaOss::RectangleRenderer::drawRectangle(_target.getPosition() - glm::vec2(3, 3), glm::vec2(6, 6), glm::vec3(1,0,0));
  YolonaOss::RectangleRenderer::end();
}
