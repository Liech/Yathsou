#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"

namespace Ahwassa {
  class Camera {
  public:  
    Camera(std::string name, int width, int height);
  
    void bind();
    std::vector<Uniform*> getUniforms();
    std::string getName();

    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();

    glm::vec3 getPickRay(glm::vec2);
    glm::vec3 viewToWorldCoordTransform(int mouse_x, int mouse_y);
    glm::vec2 worldToViewCoordTransform(glm::vec3 pos);

    glm::vec2 getResolution();
    glm::vec3 getPosition  ();
    void      setPosition  (glm::vec3 v);
    glm::vec3 getUp        ();
    void      setUp        (glm::vec3 v);
    glm::vec3 getTarget    ();
    void      setTarget    (glm::vec3 v);
    glm::vec3 getDir       ();
    void      setDir       (glm::vec3 v);
    float     getFOV       ();
    void      setFOV       (float v);
    bool      is2D         ();
    void      set2D        (bool);
    float     getNearPlane ();
    float     getFarPlane  ();

    void                 set2DView(Iyathuum::glmAABB<2> view);
    Iyathuum::glmAABB<2> getView();

  private:  
    UniformMat4 _view       ;    
    UniformMat4 _projection ;
    UniformMat4 _invViewProj;
    UniformVec3 _cameraPos ;

    float                _fov      = 45;
    glm::vec3            _position = glm::vec3(4, 3, 3);
    glm::vec3            _up       = glm::vec3(0, 1, 0);
    glm::vec3            _target   = glm::vec3(0, 0, 0);
    int                  _width     ;
    int                  _height    ;
    bool                 _is2D     = false;
    Iyathuum::glmAABB<2> _view2D    ;
    std::string          _name;
  };
}