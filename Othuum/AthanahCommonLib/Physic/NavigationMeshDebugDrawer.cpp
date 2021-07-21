#include "NavigationMeshDebugDrawer.h"

#include "SuthanusPhysicsLib/PhysicNavigationMesh.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Renderer/BoxRenderer.h"

namespace Athanah {
  NavigationMeshDebugDrawer::NavigationMeshDebugDrawer(const Suthanus::PhysicNavigationMesh& mesh, std::shared_ptr<Ahwassa::Camera> camera) {
    _links = mesh.getLinks();
    _nodes = mesh.getNodePositions();
    _renderer = std::make_shared<Ahwassa::BoxRenderer>(camera);

    for (size_t i = 0; i < _nodes.size(); i++) 
      _boxes.push_back(_renderer->newDot(_nodes[i], 7.0f, Iyathuum::Color(255, 255, 255)));
  }

  void NavigationMeshDebugDrawer::draw() {
    _renderer->draw();
  }
}