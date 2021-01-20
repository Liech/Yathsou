#include "DirectWASDController.h"

#include "YolonaOss/OpenGL/Keys.h"
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include "YolonaOss/OpenGL/Window.h"

namespace YolonaOss
{
  DirectWASDController::DirectWASDController(WASDInputable& target) :
    _target(target)
  {

  }

  void YolonaOss::DirectWASDController::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
  }

  void YolonaOss::DirectWASDController::update()
  {
    auto isDown = [this](YolonaOss::GL::Key key) {
      return _spec->getWindow()->getKeyStatus(key) == YolonaOss::GL::KeyStatus::PRESS;
    };
    auto isStart = [this](YolonaOss::GL::Key key, bool old) {
      bool pressed = (_spec->getWindow()->getKeyStatus(key) == YolonaOss::GL::KeyStatus::PRESS);
      return pressed != old && pressed;
    };
    auto isEnd = [this](YolonaOss::GL::Key key, bool old) {
      bool pressed = (_spec->getWindow()->getKeyStatus(key) == YolonaOss::GL::KeyStatus::PRESS);
      return pressed != old && !pressed;
    };
    
    if (isDown (YolonaOss::GL::Key::KEY_W)                    ) _target.inputUp       ();
    if (isDown (YolonaOss::GL::Key::KEY_A)                    ) _target.inputLeft     ();
    if (isDown (YolonaOss::GL::Key::KEY_S)                    ) _target.inputDown     ();
    if (isDown (YolonaOss::GL::Key::KEY_D)                    ) _target.inputRight    ();
    if (isDown (YolonaOss::GL::Key::KEY_Q)                    ) _target.inputSpecial  ();
    if (isDown (YolonaOss::GL::Key::KEY_E)                    ) _target.inputInteract ();
    if (isDown (YolonaOss::GL::Key::KEY_F)                    ) _target.inputInventory();

    if (isEnd  (YolonaOss::GL::Key::KEY_W,_oldStatusUp       )) _target.startUp       ();
    if (isEnd  (YolonaOss::GL::Key::KEY_A,_oldStatusDown     )) _target.startLeft     ();
    if (isEnd  (YolonaOss::GL::Key::KEY_S,_oldStatusLeft     )) _target.startDown     ();
    if (isEnd  (YolonaOss::GL::Key::KEY_D,_oldStatusRight    )) _target.startRight    ();
    if (isEnd  (YolonaOss::GL::Key::KEY_Q,_oldStatusSpecial  )) _target.startSpecial  ();
    if (isEnd  (YolonaOss::GL::Key::KEY_E,_oldStatusInteract )) _target.startInteract ();
    if (isEnd  (YolonaOss::GL::Key::KEY_F,_oldStatusInventory)) _target.startInventory();

    if (isStart(YolonaOss::GL::Key::KEY_W,_oldStatusUp       )) _target.endUp         ();
    if (isStart(YolonaOss::GL::Key::KEY_A,_oldStatusDown     )) _target.endLeft       ();
    if (isStart(YolonaOss::GL::Key::KEY_S,_oldStatusLeft     )) _target.endDown       ();
    if (isStart(YolonaOss::GL::Key::KEY_D,_oldStatusRight    )) _target.endRight      ();
    if (isStart(YolonaOss::GL::Key::KEY_Q,_oldStatusSpecial  )) _target.endSpecial    ();
    if (isStart(YolonaOss::GL::Key::KEY_E,_oldStatusInteract )) _target.endInteract   ();
    if (isStart(YolonaOss::GL::Key::KEY_F,_oldStatusInventory)) _target.endInventory  ();


    _oldStatusUp        = _spec->getWindow()->getKeyStatus(YolonaOss::GL::Key::KEY_W) == YolonaOss::GL::KeyStatus::PRESS;
    _oldStatusDown      = _spec->getWindow()->getKeyStatus(YolonaOss::GL::Key::KEY_A) == YolonaOss::GL::KeyStatus::PRESS;
    _oldStatusLeft      = _spec->getWindow()->getKeyStatus(YolonaOss::GL::Key::KEY_S) == YolonaOss::GL::KeyStatus::PRESS;
    _oldStatusRight     = _spec->getWindow()->getKeyStatus(YolonaOss::GL::Key::KEY_D) == YolonaOss::GL::KeyStatus::PRESS;
    _oldStatusSpecial   = _spec->getWindow()->getKeyStatus(YolonaOss::GL::Key::KEY_Q) == YolonaOss::GL::KeyStatus::PRESS;
    _oldStatusInteract  = _spec->getWindow()->getKeyStatus(YolonaOss::GL::Key::KEY_E) == YolonaOss::GL::KeyStatus::PRESS;
    _oldStatusInventory = _spec->getWindow()->getKeyStatus(YolonaOss::GL::Key::KEY_F) == YolonaOss::GL::KeyStatus::PRESS;


  }
}