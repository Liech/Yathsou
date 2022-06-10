#include "WindowAPI.h"

#include <iostream>

#include "IyathuumCoreLib/API/API.h"
#include "IyathuumCoreLib/API/APIFunction.h"

namespace Ahwassa {
  WindowAPI& WindowAPI::instance() {
    static WindowAPI api;
    return api;
  }

  void WindowAPI::add(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    
    std::unique_ptr<Iyathuum::APIFunction> hamlo = std::make_unique<Iyathuum::APIFunction>("Hallo", [](const nlohmann::json&) {
      std::cout << "Hallo" << std::endl;
      return 0;
      });
    hamlo->setDescription("Hamlo :§");
    api.addFunction(std::move(hamlo));    
  }
}