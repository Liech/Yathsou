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
    virtual bool focusKeyEvent(                           const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) { return false; };
    virtual bool      keyEvent(                           const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) { return false; };
    virtual bool mouseEvent(     const glm::vec2& localPosition, const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) { return false; };
    virtual bool mouseClickEvent(const glm::vec2& localPosition, const Iyathuum::Key& button                            ) { return false; };
    virtual bool mouseWheelEvent(const glm::vec2& movement                                                       ) { return false; };
    virtual bool mouseMoveEvent( const glm::vec2& current, const glm::vec2& movement                             ) { return false; };
    virtual bool dropEvent     (const std::string& filePath)                                                 {return false;}

    //Position
    const Iyathuum::glmAABB<2>& getLocalPosition()  const;
    const Iyathuum::glmAABB<2>  getGlobalPosition() const;
    void                        setLocalPosition(const Iyathuum::glmAABB<2>&);
    void                        setSize(const glm::vec2&);

    void        setParent(UIElement* parent);
    UIElement*  getParent() const;

    virtual void setVisible(bool visible);
    bool         isVisible() const;
    virtual bool isInside(const glm::vec2&, const Iyathuum::Key&);
  private:
    Iyathuum::glmAABB<2> _localPosition;
    UIElement*           _parent  = nullptr;
    bool                 _visible = true;
  };
}