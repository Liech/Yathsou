#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Ahwassa {
  Camera::Camera(const std::string& name, const glm::ivec2& resolution):
    _view(name + "View"),
    _projection(name + "Projection"),
    _cameraPos(name + "Position"),
    _invViewProj(name + "inv") 
  {
    _name       = name;
    _resolution = resolution;
  }

  std::string Camera::getName() const {
    return _name;
  }

  void Camera::bind()
  {
    //http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
    glm::mat4 Projection = getProjectionMatrix();

    glm::mat4 View = getViewMatrix();

    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View;

    _view.setValue(View);
    _projection.setValue(Projection);
    _invViewProj.setValue(glm::inverse(mvp));
    _cameraPos.setValue(getPosition());
  }

  std::vector<Uniform*> Camera::getUniforms() {
    return std::vector<Uniform*> {&_view, & _projection, & _cameraPos, & _invViewProj};
  }

  glm::mat4 Camera::getProjectionMatrix() const {
    if (_is2D) {
      glm::vec2 p = _view2D.getPosition();
      return glm::ortho(p[0], p[0] + _view2D.getSize()[0], p[1] + _view2D.getSize()[1], p[1] + 0.0f, 0.1f, 100.0f);
    }
    return glm::perspective(glm::radians(getFOV()), (float)getResolution()[0] / getResolution()[1], getNearPlane(), getFarPlane());
  }

  glm::mat4 Camera::getViewMatrix() const{
    if (_is2D)
      return glm::lookAt(glm::vec3(0.f, 0.f, 2.0f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));
    return glm::lookAt(getPosition(), getTarget(), getUp());
  }

  glm::vec2 Camera::worldToViewCoordTransform(const glm::vec3& worldPos) const
  {
    //https://stackoverflow.com/questions/8491247/c-opengl-convert-world-coords-to-screen2d-coords
    glm::vec4 clipSpacePos = getProjectionMatrix() * (getViewMatrix() * glm::vec4(worldPos, 1.0));
    glm::vec3 ndcSpacePos = clipSpacePos / clipSpacePos.w;
    float x = ((ndcSpacePos[0] + 1.0) / 2.0) * getResolution()[0];
    float y = ((ndcSpacePos[1] + 1.0) / 2.0) * getResolution()[1];
    return glm::vec2(x, y);
  }

  // SCREEN SPACE: mouse_x and mouse_y are screen space
  glm::vec3 Camera::viewToWorldCoordTransform(int mouse_x, int mouse_y) const{
    // NORMALISED DEVICE SPACE
    double x = 2.0 * mouse_x / getResolution()[0] - 1;
    double y = 2.0 * mouse_y / getResolution()[1] - 1;

    // HOMOGENEOUS SPACE
    glm::vec4 screenPos = glm::vec4(x, -y, -1.0f, 1.0f);

    // Projection/Eye Space
    glm::mat4 ProjectView = getProjectionMatrix() * glm::lookAt(glm::vec3(0, 0, 0), glm::normalize(getTarget() - getPosition()), getUp());// getViewMatrix();
    glm::mat4 viewProjectionInverse = inverse(ProjectView);

    glm::vec4 worldPos = viewProjectionInverse * screenPos;
    return glm::vec3(worldPos);
  }

  glm::vec3 Camera::getPickRay(const glm::vec2& v) const {
    glm::vec3 worldMouse = viewToWorldCoordTransform(v[0], v[1]);
    return worldMouse;
  }

  bool Camera::is2D() const {
    return _is2D;
  }

  void  Camera::set2D(bool on) {
    _is2D = on;
  }

  void Camera::set2DView(const Iyathuum::glmAABB<2>& view) {
    _view2D = view;
  }

  Iyathuum::glmAABB<2> Camera::getView() const {
    return _view2D;
  }

  float Camera::getNearPlane() const {
    return 3; 
  }

  float Camera::getFarPlane() const {
    return 2000.0f;
  }

  glm::ivec2 Camera::getResolution() const{
    return _resolution; 
  }

  void Camera::setResolution(const glm::ivec2& newResolution) {

  }

  glm::vec3 Camera::getPosition() const{
    return _position; 
  }

  void Camera::setPosition(const glm::vec3& v) {
    _position = v; 
  }

  glm::vec3 Camera::getUp() const{
    return _up; 
  }

  void Camera::setUp(const glm::vec3& v) {
    _up = v; 
  }

  glm::vec3 Camera::getTarget() const {
    return _target; 
  }

  void Camera::setTarget(const glm::vec3& v) {
    _target = v; 
  }

  float Camera::getFOV() const {
    return _fov; 
  }

  void Camera::setFOV(float v) {
    _fov = v; 
  }

  glm::vec3 Camera::getDir() const {
    return glm::normalize(_target - _position);
  }

  void Camera::setDir(const glm::vec3& v) {
    setTarget(_position + v);
  }
}