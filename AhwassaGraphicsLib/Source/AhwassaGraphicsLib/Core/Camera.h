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
    Camera(const std::string& name, const glm::ivec2& resolution);
  
    void bind();
    std::vector<Uniform*> getUniforms();
    std::string getName() const;

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;

    glm::vec3 getPickRay(const glm::vec2&) const;
    glm::vec3 viewToWorldCoordTransform(int mouse_x, int mouse_y) const;
    glm::vec2 worldToViewCoordTransform(const glm::vec3& pos) const;

    glm::vec2 getResolution()             const;
    void      setResolution(const glm::ivec2&);
    glm::vec3 getPosition  ()             const;
    void      setPosition  (const glm::vec3& v);
    glm::vec3 getUp        ()             const;
    void      setUp        (const glm::vec3& v);
    glm::vec3 getCamUp     ()             const;
    glm::vec3 getTarget    ()             const;
    void      setTarget    (const glm::vec3& v);
    glm::vec3 getDir       ()             const;
    void      setDir       (const glm::vec3& v);
    glm::vec3 getRight     ()             const;
    void      setRight     (const glm::vec3& v);
    float     getFOV       ()             const;
    void      setFOV       (float v);
    bool      is2D         ()             const;
    void      set2D        (bool);
    float     getNearPlane ()             const;
    float     getFarPlane  ()             const;

    void                 set2DView(const Iyathuum::glmAABB<2>& view);
    Iyathuum::glmAABB<2> getView() const;

  private:  
    UniformMat4 _view       ;    
    UniformMat4 _projection ;
    UniformMat4 _invViewProj;
    UniformVec3 _cameraPos ;

    float                _fov      = 45;
    glm::vec3            _position = glm::vec3(4, 3, 3);
    glm::vec3            _up       = glm::vec3(0, 1, 0);
    glm::vec3            _right    = glm::vec3(0, 0, 0);
    glm::vec3            _target   = glm::vec3(0, 0, 0);
    glm::ivec2           _resolution;
    int                  _height    ;
    bool                 _is2D     = false;
    Iyathuum::glmAABB<2> _view2D    ;
    std::string          _name;
  };
}