#include "MainCharacter.h"

MainCharacter::MainCharacter()
{
  _position = glm::vec2(10, 10);
}

glm::vec2 MainCharacter::getPosition() const
{
  return _position;
}

void MainCharacter::inputLeft(){
  _position[0] -= 1;
}

void MainCharacter::inputRight(){
  _position[0] += 1;
}

void MainCharacter::inputDown(){
  _position[1] -= 1;
}

void MainCharacter::inputUp(){
  _position[1] += 1;
}

