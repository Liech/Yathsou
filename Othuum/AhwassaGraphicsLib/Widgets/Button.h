//#pragma once
//
//#include <string>
//#include <functional>
//
//#include "Input/UIElement.h"
//#include "Drawables/Drawable.h"
//
//namespace Ahwassa {
//  class Button : public UIElement, public Drawable
//  {
//  public:
//    Button(Window* w);
//    Button(std::string name, Iyathuum::glmAABB<2> position, std::function<void(void)> clickedFunction, Window* w,UIElement* parent = nullptr);
//    ~Button();
//
//    virtual void draw() override;
//
//    virtual void mouseEnter() override;
//    virtual void mouseLeave() override;
//    virtual bool mouseClick(glm::vec2 position, Iyathuum::Key k) override;
//    virtual void setVisible(bool visible) override;
//
//    void setText(std::string t);
//  private:
//    std::string               _name;
//    std::function<void(void)> _clickedFunction;
//
//    bool _hovered = false;
//  };
//}