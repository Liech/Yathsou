#include "GeometryAPI.h"

#include <iostream>
#include <glm/glm.hpp>

#include "IyathuumCoreLib/API/API.h"
#include "IyathuumCoreLib/API/APIFunction.h"
#include "IyathuumCoreLib/API/FunctionRelay.h"

#include "AhwassaGraphicsLib/Geometry/BasicShapeGenerator.h"

namespace Ahwassa {
  GeometryAPI& GeometryAPI::instance() {
    static GeometryAPI api;
    return api;
  }

  GeometryAPI::~GeometryAPI() {

  }

  void GeometryAPI::add(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    generateCube(api, relay);
  }

  void GeometryAPI::generateCube(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    std::unique_ptr<Iyathuum::APIFunction> create = std::make_unique<Iyathuum::APIFunction>("generateCube", [&relay, this](const nlohmann::json& input) {
      std::cout << "scripting:getCube" << std::endl;
      nlohmann::json result;

      std::pair<std::vector<PositionNormalVertex>, std::vector<int>> vertexIndex = BasicShapeGenerator().getCube();
      for (auto& x : vertexIndex.first) {
        nlohmann::json sub;
        nlohmann::json position = nlohmann::json::array();
        position.push_back(x.position[0]);
        position.push_back(x.position[1]);
        position.push_back(x.position[2]);
        nlohmann::json normal   = nlohmann::json::array();
        normal.push_back(x.normal[0]);
        normal.push_back(x.normal[1]);
        normal.push_back(x.normal[2]);
        sub["position"] = position;
        sub["normal"]   = normal;
        result.push_back(sub);
      }

      return result;
      });
    create->setDescription(
      R"(
        Creates Cube

        input:
        {
           
        }

        output:
        [
          {
           position=[0,0,0],
           normal = [0,0,0]
          },
          ...
        ]
    )");
    api.addFunction(std::move(create));
  }
}