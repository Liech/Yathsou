#include "WindowAPI.h"

#include <iostream>
#include <glm/glm.hpp>

#include "IyathuumCoreLib/API/API.h"
#include "IyathuumCoreLib/API/APIFunction.h"
#include "IyathuumCoreLib/API/FunctionRelay.h"

#include <AhwassaGraphicsLib/Core/Window.h>

namespace Ahwassa {
  WindowAPI& WindowAPI::instance() {
    static WindowAPI api;
    return api;
  }

  WindowAPI::~WindowAPI() {

  }

  void WindowAPI::add(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    createWindow(api, relay);
  }

  void WindowAPI::createWindow(Iyathuum::API& api, Iyathuum::FunctionRelay & relay){
    std::unique_ptr<Iyathuum::APIFunction> create = std::make_unique<Iyathuum::APIFunction>("createWindow", [&relay, this](const nlohmann::json& input) {
      std::cout << "scripting:CreateWindow" << std::endl;
      std::string title = input["Title"];
      glm::ivec2 resolution = glm::ivec2(input["Resolution"][0], input["Resolution"][1]);
      size_t startup = input["Startup"];
      size_t update  = input["Update" ];
      size_t resize  = input["Resize" ];

      _window = std::make_unique<Window>(title, resolution);
      _window->Startup = [&relay, startup]() {relay.call(startup, nlohmann::json()); };
      _window->Update  = [&relay, update ]() {relay.call(update , nlohmann::json()); };

      _window->Resize  = [&relay, resize ](const glm::ivec2& resolution) {
        nlohmann::json res = nlohmann::json::array( { resolution[0],resolution[1]});
        relay.call(resize , res); 
      };
      
      _window->run();

      return input;
      });
    create->setDescription(R"(
Creates Window.

Syntax:
  {
    'Title': 'Name',
    'Resolution':[X,Y],
    'Startup':<Function()>,
    'Update':<Function()>,
    'Resize':<Function(list[2] resolution)>
  }
)");
    api.addFunction(std::move(create));
  }
}