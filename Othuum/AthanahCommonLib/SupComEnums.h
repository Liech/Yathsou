#pragma once

namespace Athanah {
  enum class TechLevel {
    T0, T1, T2, T3, T4
  };

  enum class ButtonStatus {
    Normal, Hover, Pressed
  };
  enum class SelectableButtonStatus {
    Normal, Hover, Selected, SelectedHover
  };
  enum class Faction {
    Aeon, Cybran, Uef, Seraphim, Undefined
  };
}