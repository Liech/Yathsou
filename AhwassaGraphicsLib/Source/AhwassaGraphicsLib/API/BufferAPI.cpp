#include "BufferAPI.h"

#include <iostream>
#include <glm/glm.hpp>

#include "IyathuumCoreLib/API/API.h"
#include "IyathuumCoreLib/API/APIFunction.h"
#include "IyathuumCoreLib/API/FunctionRelay.h"

#include "AhwassaGraphicsLib/BufferObjects/VBO.h"

namespace Ahwassa {
  BufferAPI& BufferAPI::instance() {
    static BufferAPI api;
    return api;
  }

  BufferAPI::~BufferAPI() {

  }

  void BufferAPI::add(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    createVBO(api, relay);
  }

  void BufferAPI::createVBO(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    std::unique_ptr<Iyathuum::APIFunction> create = std::make_unique<Iyathuum::APIFunction>("createVBO", [&relay, this](const nlohmann::json& input) {
      std::cout << "scripting:createVBO" << std::endl;

      std::vector<AttributeDescription> desc;
      for (auto& x : input["Description"])
        desc.push_back(AttributeDescription(x));

      int structSize = 0;
      for (auto& x : desc)
        structSize += x.getSize();

      const nlohmann::json& vertecies = input["Data"];

      std::vector<unsigned char> rawData;

      throw std::runtime_error("Raw data out of serialized data is hard :(");

      std::shared_ptr<IVBO> buffer = std::make_shared<IVBO>(vertecies.size(), structSize, rawData.data());
      _vbos[input["Name"]] = buffer;
      return nlohmann::json();
      });
    create->setDescription(
      R"(
Creates an Vertex Buffer containing vertex data

Syntax:
  {
     "Description" : [{"Name": "position", "Type" : "Float", "Size": 3}, {"Name": "Other",...],
     "Data" : [
       {"position" : [0.0,0.0,0.0]}, "Other" : ...}
       {"position" : [1.0,0.0,0.0]}, "Other" : ...}
       ...
     ]
  }
    )");
    api.addFunction(std::move(create));
  }
}