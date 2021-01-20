#pragma once


namespace YolonaOss
{
  class WASDInputable
  {
  public:
    virtual void inputLeft () {};
    virtual void inputRight() {};
    virtual void inputUp   () {};
    virtual void inputDown () {};

    virtual void endLeft   () {};
    virtual void endRight  () {};
    virtual void endUp     () {};
    virtual void endDown   () {};

    virtual void startLeft () {};
    virtual void startRight() {};
    virtual void startUp   () {};
    virtual void startDown () {};

    virtual void inputInteract()  {}; // E
    virtual void inputSpecial()   {}; // Q
    virtual void inputInventory() {}; // F

    virtual void startInteract()  {}; // E
    virtual void startSpecial()   {}; // Q
    virtual void startInventory() {}; // F

    virtual void endInteract()    {}; // E
    virtual void endSpecial()     {}; // Q
    virtual void endInventory()   {}; // F
  };
}