#pragma once

#include "YolonaOss/Input/WASDInputable.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"

class MainCharacter : public YolonaOss::WASDInputable
{
public:
  MainCharacter();
  glm::vec2 getPosition() const;

  void inputLeft () override;
  void inputRight() override;
  void inputDown () override;
  void inputUp   () override;

private:
  glm::vec2 _position;
};