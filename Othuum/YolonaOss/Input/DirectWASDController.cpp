#include "DirectWASDController.h"

#include "IyathuumCoreLib/BaseTypes/Keys.h"
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
    auto isDown = [this](Iyathuum::Key key) {
      return _spec->getWindow()->getKeyStatus(key) == Iyathuum::KeyStatus::PRESS;
    };
    auto isStart = [this](Iyathuum::Key key, bool old) {
      bool pressed = (_spec->getWindow()->getKeyStatus(key) == Iyathuum::KeyStatus::PRESS);
      return pressed != old && pressed;
    };
    auto isEnd = [this](Iyathuum::Key key, bool old) {
      bool pressed = (_spec->getWindow()->getKeyStatus(key) == Iyathuum::KeyStatus::PRESS);
      return pressed != old && !pressed;
    };
    
    if (isDown (Iyathuum::Key::KEY_W)                    ) _target.inputUp       ();
    if (isDown (Iyathuum::Key::KEY_A)                    ) _target.inputLeft     ();
    if (isDown (Iyathuum::Key::KEY_S)                    ) _target.inputDown     ();
    if (isDown (Iyathuum::Key::KEY_D)                    ) _target.inputRight    ();
    if (isDown (Iyathuum::Key::KEY_Q)                    ) _target.inputSpecial  ();
    if (isDown (Iyathuum::Key::KEY_E)                    ) _target.inputInteract ();
    if (isDown (Iyathuum::Key::KEY_F)                    ) _target.inputInventory();

    if (isEnd  (Iyathuum::Key::KEY_W,_oldStatusUp       )) _target.startUp       ();
    if (isEnd  (Iyathuum::Key::KEY_A,_oldStatusDown     )) _target.startLeft     ();
    if (isEnd  (Iyathuum::Key::KEY_S,_oldStatusLeft     )) _target.startDown     ();
    if (isEnd  (Iyathuum::Key::KEY_D,_oldStatusRight    )) _target.startRight    ();
    if (isEnd  (Iyathuum::Key::KEY_Q,_oldStatusSpecial  )) _target.startSpecial  ();
    if (isEnd  (Iyathuum::Key::KEY_E,_oldStatusInteract )) _target.startInteract ();
    if (isEnd  (Iyathuum::Key::KEY_F,_oldStatusInventory)) _target.startInventory();

    if (isStart(Iyathuum::Key::KEY_W,_oldStatusUp       )) _target.endUp         ();
    if (isStart(Iyathuum::Key::KEY_A,_oldStatusDown     )) _target.endLeft       ();
    if (isStart(Iyathuum::Key::KEY_S,_oldStatusLeft     )) _target.endDown       ();
    if (isStart(Iyathuum::Key::KEY_D,_oldStatusRight    )) _target.endRight      ();
    if (isStart(Iyathuum::Key::KEY_Q,_oldStatusSpecial  )) _target.endSpecial    ();
    if (isStart(Iyathuum::Key::KEY_E,_oldStatusInteract )) _target.endInteract   ();
    if (isStart(Iyathuum::Key::KEY_F,_oldStatusInventory)) _target.endInventory  ();


    _oldStatusUp        = _spec->getWindow()->getKeyStatus(Iyathuum::Key::KEY_W) == Iyathuum::KeyStatus::PRESS;
    _oldStatusDown      = _spec->getWindow()->getKeyStatus(Iyathuum::Key::KEY_A) == Iyathuum::KeyStatus::PRESS;
    _oldStatusLeft      = _spec->getWindow()->getKeyStatus(Iyathuum::Key::KEY_S) == Iyathuum::KeyStatus::PRESS;
    _oldStatusRight     = _spec->getWindow()->getKeyStatus(Iyathuum::Key::KEY_D) == Iyathuum::KeyStatus::PRESS;
    _oldStatusSpecial   = _spec->getWindow()->getKeyStatus(Iyathuum::Key::KEY_Q) == Iyathuum::KeyStatus::PRESS;
    _oldStatusInteract  = _spec->getWindow()->getKeyStatus(Iyathuum::Key::KEY_E) == Iyathuum::KeyStatus::PRESS;
    _oldStatusInventory = _spec->getWindow()->getKeyStatus(Iyathuum::Key::KEY_F) == Iyathuum::KeyStatus::PRESS;


  }
}