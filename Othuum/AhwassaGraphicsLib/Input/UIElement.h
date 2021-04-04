#pragma once

#include <memory>

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"

namespace Ahwassa {
  class UIElement {
  public:
    
    //Events
    virtual void update() {};
    virtual void startFocusEvent() {};
    virtual void endFocusEvent  () {};
    virtual bool focusKeyEvent(                           Iyathuum::Key button, Iyathuum::KeyStatus status) { return false; };
    virtual bool      keyEvent(                           Iyathuum::Key button, Iyathuum::KeyStatus status) { return false; };
    virtual bool mouseEvent(     glm::vec2 localPosition, Iyathuum::Key button, Iyathuum::KeyStatus status) { return false; };
    virtual bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button                            ) { return false; };
    virtual bool mouseWheelEvent(glm::vec2 movement                                                       ) { return false; };
    virtual bool mouseMoveEvent( glm::vec2 current, glm::vec2 movement                                    ) { return false; };

    //Position
    const Iyathuum::glmAABB<2>& getLocalPosition()  const;
    const Iyathuum::glmAABB<2>  getGlobalPosition() const;
    void                        setLocalPosition(Iyathuum::glmAABB<2>);

    void                        setParent(std::shared_ptr<UIElement> parent);
    std::shared_ptr<UIElement>  getParent() const;

    virtual void setVisible(bool visible);
    bool         isVisible() const;

  private:
    Iyathuum::glmAABB<2>     _localPosition;
    std::weak_ptr<UIElement> _parent;
    bool                     _visible = true;
  };
}