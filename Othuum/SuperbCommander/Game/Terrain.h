#pragma once

namespace Superb {
  class World;
  
  class Terrain {
    public:
      Terrain();
      virtual ~Terrain() = default;

      void menu();

      void drawMidLayer();

    private:
  };
}