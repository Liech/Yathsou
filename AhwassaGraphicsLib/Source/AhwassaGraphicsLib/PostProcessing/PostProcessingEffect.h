#pragma once

#include <memory>

#include "AhwassaGraphicsLib/BufferObjects/VBO.h"
#include "AhwassaGraphicsLib/Vertex/PositionTextureVertex.h"

namespace Ahwassa {
  class Window;
  class Texture;
  class Rendertarget;
  class VAO;
  class ShaderProgram;
  class UniformMat4;
  class Uniform;

  class PostProcessingEffect {
    public:
      PostProcessingEffect(std::string name, Ahwassa::Window* w, const glm::ivec2& resolution);

      std::shared_ptr<Ahwassa::Texture> getResult();
      void drawResult();

    protected:
      virtual void start();
      void end();

      glm::ivec2 getResolution() const;
      Ahwassa::Window* getWindow();
      std::vector<Ahwassa::Uniform*> getUniforms();


      bool  enabled();
      void  setEnabled(bool);
    private:
      std::unique_ptr<Ahwassa::VBO<Ahwassa::PositionTextureVertex>> _vbo       ;
      std::unique_ptr<Ahwassa::VAO>                                 _vao       ;
      std::shared_ptr<Ahwassa::Rendertarget>                        _result    ;
      std::shared_ptr<Ahwassa::ShaderProgram>                       _shader    ;
      std::unique_ptr<Ahwassa::UniformMat4>                         _projection;
      std::vector<Ahwassa::PositionTextureVertex>                   _vertices  ;

      std::string                                                   _name;
      glm::ivec2                                                    _resolution;
      Ahwassa::Window*                                              _window;
      bool                                                          _enabled = true;
  };
}