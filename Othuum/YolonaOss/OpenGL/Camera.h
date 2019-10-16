#pragma once

#include "Uniform.h"
#include "glm/glm.hpp"
#include <vector>
#include "../Camera/Camera.h"
namespace YolonaOss {

  namespace GL {
    class Camera : public YolonaOss::Camera::Camera{
    public:

      Camera(std::string name, int width, int height);
      Camera(std::string name, YolonaOss::Camera::Camera* cam);

      void bind();

      std::vector<Uniform*> getUniforms();

    private:

      UniformMat4 _view;
      UniformMat4 _projection;
      UniformMat4 _invViewProj;
      UniformVec3 _cameraPos;

      double _lastFrame;
    };
  }
}