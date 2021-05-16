#pragma once

#include <memory>
#include <string>

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"

namespace Ahwassa {
  class UIElement {
  public:
    
    //Events
    virtual void draw() {};
    virtual void update() {};
    virtual void startFocusEvent() {};
    virtual void endFocusEvent  () {};
    virtual void mouseEnterEvent() {};
    virtual void mouseLeaveEvent() {};
    virtual bool focusKeyEvent(                           Iyathuum::Key button, Iyathuum::KeyStatus status) { return false; };
    virtual bool      keyEvent(                           Iyathuum::Key button, Iyathuum::KeyStatus status) { return false; };
    virtual bool mouseEvent(     glm::vec2 localPosition, Iyathuum::Key button, Iyathuum::KeyStatus status) { return false; };
    virtual bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button                            ) { return false; };
    virtual bool mouseWheelEvent(glm::vec2 movement                                                       ) { return false; };
    virtual bool mouseMoveEvent( glm::vec2 current, glm::vec2 movement                                    ) { return false; };
    virtual bool dropEvent     (const std::string filePath)                                                 {return false;}

    //Position
    const Iyathuum::glmAABB<2>& getLocalPosition()  const;
    const Iyathuum::glmAABB<2>  getGlobalPosition() const;
    void                        setLocalPosition(Iyathuum::glmAABB<2>);
    void                        setSize(const glm::vec2&);

    void        setParent(UIElement* parent);
    UIElement*  getParent() const;

    virtual void setVisible(bool visible);
    bool         isVisible() const;
    bool         isInside(glm::vec2);
  private:
    Iyathuum::glmAABB<2> _localPosition;
    UIElement*           _parent  = nullptr;
    bool                 _visible = true;
  };
}