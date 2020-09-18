#pragma once
//
//#include "YolonaOss/OpenGL/Drawable.h"
//#include <memory>
//
//#include "YolonaOss/OpenGL/VBO.h"
//#include "YolonaOss/OpenGL/VAO.h"
//#include "YolonaOss/OpenGL/IBO.h"
//#include "YolonaOss/OpenGL/ShaderProgram.h"
//#include "YolonaOss/OpenGL/PositionColorNormalVertex.h"
//#include <time.h>
//#include "YolonaOss/OpenGL/Camera.h"
//#include "YolonaOss/OpenGL/Uniform.h"
//using namespace YolonaOss;
////5 camera
//
//class DrawCubes : public GL::Drawable
//{
//public:
//
//  // Inherited via Drawable
//  virtual void load(GL::DrawSpecification *) override;
//  virtual void draw() override;
//
//private:
//  GL::DrawSpecification* _spec;
//  GLuint program;
//
//  std::unique_ptr<GL::UniformVec3>              _light;
//  std::unique_ptr<GL::UniformMat4>              _model;
//  std::shared_ptr<GL::Camera>                   _camera;
//  std::unique_ptr<GL::IBO>                      _ibo;
//  std::unique_ptr<GL::VBO<GL::PositionColorNormalVertex>> _vbo;
//  std::unique_ptr<GL::VAO<GL::PositionColorNormalVertex>> _vao;
//  std::unique_ptr<GL::ShaderProgram>            _shader;
//  std::vector<glm::vec3>                    _positions;
//  int drawCall = 0;
//
//  std::string vertex_shader_source;
//  std::string fragment_shader_source;
//};
//
