#pragma once


namespace Ahwassa {
  class IMesh {
  public:
    virtual void draw() = 0;
    virtual void drawInstanced(size_t) = 0;
  };
}