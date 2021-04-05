#pragma once

#include <string>
#include <functional>

#include "AhwassaGraphicsLib/Input/UIElement.h"
#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa {
  class Button;
  class Label;
  class LineEdit;

  class ListLayout : public UIElement, public Drawable {
  public:
    ListLayout(Iyathuum::glmAABB<2> position, Window* w, UIElement* parent = nullptr);

    void                        clear();
    int  addElement(std::shared_ptr<UIElement> w);
    void removeWidget(int w);
    virtual void draw() override;
    std::shared_ptr<Button>     addButton(std::string name, std::function<void()> onClicked, Iyathuum::glmAABB<2> size = Iyathuum::glmAABB<2>({ 0.0, 0.0 }, { 200.0, 50.0 }));
    std::shared_ptr<ListLayout> addLayout();
    std::shared_ptr<Label>      addLabel(std::string text);
    std::shared_ptr<LineEdit>   addLineEdit(std::string text);


    void setHorizontal(bool horizontal);
    //virtual void setVisible(bool visible)        override;
    void adjustSize();
    virtual bool mouseWheelEvent(glm::vec2 movement) override;

    void setMaximumSize(glm::vec2 size) { _maximumSize = size; }

    float getCurrentScroll() { return _scroll; }
    void  setCurrentScroll(float scroll) { _scroll = scroll; }
    float getMaximumScroll();

    std::vector<std::shared_ptr<UIElement>> getElements();

  private:
    const float spacing = 0;

    Iyathuum::glmAABB<2>     getElementSize();
    std::array<double, 2> getPotentialSize();

    std::vector<std::shared_ptr<UIElement>> _widgets;
    bool                                    _horizontal = false;
    float                                   _scroll = 0;
    glm::vec2                               _maximumSize = glm::vec2(0, 0);
  };
}