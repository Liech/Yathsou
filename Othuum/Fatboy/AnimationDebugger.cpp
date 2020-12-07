#include "AnimationDebugger.h"

#include <iostream>

#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Background.h"
#include "YolonaOss/Drawables/Ground.h"

#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/Camera/CameraSystem.h"
#include "YolonaOss/Camera/FreeCamera.h"
#include "YolonaOss/OpenGL/Camera.h"

#include "YolonaOss/OpenGL/Keys.h"
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include "YolonaOss/OpenGL/Window.h"

#include "YolonaOss/Renderer/SupComModelRenderer.h"
#include "YolonaOss/Renderer/BoxRenderer.h"

#include "SupComModel.h"
#include "YolonaOss/OpenGL/SupComVertex.h"
#include "HaasScriptingLib/ScriptEngine.h"
#include "YolonaOss/Drawables/Widgets/Button.h"
#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp"
#include <IyathuumCoreLib/lib/glm/gtx/quaternion.hpp>
#include <IyathuumCoreLib/lib/glm/gtx/euler_angles.hpp>

namespace Fatboy{
  AnimationDebugger::AnimationDebugger() {
    _animName = "walk";
    _unitName = "UAL0401";
    _preDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _postDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _preDrawables->addDrawable(std::make_shared<YolonaOss::Background>());
    _postDrawables->addDrawable(std::make_shared<YolonaOss::FPS>());
    //_preDrawables->addDrawable(std::make_shared<YolonaOss::Ground>());
    _cam = std::make_shared<YolonaOss::Camera::CameraSystem>();
  }

  void AnimationDebugger::load(YolonaOss::GL::DrawSpecification* spec){
    _spec = spec;
    _preDrawables->load(spec);
    _postDrawables->load(spec);
    _cam->load(spec);
    _cam->setCurrentCam("None");

    loadMenu();
    loadModel();
    loadScript();

  }

  void AnimationDebugger::draw() {
    _layout->adjustSize();
    _preDrawables->draw();
    _postDrawables->draw();
    drawModel();
  }

  void AnimationDebugger::loadScript()  {
    //_script = std::make_shared<Haas::ScriptEngine>();
    //try
    //{
    //  _script->executeFile("AnimationTest.lua");
    //
    //  _script->setVar("SCAAnimation", _modl->_animations[_animName]->toJson());
    //  _script->setVar("Model", _modl->_model->toJson());
    //}
    //catch (...)
    //{
    //  std::cout << "ERROR WHILE FILE EXEC" << std::endl;
    //}
  }

  void AnimationDebugger::loadModel() {

    std::string folder = "E:\\scmunpacked\\units\\" + _unitName;
    std::string a1 = _unitName + "_lod0.scm";
    std::string texture = _unitName + "_Albedo.dds";
    std::string mapdds = "C:\\Users\\Niki\\Documents\\My Games\\Gas Powered Games\\Supreme Commander Forged Alliance\\Maps\\Setons 10x10\\setons 10x10.dds";
    SCM imp;
    _modl = std::make_shared<SupComModel>(folder);

    std::vector<YolonaOss::GL::SupComVertex> verticesT;
    std::vector<int>                                 indices;
    for (int i = 0; i < _modl->_model->vertecies.size(); i++) {
      YolonaOss::GL::SupComVertex v;
      auto vPre = _modl->_model->vertecies[i];
      v.position = vPre.position;
      v.tangent = vPre.tangent;
      v.normal = vPre.normal;
      v.binormal = vPre.binormal;
      v.uv1 = vPre.uv1;
      v.uv2 = vPre.uv2;
      v.bones[0] = vPre.boneIndex[0];
      v.bones[1] = vPre.boneIndex[1];
      v.bones[2] = vPre.boneIndex[2];
      v.bones[3] = vPre.boneIndex[3];
      verticesT.push_back(v);
    }
    for (int i = 0; i < _modl->_model->indices.size(); i++)
    {
      indices.push_back(_modl->_model->indices[i].a);
      indices.push_back(_modl->_model->indices[i].b);
      indices.push_back(_modl->_model->indices[i].c);
    }
    _scMesh = new YolonaOss::SupComGLMesh(verticesT, indices);
    _scMesh->setAlbedo(_modl->_albedo);
    _scMesh->setInfo(_modl->_info);
    _scMesh->setNormal(_modl->_normal);
  }

