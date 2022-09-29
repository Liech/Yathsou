#pragma once

#include <memory>
#include <map>
#include <string>

namespace Iyathuum {
  class API;
  class FunctionRelay;
}

namespace Ahwassa {
  class ShaderProgram;
  class Uniform;

  class ShaderAPI {
    public:
    static ShaderAPI& instance();

    ~ShaderAPI();

    void add(Iyathuum::API&, Iyathuum::FunctionRelay& relay);

    private:
      ShaderAPI() = default;

      void createFloatUniform(Iyathuum::API&, Iyathuum::FunctionRelay& relay);
      void createShader      (Iyathuum::API&, Iyathuum::FunctionRelay& relay);

      std::map<std::string, std::shared_ptr<Uniform>>       _uniforms;
      std::map<std::string, std::unique_ptr<ShaderProgram>> _programs;
  };
}