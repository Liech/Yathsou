#include "PhysicNavigationMesh.h"
#include <set>
#include "PhysicEngine.h"

namespace Suthanus {
  PhysicNavigationTreeNode::PhysicNavigationTreeNode(glm::vec3 pos, std::shared_ptr<PhysicNavigationNode> n)
    :
    Iyathuum::glmOctreeObject(pos), _node(n)
  {
  }

  std::shared_ptr<PhysicNavigationNode> PhysicNavigationTreeNode::node() {
    return _node;
  }

  PhysicNavigationMesh::PhysicNavigationMesh(const PhysicEngine& engine,const Iyathuum::glmAABB<3>& volume,glm::vec3 seedStart,float sampleDistance, float climbingAngleDeg) 
  : _engine(engine),
  _volume(volume),
  _tree(volume){
    _sampleDistance = sampleDistance  ;
    _climbAngle     = climbingAngleDeg;
    initMesh(seedStart);
  }

  void PhysicNavigationMesh::initMesh(glm::vec3 seedStart) {
    glm::vec3 start   = _volume.getPosition();
    glm::vec3 end     = start + _volume.getSize();

    std::shared_ptr<PhysicNavigationNode> previousElement = nullptr;;
    std::vector<std::shared_ptr<PhysicNavigationNode>> previousRow(_volume.getSize()[0] / _sampleDistance,nullptr);
    size_t amountX = _volume.getSize()[0] / _sampleDistance;
    size_t amountZ = _volume.getSize()[2] / _sampleDistance;

    for (size_t x = 0; x < amountX;x++) {
      previousElement = nullptr;
      for (size_t z = 0;z < amountZ;z++)
      {
        glm::vec3 current = start + glm::vec3(_sampleDistance*x,0,_sampleDistance*z);
        glm::vec3 hit;
        bool ok = _engine.raycast(current, glm::vec3(0, 1, 0), hit) != nullptr;
        if (!ok) {
          previousElement = nullptr;
          previousRow[z]  = nullptr;
          continue;
        }
        std::shared_ptr<PhysicNavigationNode> node = std::make_shared<PhysicNavigationNode>();
        node->position = hit;
        _nodes.push_back(node);
        auto treeNode = std::make_shared<PhysicNavigationTreeNode>(node->position, node);
        _tree.add(treeNode);
        if (previousRow[z] != nullptr) {
          node          ->links.push_back(previousRow[z]);
          previousRow[z]->links.push_back(node);
        }
        if (previousElement != nullptr) {
          node->links.push_back(previousElement);
          previousElement->links.push_back(node);
        }
        previousElement = node;
        previousRow[z] = node;
      }
    }
  }

  std::vector<glm::vec3> PhysicNavigationMesh::getNodePositions() const{
    std::vector<glm::vec3> result;

    for (auto x : _nodes)
      result.push_back(x->position);

    return result;
  }

  std::vector<std::pair<glm::vec3, glm::vec3>> PhysicNavigationMesh::getLinks() const{
    std::set<std::shared_ptr<PhysicNavigationNode>> processedNodes;
    std::vector<std::pair<glm::vec3, glm::vec3>> result;

    for (auto& x : _nodes)
    {
      for (auto link : x->links)
      {
        //if (processedNodes.count(link) != 0)
        //  continue;
        result.push_back(std::make_pair(x->position,link->position));
      }
      processedNodes.insert(x);
    }

    return result;
  }

  std::shared_ptr<PhysicNavigationNode> PhysicNavigationMesh::findNext(glm::vec3 pos) const {
    std::set<std::shared_ptr<Iyathuum::glmOctreeObject>> objs = _tree.findSphere(pos, _sampleDistance * 2);
    std::vector<std::shared_ptr<PhysicNavigationTreeNode>> nodes;
    for (auto node : objs)
      nodes.push_back(std::dynamic_pointer_cast<PhysicNavigationTreeNode>(node));
    std::sort(nodes.begin(), nodes.end(), [&](const std::shared_ptr<PhysicNavigationTreeNode>& a, const std::shared_ptr<PhysicNavigationTreeNode>& b) -> bool
    {
      float la = glm::distance(a->glmPosition(), pos);
      float lb = glm::distance(b->glmPosition(), pos);
      return la < lb;
    });
    if (nodes.size() > 0)
      return nodes[0]->node();
    else
      return nullptr;
  }
}