  void AnimationDebugger::loadMenu(){
    std::shared_ptr<YolonaOss::Widgets::Button> scout = std::make_shared<YolonaOss::Widgets::Button>("Scout", Iyathuum::AABB<2>({ 0, 0 }, { 300, 50 }), [this]() {
      _animName = "walk01";
      _unitName = "URL0106";
      loadModel();
      });
    std::shared_ptr<YolonaOss::Widgets::Button> gc = std::make_shared<YolonaOss::Widgets::Button>("GC", Iyathuum::AABB<2>({ 0, 0 }, { 300, 50 }), [this]() {
      _animName = "walk";
      _unitName = "UAL0401";
      loadModel();
      });
    std::shared_ptr<YolonaOss::Widgets::Button> spiderlord = std::make_shared<YolonaOss::Widgets::Button>("Monkeylord", Iyathuum::AABB<2>({ 0, 0 }, { 300, 50 }), [this]() {
      _animName = "001";
      _unitName = "URL0402";
      loadModel();
      });
    std::shared_ptr<YolonaOss::Widgets::Button> brick = std::make_shared<YolonaOss::Widgets::Button>("Brick", Iyathuum::AABB<2>({ 0, 0 }, { 300, 50 }), [this]() {
      _animName = "walk";
      _unitName = "XRL0305";
      loadModel();
      });
    std::shared_ptr<YolonaOss::Widgets::Button> mole = std::make_shared<YolonaOss::Widgets::Button>("Mole", Iyathuum::AABB<2>({ 0, 0 }, { 300, 50 }), [this]() {
      _animName = "walk";
      _unitName = "URL0101";
      loadModel();
      });

    
    std::shared_ptr<YolonaOss::Widgets::Button> reload = std::make_shared<YolonaOss::Widgets::Button>("Reload", Iyathuum::AABB<2>({ 0, 0 }, { 300, 50 }), [this]() {
      loadScript();
      });
    _layout = std::make_shared<YolonaOss::Widgets::ListLayout>(Iyathuum::AABB<2>({ 0, 0 }, { 700, 900 }));
    _layout->addWidget(scout);
    _layout->addWidget(gc);
    _layout->addWidget(spiderlord);
    _layout->addWidget(brick);
    _layout->addWidget(mole);
    _layout->addWidget(reload);
    _postDrawables->addDrawable(_layout);
  }

