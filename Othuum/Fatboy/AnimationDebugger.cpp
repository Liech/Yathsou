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
#include "SupComModel.h"
#include "YolonaOss/OpenGL/SupComVertex.h"
#include "HaasScriptingLib/ScriptEngine.h"
#include "YolonaOss/Drawables/Widgets/Button.h"
#include "YolonaOss/Drawables/Widgets/ListLayout.h"

namespace Fatboy{
  AnimationDebugger::AnimationDebugger() {
    _preDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _postDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _preDrawables->addDrawable(std::make_shared<YolonaOss::Background>());
    _postDrawables->addDrawable(std::make_shared<YolonaOss::FPS>());
    _preDrawables->addDrawable(std::make_shared<YolonaOss::Ground>());
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
    _script = std::make_shared<Haas::ScriptEngine>();
    _script->executeFile("AnimationTest.lua");

    _script->setVar("Animation", _modl->_animations[_animName]->toJson());
    _script->setVar("Model", _modl->_model->toJson());
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
      _animName = "walk";
      _unitName = "URL0402";
      loadModel();
      });
    std::shared_ptr<YolonaOss::Widgets::Button> brick = std::make_shared<YolonaOss::Widgets::Button>("Brick", Iyathuum::AABB<2>({ 0, 0 }, { 300, 50 }), [this]() {
      _animName = "walk";
      _unitName = "XRL0305";
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
    _layout->addWidget(reload);
    _postDrawables->addDrawable(_layout);
  }

  void AnimationDebugger::drawModel()  {

    float scale = 0.1f;

    std::vector<glm::mat4> animation;
    animation.resize(32);
    for (int i = 0; i < 32; i++)
      animation[i] = glm::mat4(1.0);

    nlohmann::json jAnim = nlohmann::json::array();
    for (glm::mat4 g : animation) {
      nlohmann::json arr = nlohmann::json::array();
      for (int i = 0; i < 16; i++) {
        float ig = glm::value_ptr(g)[i];
        arr.push_back(ig);
      }
      jAnim.push_back(arr);
    }
    //std::cout << input.dump(4);
    nlohmann::json input;
    input["Mats"] = jAnim;
    input["Scale"] = scale;

    nlohmann::json out = _script->callScript("anim", input);
    //std::cout << out.dump(4);
    for (int i = 0; i < 32; i++) {
      for (int j = 0; j < 16;j++)
        glm::value_ptr(animation[i])[j] = out[i][j];
    }

    
      
    YolonaOss::SupComModelRenderer::start();
    //_animationTime += 0.001f;
    YolonaOss::SupComModelRenderer::draw(*_scMesh, glm::scale(glm::translate(glm::mat4(1.0), glm::vec3(0, 10, 0) * scale), glm::vec3(scale, scale, scale)), animation);
    YolonaOss::SupComModelRenderer::end();
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
}