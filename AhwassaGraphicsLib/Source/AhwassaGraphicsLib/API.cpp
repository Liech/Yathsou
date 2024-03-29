#include "API.h"

#include "IyathuumCoreLib/API/API.h"

#include "API/WindowAPI.h"
#include "API/ShaderAPI.h"
#include "API/BufferAPI.h"
#include "API/UtilAPI.h"
#include "API/GeometryAPI.h"

namespace Ahwassa {
  std::unique_ptr<Iyathuum::API> API::getAPI(Iyathuum::FunctionRelay& relay) {
    std::unique_ptr<Iyathuum::API> result = std::make_unique<Iyathuum::API>("Ahwassa");

    WindowAPI  ::instance().add(*result, relay);
    ShaderAPI  ::instance().add(*result, relay);
    BufferAPI  ::instance().add(*result, relay);
    UtilAPI    ::instance().add(*result, relay);
    GeometryAPI::instance().add(*result, relay);

    return std::move(result);
  }
}