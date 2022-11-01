#include "BufferAPI.h"

#include <iostream>
#include <glm/glm.hpp>

#include "IyathuumCoreLib/API/API.h"
#include "IyathuumCoreLib/API/APIFunction.h"
#include "IyathuumCoreLib/API/FunctionRelay.h"

#include "AhwassaGraphicsLib/BufferObjects/SVBO.h"
#include "AhwassaGraphicsLib/BufferObjects/IBO.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"

namespace Ahwassa {
  BufferAPI& BufferAPI::instance() {
    static BufferAPI api;
    return api;
  }

  BufferAPI::~BufferAPI() {

  }

  void BufferAPI::add(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    createVBO (api, relay);
    createIBO (api, relay);
    drawBuffer(api, relay);
  }

  void BufferAPI::drawBuffer(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    std::unique_ptr<Iyathuum::APIFunction> create = std::make_unique<Iyathuum::APIFunction>("drawBuffer", [&relay, this](const nlohmann::json& input) {
      std::cout << "scripting:drawBuffer" << std::endl;

      std::string vertexBufferName = input["VertexBuffer"];

      if (input.contains("IndexBuffer"))
      {
        std::string indexBufferName = input["IndexBuffer"];
        _ibos[indexBufferName]->draw(_vaos[vertexBufferName].get());
      }
      else
      {
        _vaos[vertexBufferName]->draw();
      }

      nlohmann::json result = nlohmann::json::array();
      return result;
      });
    create->setDescription(
      R"(
        Draws

        {
            "IndexBuffer" : "Name",  # optional
            "VertexBuffer" : "Name"
        }
    )");
    api.addFunction(std::move(create));
  }

  void BufferAPI::createIBO(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    std::unique_ptr<Iyathuum::APIFunction> create = std::make_unique<Iyathuum::APIFunction>("createIBO", [&relay, this](const nlohmann::json& input) {
      std::cout << "scripting:createIBO" << std::endl;
      nlohmann::json result = nlohmann::json::array();
      std::string name = input["Name"];
      std::vector<int> data;
      data.reserve(input["Data"].size());
      for (auto& x : input["Data"])
        result.push_back(x);
      _ibos[name] = std::make_shared<IBO>(data);
      return result;
      });
    create->setDescription(
      R"(
Creates an Index Buffer

Syntax:
  {
    "Name" : "Name",
    "Data" : [0,1,2,3,4,...]
  }
    )");
    api.addFunction(std::move(create));
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
          int dimensions = vertex[desc.getName()].size();
          for (int dimension = 0; dimension < dimensions; dimension++) {
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
      _vaos[input["Name"]] = std::make_shared<VAO>(buffer.get());
      return nlohmann::json();
      });
    create->setDescription(
      R"(
Creates an Vertex Buffer containing vertex data

Syntax:
  {
     "Name": "BufferName",
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