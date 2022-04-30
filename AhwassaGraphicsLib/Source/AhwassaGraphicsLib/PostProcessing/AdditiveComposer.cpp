#include "AdditiveComposer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Uniforms/UniformFloat.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"

namespace Ahwassa {
  AdditiveComposer::AdditiveComposer(Ahwassa::Window* window, std::vector<std::shared_ptr<Ahwassa::Texture>> textures, const glm::ivec2& resolution) : PostProcessingEffect("Composition",window,resolution) {
    _textures = textures;
    std::string vertex_shader_source = R"(
    out vec2 TexCoords;

    void main()
    {
      gl_Position = projection * vec4(position.xy, 0.0, 1.0);
      TexCoords = texture;
    }  
   )";

    std::string textureSampling = "";

    for (int i = 0; i < _textures.size(); i++)
      textureSampling += "vec4 tex" + std::to_string(i) + " = texture(" + _textures[i]->getName() + ", TexCoords);\n";

    for (int i = 0; i < _textures.size(); i++) {
      textureSampling += "result += tex" + std::to_string(i) + ".rgb * tex" + std::to_string(i) + ".a;\n";
    }

    std::string fragment_shader_source = R"(
     in vec2 TexCoords;    
     out vec4 color;

    
    void main()
    {    
      vec3 result = vec3(0,0,0);
       )" + textureSampling + R"(

      color = vec4(result, 1.0);
    }  
   )";

    std::vector<Ahwassa::Uniform*> uniforms = getUniforms();    

    for(auto t : _textures)
      uniforms.push_back(t.get());
    _shader = std::make_shared<Ahwassa::ShaderProgram>(Ahwassa::PositionTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void AdditiveComposer::draw() {
    if (!enabled())
      return;

    start();

    _shader->bind();

    end();
  }
}