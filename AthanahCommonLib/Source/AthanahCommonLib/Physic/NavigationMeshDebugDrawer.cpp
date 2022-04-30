#include "NavigationMeshDebugDrawer.h"

#include "SuthanusPhysicsLib/PhysicNavigationMesh.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
//#include "AhwassaGraphicsLib/Renderer/Private/BoxRenderer.h"
#include "AhwassaGraphicsLib/Renderer/Primitives/Dot.h"
#include "AhwassaGraphicsLib/Renderer/Primitives/Line.h"


namespace Athanah {
  NavigationMeshDebugDrawer::NavigationMeshDebugDrawer(const Suthanus::PhysicNavigationMesh& mesh, std::shared_ptr<Ahwassa::Camera> camera) {
    throw std::runtime_error("Update to new RenderAPI");
    _links = mesh.getLinks();
    _nodes = mesh.getNodePositions();
    //_renderer = std::make_shared<Ahwassa::BoxRenderer>(camera);

    //for (size_t i = 0; i < _nodes.size(); i++) {
    //  std::shared_ptr<Ahwassa::Dot> ptr = _renderer->newDot(_nodes[i], 0.1f, Iyathuum::Color(255, 255, 255));
    //  _boxes.push_back(std::dynamic_pointer_cast<Ahwassa::IBox>(ptr));
    //}
    //for (size_t i = 0; i < _links.size(); i++) {
    //  std::shared_ptr<Ahwassa::Line> ptr = _renderer->newLine(_links[i].first, _links[i].second, 0.07f, Iyathuum::Color(0, 255, 255));
    //  _boxes.push_back(std::dynamic_pointer_cast<Ahwassa::IBox>(ptr));
    //}
  }

  void NavigationMeshDebugDrawer::draw() {
    //_renderer->draw();
  }
}