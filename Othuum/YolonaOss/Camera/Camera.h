#pragma once

#include "glm/glm.hpp"
#include <memory>
namespace YolonaOss {
  namespace GL {
    class Window;
  }
  namespace Camera {
    //im interested how it works out if two classes have the same name but different Namespaces. See GL::Camera.
    //It will be terrible, but maybe the fire looks nice.
   
    class Camera {
    public:
      Camera(int width, int height);

      glm::vec2 getResolution() { return glm::vec2(_width, _height); }
      
      glm::vec3 getPosition() { return _position; }
      void      setPosition(glm::vec3 v) { _position = v; }
      
      glm::vec3 getUp() { return _up; }
      void      setUp(glm::vec3 v) { _up = v; }
      
      glm::vec3 getTarget() { return _target; }
      void      setTarget(glm::vec3 v) { _target = v; }
      
      float     getFOV() { return _fov; }
      void      setFOV(float v) { _fov = v; }

      glm::mat4 getProjectionMatrix();
      glm::mat4 getViewMatrix();

      glm::vec3 getPickRay(float X, float Y);
      glm::vec3 Camera::viewToWorldCoordTransform(int mouse_x, int mouse_y);

      float getNearPlane() { return 0.1f; }
      float getFarPlane() { return 100.0f; }

      void fromCamera(YolonaOss::Camera::Camera* cam);
    private:
      float _fov = 45;
      glm::vec3 _position = glm::vec3(4, 3, 3);
      glm::vec3 _up = glm::vec3(0, 1, 0);
      glm::vec3 _target = glm::vec3(4, 0, 0);
      int _width ;
      int _height;
    };
    class CameraMode {
    public:
      virtual void load(std::shared_ptr<YolonaOss::Camera::Camera> camera, GL::Window* window) = 0;
      virtual void update() = 0;
    };
  }
}