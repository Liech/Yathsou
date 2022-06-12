#include "WindowAPI.h"

#include <iostream>

#include "IyathuumCoreLib/API/API.h"
#include "IyathuumCoreLib/API/APIFunction.h"
#include "IyathuumCoreLib/API/FunctionRelay.h"

namespace Ahwassa {
  WindowAPI& WindowAPI::instance() {
    static WindowAPI api;
    return api;
  }

  void WindowAPI::add(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    
    std::unique_ptr<Iyathuum::APIFunction> hamlo = std::make_unique<Iyathuum::APIFunction>("Hallo", [&relay](const nlohmann::json& input) {
      std::cout << "Hallo" << std::endl;
      std::cout << input.dump(4) << std::endl;
      std::cout << "Relay: " << relay.call(input["FUN"], 123) << std::endl;
      return input;
      });
    hamlo->setDescription("Hamlo :§");
    api.addFunction(std::move(hamlo));    
  }
}