#pragma once

//#include "structs/Factory.h"
#include "../OpenGL/Loadable.h"
#include <iostream>
#include "../structs/Factory.h"
#include "glm/glm.hpp"
#include "../structs/BoundingBox.h"
#include <memory>

#include <map>
#include "../OpenGL/VAO.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/ShaderProgram.h"
#include "../OpenGL/PositionVertex.h"
class ShaderProgram;
class UniformMat4;
class UniformVec3;

class RectangleRenderer : public Loadable {
REGISTER(Loadable, RectangleRenderer, "RectangleRenderer", { "PreDrawCall" })
public:
  RectangleRenderer() {}
  virtual ~RectangleRenderer() {}
  static void startTextRender();
  static void endTextRender();
  static void drawRectangle(glm::vec2 pos, glm::vec2 size, glm::vec3 color);
  static void drawRectangle(BoundingBox2 box, glm::vec3 color);

  virtual void load(DrawSpecification*) override;
  
private:
  struct RenderVars {
    std::unique_ptr<VBO<PositionVertex>>   vbo        ;
    std::unique_ptr<VAO<PositionVertex>>   vao        ;
    std::unique_ptr<ShaderProgram>              shader     ;
    DrawSpecification*                          spec       ;
    std::unique_ptr<UniformMat4>                projection ;
    std::unique_ptr<UniformVec3>                color  ;
  };

  void makeShader();

  static inline bool       _alreadyLoaded = false;
  static inline bool       _inRenderProcess = false;
  static RenderVars _vars;

};