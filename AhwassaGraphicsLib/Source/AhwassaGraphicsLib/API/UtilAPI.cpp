#include "UtilAPI.h"

#include <iostream>
#include <glm/glm.hpp>

#include "IyathuumCoreLib/API/API.h"
#include "IyathuumCoreLib/API/APIFunction.h"
#include "IyathuumCoreLib/API/FunctionRelay.h"

#include "AhwassaGraphicsLib/Util.h"

namespace Ahwassa {
  UtilAPI& UtilAPI::instance() {
    static UtilAPI api;
    return api;
  }

  UtilAPI::~UtilAPI() {

  }

  void UtilAPI::add(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    setDepthBufferTest(api, relay);
  }

  void UtilAPI::setDepthBufferTest(Iyathuum::API& api, Iyathuum::FunctionRelay& relay) {
    std::unique_ptr<Iyathuum::APIFunction> create = std::make_unique<Iyathuum::APIFunction>("setDepthBufferTest", [&relay, this](const nlohmann::json& input) {
      std::cout << "scripting:depthBuffer" << std::endl;
      nlohmann::json result;

      bool enabled = input;
      Util::setDepthTest(enabled);

      return result;
      });
    create->setDescription(
      R"(
        Enables / Disables Depth Buffer Test

        False/True
    )");
    api.addFunction(std::move(create));
  }
}