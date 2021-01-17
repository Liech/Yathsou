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
#include "YolonaOss/Renderer/TextRenderer.h"

#include "SupComModel.h"
#include "YolonaOss/OpenGL/SupComVertex.h"
#include "HaasScriptingLib/ScriptEngine.h"
#include "YolonaOss/Drawables/Widgets/Button.h"
#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp"
#include <IyathuumCoreLib/lib/glm/gtx/quaternion.hpp>
#include <IyathuumCoreLib/lib/glm/gtx/euler_angles.hpp>
#include <fstream>

namespace Fatboy{
  AnimationDebugger::AnimationDebugger() {
    _animName = "walk01";
    _unitName = "URL0106";
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

    //std::string folder = "E:\\scmunpacked\\units\\" + _unitName;
    std::string folder = "C:\\Users\\Niki\\Desktop\\units\\" + _unitName;
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


    {
      std::ofstream stream;
      stream.open("Anim.json");
      nlohmann::json j = _modl->_animations[_animName]->toJson();
      stream << j.dump(4);
      stream.close();
    }
    {
      std::ofstream stream;
      stream.open("Modl.json");
      nlohmann::json j = _modl->_model->toJson();
      stream << j.dump(4);
      stream.close();
    }
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
    renderStuff2();
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
  
  glm::mat4 QuatToMat(glm::quat q)
  {
    //https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
    glm::mat4 result = glm::mat4(1.0f);
    double sqw = q.w*q.w;
    double sqx = q.x*q.x;
    double sqy = q.y*q.y;
    double sqz = q.z*q.z;

    // invs (inverse square length) is only required if quaternion is not already normalised
    double invs = 1 / (sqx + sqy + sqz + sqw);
    result[0][0] = ( sqx - sqy - sqz + sqw)*invs ; // since sqw + sqx + sqy + sqz =1/invs*invs
    result[1][1] = (-sqx + sqy - sqz + sqw)*invs ;
    result[2][2] = (-sqx - sqy + sqz + sqw)*invs ;
    
    double tmp1 = q.x*q.y;
    double tmp2 = q.z*q.w;
    result[1][0] = 2.0 * (tmp1 + tmp2)*invs ;
    result[0][1] = 2.0 * (tmp1 - tmp2)*invs ;
    
    tmp1 = q.x*q.z;
    tmp2 = q.y*q.w;
    result[2][0] = 2.0 * (tmp1 - tmp2)*invs ;
    result[0][2] = 2.0 * (tmp1 + tmp2)*invs ;
    tmp1 = q.y*q.z;
    tmp2 = q.x*q.w;
    result[2][1] = 2.0 * (tmp1 + tmp2)*invs ;
    result[1][2] = 2.0 * (tmp1 - tmp2)*invs ; 


    return result;
  }

  std::string vec2str(glm::vec3 v)
  {
    return std::to_string(v[0]) + "/" + std::to_string(v[1]) + "/" + std::to_string(v[2]);
  }

  float animtime = 0;

  void AnimationDebugger::renderStuff2()
  {
    animtime += 0.001f;
    animtime = std::fmod(animtime, _modl->_animations[_animName]->duration);
    int frame = (animtime / _modl->_animations[_animName]->duration) * (_modl->_animations[_animName]->animation.size() - 1) + 1;

    SCA::frame anim = _modl->_animations[_animName]->animation[frame];

    std::vector<glm::mat4> animationMatrices;
    animationMatrices.resize(32);
    for (int i = 0; i < 32; i++)
      animationMatrices[i] = glm::mat4(1.0);
    std::vector<glm::mat4> animationMatrices2;
    animationMatrices2.resize(32);
    for (int i = 0; i < 32; i++)
      animationMatrices2[i] = glm::mat4(1.0);

    YolonaOss::BoxRenderer::start();
    for(int i = 1;i < anim.bones.size();i++)
    {
      int imin = i - 1;
      auto pos = anim.bones[i].position;
      animationMatrices [imin] = glm::translate(animationMatrices [imin], pos);
      animationMatrices2[imin] = glm::translate(glm::mat4(1.0), pos);
      int parentIndex = _modl->_animations[_animName]->boneLinks[i - 1];
      if (parentIndex != -1)
      {
        animationMatrices [imin] = animationMatrices [parentIndex] * animationMatrices [imin];
        animationMatrices2[imin] = animationMatrices2[parentIndex] * animationMatrices2[imin];
      }

      glm::vec3 absPos = animationMatrices[imin] * glm::vec4(0, 0, 0, 1);
      YolonaOss::BoxRenderer::drawDot(absPos, glm::vec3(1, 1, 1), glm::vec4(1, 0, 0, 1));
      //YolonaOss::BoxRenderer::draw   (animationMatrices[imin]*rot,glm::vec4(0, 1, 0, 1));

      if (parentIndex != -1)
      {
        glm::vec3 parPos = animationMatrices[parentIndex] * glm::vec4(0, 0, 0, 1);
        YolonaOss::BoxRenderer::drawLine(parPos, absPos, 0.5f, glm::vec4(0, 1, 0, 1));
      }
    }

    //YolonaOss::BoxRenderer::drawDot(glm::vec3(animtime,0,0), glm::vec3(1, 1, 1), glm::vec4(1, 0, 0, 1));
    YolonaOss::BoxRenderer::end();

    YolonaOss::TextRenderer::start();

    //for (int i = 0; i < anim.bones.size(); i++)
    //{
    //  auto pos = anim.bones[i].position;
    //  YolonaOss::TextRenderer::drawText(std::to_string(i), _spec->getCam()->worldToViewCoordTransform(pos), 0.3f, glm::vec4(0, 0, 0, 1));

    //}

    std::string text = std::to_string(frame);
    glm::vec2 textPos = glm::vec2(_spec->width - YolonaOss::TextRenderer::getTextSize(text, 1)[0], 0);
    YolonaOss::TextRenderer::drawText(text, textPos, 1, glm::vec4(0, 0, 0, 1));
    YolonaOss::TextRenderer::end();

    auto r = QuatToMat(anim.bones[2].rotation);
    auto r2 = r;
    animationMatrices2[2] = animationMatrices2[2] * r;
    r = QuatToMat(anim.bones[3].rotation);
    animationMatrices2[3] = animationMatrices2[3] * r;
    r = QuatToMat(anim.bones[4].rotation);
    animationMatrices2[4] = animationMatrices2[4] * r;

    auto parentMatrix = _modl->_model->bones[1].relativeInverseMatrix;
    r = QuatToMat(anim.bones[5].rotation);
    auto t = glm::translate(glm::mat4(1.0), anim.bones[5].position);
    auto t2 = glm::translate(glm::mat4(1.0), anim.bones[1].position);
    auto t3 = glm::translate(glm::mat4(1.0), anim.bones[0].position);
    auto t4 = glm::translate(glm::mat4(1.0), anim.bones[0].position);
    animationMatrices2[5] = t2* r2* t* r;

    //for (int i = 1; i < anim.bones.size(); i++)
    //  animationMatrices2[i - 1] = animationMatrices2[i - 1] * _modl->_model->bones[i-1].relativeInverseMatrix;

    animationMatrices2[0] = animationMatrices2[0] * _modl->_model->bones[0].relativeInverseMatrix;
    animationMatrices2[1] = animationMatrices2[1] * _modl->_model->bones[1].relativeInverseMatrix;
    animationMatrices2[2] = animationMatrices2[2] * _modl->_model->bones[2].relativeInverseMatrix;
    animationMatrices2[3] = animationMatrices2[3] * _modl->_model->bones[3].relativeInverseMatrix;
    animationMatrices2[4] = animationMatrices2[4] * _modl->_model->bones[4].relativeInverseMatrix;
    animationMatrices2[5] = animationMatrices2[5] * _modl->_model->bones[5].relativeInverseMatrix;

    for (int i = 6; i < anim.bones.size(); i++)
      animationMatrices2[i] = glm::mat4(0.0f);

    YolonaOss::SupComModelRenderer::start();
    YolonaOss::SupComModelRenderer::draw(*_scMesh, glm::mat4(1.0), animationMatrices2);
    YolonaOss::SupComModelRenderer::end();
  }

  void AnimationDebugger::renderStuff()
  {
    animtime += 0.001f;
    animtime = std::fmod(animtime, _modl->_animations[_animName]->duration);
    int frame = (animtime / _modl->_animations[_animName]->duration) * (_modl->_animations[_animName]->animation.size()-1)+1;
    
    std::vector<glm::mat4> animationMatrices;
    animationMatrices.resize(64);
    for (int i = 0; i < 64; i++)
      animationMatrices[i] = glm::mat4(1.0);

    auto anim = _modl->_animations[_animName]->animation[frame];

    auto bones = _modl->_model->bones;
    for (int number = 0;number < bones.size();number++)
    {
      std::string msg = "";
      auto bone = bones[number];

      YolonaOss::BoxRenderer::start();
      if (frame % 2 == 0)
      {  // Animation
        glm::vec3 trans = anim.bones[number].position;
        msg += vec2str(trans);
        animationMatrices[number] = glm::translate(glm::mat4(1.0f), trans);
      }
      else
      {  // Model
        glm::vec3 trans = _modl->_model->bones[number].position;
        animationMatrices[number] = glm::translate(glm::mat4(1.0f), trans);
        msg += vec2str(trans);
      }
      
      glm::mat4 rot = QuatToMat(anim.bones[number].rotation);
      //YolonaOss::BoxRenderer::drawDot(anim.bones[number].position,glm::vec3(0.1f,0.1f,0.1f), glm::vec4(0, 1, 0, 1));
      if (bone.parentIndex != -1)
      {
        //auto q = _modl->_animations[_animName]->animation[frame].bones[number].rotation;
        //std::cout << q[0] << " " << q[1] << " " << q[2] << "- " << q[3] << std::endl;;
        animationMatrices[number] = animationMatrices[number]*animationMatrices[bone.parentIndex];
      }
      else
      {
        if (frame % 2 == 0) //Animation
          animationMatrices[number] = animationMatrices[number] * glm::translate(glm::mat4(1.0f),-_modl->_animations[_animName]->position);
        
      }
      glm::vec3 pos = animationMatrices[number] * glm::vec4(0, 0, 0, 1);
      
      YolonaOss::BoxRenderer::drawDot(pos,glm::vec3(1,1,1), glm::vec4(1, 0, 0, 1));
      //YolonaOss::BoxRenderer::draw(glm::translate(rot, pos), glm::vec4(0, 1, 0, 1));
      YolonaOss::BoxRenderer::draw(glm::translate(glm::mat4(1.0), pos)*rot, glm::vec4(0, 1, 0, 1));
      if (bone.parentIndex != -1)
      {
        glm::vec3 parentPos = animationMatrices[bone.parentIndex] * glm::vec4(0, 0, 0, 1);
        auto parent = bones[bone.parentIndex];
        YolonaOss::BoxRenderer::drawLine(pos,parentPos, 0.5f, glm::vec4(0, 1, 0, 1));
      }
      YolonaOss::BoxRenderer::end();

      YolonaOss::TextRenderer::start();
      YolonaOss::TextRenderer::drawText(std::to_string(number) + " " + msg, _spec->getCam()->worldToViewCoordTransform(pos), 0.3f, glm::vec4(0, 0, 0, 1));
      YolonaOss::TextRenderer::end();
    }




    YolonaOss::TextRenderer::start();
    std::string text = std::to_string(frame);
    glm::vec2 textPos = glm::vec2(_spec->width - YolonaOss::TextRenderer::getTextSize(text, 1)[0], 0);
    YolonaOss::TextRenderer::drawText(text, textPos, 1, glm::vec4(0, 0, 0, 1));
    YolonaOss::TextRenderer::end();
    YolonaOss::SupComModelRenderer::debugRender = true;
    animationMatrices.resize(32);
    YolonaOss::SupComModelRenderer::start();
    //YolonaOss::SupComModelRenderer::draw(*_scMesh, glm::mat4(1.0), animationMatrices);
    YolonaOss::SupComModelRenderer::end();
  }
}