  void AnimationDebugger::drawModel()  {

    //float scale = 1;
    //
    //std::vector<glm::mat4> animation;
    //animation.resize(32);
    //for (int i = 0; i < 32; i++)
    //  animation[i] = glm::mat4(1.0);
    //
    //nlohmann::json jAnim = nlohmann::json::array();
    //for (glm::mat4 g : animation) {
    //  nlohmann::json arr = nlohmann::json::array();
    //  for (int i = 0; i < 16; i++) {
    //    float ig = glm::value_ptr(g)[i];
    //    arr.push_back(ig);
    //  }
    //  jAnim.push_back(arr);
    //}
    ////std::cout << input.dump(4);
    //nlohmann::json input;
    //input["Mats"]      = jAnim;
    //input["Scale"]     = scale;
    //
    //struct local_dot {
    //  float     size ;
    //  glm::vec4 color;
    //  glm::vec3 pos  ;
    //};
    //struct local_line {
    //  float     size ;
    //  glm::vec4 color;
    //  glm::vec3 start;
    //  glm::vec3 end  ;
    //};
    //
    //std::vector<local_dot > dots;
    //std::vector<local_line> lines;
    //try {
    //  nlohmann::json out = _script->callScript("anim", input);
    //  //std::cout << out.dump(4);
    //  for (int i = 0; i < 32; i++) {
    //    for (int j = 0; j < 16; j++)
    //      glm::value_ptr(animation[i])[j] = out["anim"][i][j];
    //  }
    //  for (auto sub : out["Dots"]) {
    //    local_dot d;
    //    d.pos = glm::vec3(sub["Pos"][0], sub["Pos"][1], sub["Pos"][2]);
    //    d.color = glm::vec4(sub["Color"][0], sub["Color"][1], sub["Color"][2], sub["Color"][3]);
    //    d.size  = sub["Size"];
    //    dots.push_back(d);
    //  }
    //  for (auto sub : out["Lines"]) {
    //    local_line d;
    //    d.start = glm::vec3(sub["Start"][0], sub["Start"][1], sub["Start"][2]);
    //    d.end   = glm::vec3(sub["End"][0], sub["End"][1], sub["End"][2]);
    //    d.color = glm::vec4(sub["Color"][0], sub["Color"][1], sub["Color"][2], sub["Color"][3]);
    //    d.size  = sub["Size"];
    //    lines.push_back(d);
    //  }
    //}
    //catch (...)
    //{
    //  std::cout << "ERRROR ON PARSE OUTPUT" << std::endl;
    //}
    //
    //
    //  
    //YolonaOss::SupComModelRenderer::start();
    ////_animationTime += 0.001f;
    //glm::vec3 renderCenter = glm::vec3(0, 0, 0) * scale;
    //YolonaOss::SupComModelRenderer::draw(*_scMesh, glm::scale(glm::translate(glm::mat4(1.0), renderCenter ), glm::vec3(scale, scale, scale)), animation);
    //YolonaOss::SupComModelRenderer::end();
    //YolonaOss::BoxRenderer::start();
    //YolonaOss::BoxRenderer::drawDot(renderCenter, glm::vec3(0.1f,0.1f,0.1f), glm::vec4(1, 1, 1, 1));
    //for (auto d : dots)
    //  YolonaOss::BoxRenderer::drawDot(d.pos, glm::vec3(d.size, d.size, d.size), d.color);
    //for (auto d : lines)
    //  YolonaOss::BoxRenderer::drawLine(d.start,d.end, d.size, d.color);
    //YolonaOss::BoxRenderer::end();
    renderStuff();
  }


  void AnimationDebugger::update(){
    _cam->update();

    auto isPressed = [this](YolonaOss::GL::Key key) {
      return _spec->getWindow()->getKeyStatus(key) == YolonaOss::GL::KeyStatus::PRESS;
    };
    if (isPressed(YolonaOss::GL::Key::KEY_F2) && !_keyPressed)
    {
      if (_cam->getCurrentCam() == "None")
        _cam->setCurrentCam("FreeCamera");
      else
        _cam->setCurrentCam("None");
      _keyPressed = true;
    }
    else if (!isPressed(YolonaOss::GL::Key::KEY_F2)) 
      _keyPressed = false;
  }
  
  glm::mat4 QuatToMat(glm::quat input)
  {
    glm::vec3 euler = glm::eulerAngles(input) * 3.14159f / 180.f;

    glm::mat4 transformX = glm::eulerAngleX(euler.x);
    glm::mat4 transformY = glm::eulerAngleY(euler.y);
    glm::mat4 transformZ = glm::eulerAngleZ(euler.z);

    return transformX * transformY * transformZ; // or some other order
  }

