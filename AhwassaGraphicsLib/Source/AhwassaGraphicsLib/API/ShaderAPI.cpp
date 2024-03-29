#include "ShaderAPI.h"

#include <iostream>
#include <glm/glm.hpp>

#include "IyathuumCoreLib/API/API.h"
#include "IyathuumCoreLib/API/APIFunction.h"
#include "IyathuumCoreLib/API/FunctionRelay.h"

#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/AttributeDescription.h"
#include "AhwassaGraphicsLib/Uniforms/UniformFloat.h"
#include "AhwassaGraphicsLib/Vertex/PositionVertex.h"

namespace Ahwassa {
  ShaderAPI& ShaderAPI::instance() {
    static ShaderAPI api;
    return api;
  }

  ShaderAPI::~ShaderAPI() {

  }

  void ShaderAPI::add(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    createShader        (api, relay);
    createFloatUniform  (api, relay);
    setValueFloatUniform(api, relay);
    positionVertex      (api, relay);
  }
  
  void ShaderAPI::setValueFloatUniform(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    std::unique_ptr<Iyathuum::APIFunction> create = std::make_unique<Iyathuum::APIFunction>("setValueFloatUniform", [&relay, this](const nlohmann::json& input) {
      std::cout << "scripting:setValueFloatUniform" << std::endl;
      std::string name = input["Name"];
      float value = input["Value"];
      std::shared_ptr<UniformFloat> u = std::dynamic_pointer_cast<UniformFloat>(_uniforms[name]);
      u->setValue(value);
      return nlohmann::json();
      });
    create->setDescription(
      R"(
Sets a Float Value of a proxy that can be used in shaders.

Syntax:
  {
    'Name': 'Name',
    'Value': FloatValue,
  }
    )");
    api.addFunction(std::move(create));
  }

  void ShaderAPI::createFloatUniform(Iyathuum::API& api, Iyathuum::FunctionRelay& relay){
    std::unique_ptr<Iyathuum::APIFunction> create = std::make_unique<Iyathuum::APIFunction>("createFloatUniform", [&relay, this](const nlohmann::json& input) {
      std::cout << "scripting:createFloatUniform" << std::endl;
      std::string name = input["Name"];
      float value = input["Value"];
      auto u = std::make_shared<UniformFloat>(name);
      _uniforms[name] = u;
      u->setValue(value);
      return nlohmann::json();
      });
    create->setDescription(
      R"(
Creates a Float Value proxy that can be used in shaders.

Syntax:
  {
    'Name': 'Name',
    'Value': FloatValue,
  }
    )");
    api.addFunction(std::move(create));
  }

  void ShaderAPI::createShader(Iyathuum::API& api, Iyathuum::FunctionRelay& relay)
  {
    std::unique_ptr<Iyathuum::APIFunction> create = std::make_unique<Iyathuum::APIFunction>("createShader", [&relay, this](const nlohmann::json& input) {
      std::cout << "scripting:CreateShader" << std::endl;
      std::string name         = input["Name"];
      std::string VertexShader = input["VertexShader"];
      std::string PixelShader  = input["PixelShader"];
      
      std::vector<Uniform*>             uniform;
      std::vector<AttributeDescription> description;
      
      for (auto& desc : input["Attributes"]) {
        description.push_back(AttributeDescription(desc));
      }      
      for (auto& uniformName : input["Uniforms"]) {
        uniform.push_back(_uniforms[uniformName].get());
      }

      _programs[name] = std::make_unique<ShaderProgram>(description, uniform, VertexShader, PixelShader);
      return nlohmann::json();
    });
    create->setDescription(
    R"(
Creates a Shader.

Syntax:
  {
    'Name': 'Name',
    'VertexShader':'...',
    'PixelShader' :'...',
    'Attributes' : [AttributeDescription,...]
  }
  
  AttirbuteDescription
  {
    'Name' : 'Name'
    'Size' : Integer //Amount of the same (e.g. vec2 has 2)
    'Type' : 'Float/Char/UInt'
    'Instancing' : True/False //for instancing it has to be true. Default is false
  }
    )");
    api.addFunction(std::move(create));
  }

  void ShaderAPI::positionVertex(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    std::unique_ptr<Iyathuum::APIFunction> create = std::make_unique<Iyathuum::APIFunction>("positionVertex", [&relay, this](const nlohmann::json& input) {
      std::cout << "scripting:positionVertex" << std::endl;
      nlohmann::json result = nlohmann::json::array();
      for (auto& x : PositionVertex::getBinding())
        result.push_back(x.toJson());
      return result;
      });
    create->setDescription(
      R"(
Format for the Shader for Vertices with only Position.

Syntax:
  {
  }
    )");
    api.addFunction(std::move(create));
  }
}