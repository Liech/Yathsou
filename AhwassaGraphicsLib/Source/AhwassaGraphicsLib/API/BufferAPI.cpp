#include "BufferAPI.h"

#include <iostream>
#include <glm/glm.hpp>

#include "IyathuumCoreLib/API/API.h"
#include "IyathuumCoreLib/API/APIFunction.h"
#include "IyathuumCoreLib/API/FunctionRelay.h"

#include "AhwassaGraphicsLib/BufferObjects/SVBO.h"

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

      std::vector<AttributeDescription> description;
      for (auto& x : input["Description"])
        description.push_back(AttributeDescription(x));

      int structSize = 0;
      for (auto& x : description)
        structSize += x.getSize();

      const nlohmann::json& vertecies = input["Data"];
      size_t amountVertices = vertecies.size();

      std::vector<unsigned char> rawData;
      rawData.resize(amountVertices * structSize);
      size_t position = 0;
      for (size_t i = 0; i < amountVertices; i++) {
        const nlohmann::json& vertex = vertecies[i];
        for (auto& desc : description) {
          int dimensions = desc.getSize();
          for (int dimension = 0; i < dimensions; dimension++) {
            if (desc.getType() == AttributeDescription::DataType::Char) {
              int data;
              if (dimensions == 1)
                data = vertex[desc.getName()];
              else
                data = vertex[desc.getName()][dimension];
              *(rawData.data() + position) = (char)data;

              const int charSize = 1;
              position += charSize;
            }
            else if (desc.getType() == AttributeDescription::DataType::Float) {
              float data;
              if (dimensions == 1)
                data = vertex[desc.getName()];
              else
                data = vertex[desc.getName()][dimension];
              *(rawData.data() + position) = data;

              const int floatSize = 4;
              position += floatSize;
            }
            else if (desc.getType() == AttributeDescription::DataType::UInt) {
              unsigned int data;
              if (dimensions == 1)
                data = vertex[desc.getName()];
              else
                data = vertex[desc.getName()][dimension];
              *(rawData.data() + position) = data;

              const int uintSize = 4;
              position += uintSize;
            }
          }
        }
      }
      std::shared_ptr<SVBO> buffer = std::make_shared<SVBO>(amountVertices, rawData.data(), description);
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