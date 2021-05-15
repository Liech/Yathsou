#pragma once


namespace Ahwassa {
  class IMesh {
  public:
    virtual void draw() const = 0;
    virtual void drawInstanced(size_t) const= 0;
  };
}