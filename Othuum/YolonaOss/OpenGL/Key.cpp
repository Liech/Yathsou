#include "Keys.h"

#include <set>

namespace YolonaOss {
  namespace GL {
    std::set<Key> CharacterSets::InputExtraSymbols{
      Key::KEY_PERIOD,
      Key::KEY_SPACE
    };

    std::set<Key> CharacterSets::AlphanumericKeys{
      Key::KEY_A,
      Key::KEY_B,
      Key::KEY_C,
      Key::KEY_D,
      Key::KEY_E,
      Key::KEY_F,
      Key::KEY_G,
      Key::KEY_H,
      Key::KEY_I,
      Key::KEY_J,
      Key::KEY_K,
      Key::KEY_L,
      Key::KEY_M,
      Key::KEY_N,
      Key::KEY_O,
      Key::KEY_P,
      Key::KEY_Q,
      Key::KEY_R,
      Key::KEY_S,
      Key::KEY_T,
      Key::KEY_U,
      Key::KEY_V,
      Key::KEY_W,
      Key::KEY_X,
      Key::KEY_Y,
      Key::KEY_Z,
      Key::KEY_0,
      Key::KEY_1,
      Key::KEY_2,
      Key::KEY_3,
      Key::KEY_4,
      Key::KEY_5,
      Key::KEY_6,
      Key::KEY_7,
      Key::KEY_8,
      Key::KEY_9,
    };

    std::set<Key> CharacterSets::Numeric{
      Key::KEY_0,
      Key::KEY_1,
      Key::KEY_2,
      Key::KEY_3,
      Key::KEY_4,
      Key::KEY_5,
      Key::KEY_6,
      Key::KEY_7,
      Key::KEY_8,
      Key::KEY_9
    };
  }
}