  float animtime = 0;
  void AnimationDebugger::renderStuff()
  {
    animtime += 0.01f;
    animtime = std::fmod(animtime, _modl->_animations[_animName]->duration);
    YolonaOss::BoxRenderer::start();
    std::vector<glm::mat4> cummulativePos;
    std::vector<glm::vec3> antiPos;
    
    int numberOfFrames = _modl->_animations[_animName]->animation.size()-1;
    int frameID = std::floor((animtime * numberOfFrames) / _modl->_animations[_animName]->duration)+1;
    auto frame = _modl->_animations[_animName]->animation[frameID];
    std::cout << frameID <<std::endl;
    int amountOfBones = frame.bones.size();
    cummulativePos.resize(_modl->_model->bones.size());
    antiPos.resize(amountOfBones);
    std::map<std::string, int> boneMap;
    for (int i = 0; i < _modl->_model->bones.size(); i++)
      boneMap[_modl->_model->bones[i].name] = i;
    for (int i = 0; i < cummulativePos.size(); i++)
      cummulativePos[i] = glm::mat4(1.0);
    for (int i = 0; i < amountOfBones; i++){
      int index = boneMap[frame.bones[i].name];
      SCM::bone b = _modl->_model->bones[index];
      //cummulativePos[i] = glm::translate(glm::mat4(1.0),b.position);
      glm::mat4 rot = QuatToMat(frame.bones[i].rotation);
      //if (b.parentIndex != 0)
        cummulativePos[index] = glm::translate(glm::mat4(1.0), frame.bones[i].position) * rot;
        antiPos[i] = glm::vec3(0, 0, 0);//-_modl->_model->bones[i].position;
      //else
      //  cummulativePos[i] = glm::mat4(1.0);
      if (b.parentIndex != -1) {
        cummulativePos[index] = cummulativePos[b.parentIndex]*cummulativePos[index];
        YolonaOss::BoxRenderer::drawLine(cummulativePos[index]*glm::vec4(0,0,0,1), cummulativePos[b.parentIndex] * glm::vec4(0, 0, 0, 1), 0.1f, glm::vec4(1, 0, 0, 1));
        //antiPos[i] += antiPos[b.parentIndex];
      }
      else
      {
        cummulativePos[index] = glm::translate(glm::mat4(1.0), b.position);
      }
      YolonaOss::BoxRenderer::draw(glm::mat4(0.2f)* cummulativePos[index], glm::vec4(1, 0, 0, 1));
    }

    YolonaOss::BoxRenderer::drawDot(glm::vec3(0, 0, 0), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec4(1, 1, 1, 1));
    YolonaOss::BoxRenderer::end();

    for (int i = 0; i < amountOfBones; i++){
      //cummulativePos[i] = cummulativePos[i]*_modl->_model->bones[i].relativeInverseMatrix;
      if (i == 9) continue;
      cummulativePos[i] = glm::mat4(0.0);
    }

    int b = 9;
    std::cout << "START" << std::endl;    
    while (b != -1)
    {
      std::cout <<b<<": " << _modl->_model->bones[b].position[0] << "/" << _modl->_model->bones[b].position[1] << "/" << _modl->_model->bones[b].position[2] << std::endl;
      b = _modl->_model->bones[b].parentIndex;
    }

    glm::vec3 pos0 = glm::vec3(5.2f,-2.0f,-4.0f);
    glm::vec3 pos1 = glm::vec3(5.2f,-2.0f,-4.0f);
    glm::vec3 pos2 = glm::vec3(5.2f,-2.0f,-4.0f);
    glm::vec3 pos3 = glm::vec3(5.2f,-2.0f,-4.0f);
    
    static int x = 0;
    x = (x + 1) % 4;
    
    if (x==0) 
      cummulativePos[9] = glm::translate(glm::mat4(1.0), pos0);
    else if (x == 1)
      cummulativePos[9] = glm::translate(glm::mat4(1.0), pos1);
    else if (x == 2)
      cummulativePos[9] = glm::translate(glm::mat4(1.0), pos2);
    else if (x == 3)
      cummulativePos[9] = glm::translate(glm::mat4(1.0), pos3);

    YolonaOss::SupComModelRenderer::debugRender = true;
    cummulativePos.resize(32);
    YolonaOss::SupComModelRenderer::start();
    YolonaOss::SupComModelRenderer::draw(*_scMesh, glm::mat4(1.0), cummulativePos);
    YolonaOss::SupComModelRenderer::end();

    std::vector<glm::mat4> cp(cummulativePos.begin(),cummulativePos.end());
    
    //cp[9] = glm::inverse(_modl->_model->bones[9].relativeInverseMatrix);
    //
    //YolonaOss::SupComModelRenderer::debugRender = false;
    //YolonaOss::SupComModelRenderer::start();
    //YolonaOss::SupComModelRenderer::draw(*_scMesh, glm::mat4(1.0), cp);
    //YolonaOss::SupComModelRenderer::end();
  }
}