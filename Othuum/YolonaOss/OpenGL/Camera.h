#pragma once

#include "Uniform.h"
#include "../glm/glm.hpp"
#include <vector>

class Camera {  
public:
  
  Camera(std::string name, int width, int height);

  void bind();
  
  glm::vec3 getPosition();
  void setPosition(glm::vec3 v);
  glm::vec3 getUp() { return _up; }
  void setUp(glm::vec3 v) { _up = v; }
  glm::vec3 getTarget() { return _target; }
  void setTarget(glm::vec3 v) { _target = v; }
  float getFOV() { return _fov; }
  void setFOV(float v) { _fov = v; }

  std::vector<Uniform*> getUniforms();

private:
  float _fov = 45;
  glm::vec3 _position = glm::vec3(4, 3, 3);
  glm::vec3 _up = glm::vec3(0,1,0);
  glm::vec3 _target = glm::vec3(0, 0, 0);
  int _width;
  int _height;

  UniformMat4 _view;
  UniformMat4 _projection;
  UniformMat4 _invViewProj;
  UniformVec3 _cameraPos;

  double _lastFrame;
};