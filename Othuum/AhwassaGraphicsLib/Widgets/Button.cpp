//#include "Button.h"
//
//#include "glad/glad.h"
//#include "IyathuumCoreLib/Singleton/Database.h"
//
//namespace Ahwassa {
//  Button::Button(Window* w) : Drawable(w)
//  {
//    _name = "Def";
//    setVisible(true);
//  }
//
//  Button::Button(std::string name, Iyathuum::glmAABB<2> position, std::function<void(void)> clickedFunction, Window* w, UIElement* parent) : Drawable(w)
//  {
//    _clickedFunction = clickedFunction;
//    _name = name;
//    setVisible(true);
//  }
//
//  Button::~Button()
//  {
//    setVisible(false);
//  }
//
//  void Button::draw()
//  {
//    if (!isVisible())
//      return;
//
//    RectangleRenderer::start();
//    RectangleRenderer::drawRectangle(getGlobalPosition(), _hovered ? glm::vec3(0.8f, 0.8f, 0.8f) : glm::vec3(0.4f, 0.4f, 0.4f));
//    RectangleRenderer::end();
//    glm::vec2 textSize = TextRenderer::getTextSize(_name, 1);
//    glm::vec2 spacing = (glm::vec2(getGlobalPosition().getSize()[0], getGlobalPosition().getSize()[1]) - textSize) / 2.0f;
//    TextRenderer::start();
//    glm::vec2 pos = Util<2>::array2Vec(getGlobalPosition().getPosition()) + spacing;
//    TextRenderer::drawText(_name, pos, 1, glm::vec3(0, 0, 0));
//    TextRenderer::end();
//  }
//
//  void Button::mouseEnter() {
//    _hovered = true;
//  };
//
//  void Button::mouseLeave() {
//    _hovered = false;
//  };
//
//  bool Button::mouseClick(glm::vec2 position, Iyathuum::Key k) {
//    _clickedFunction();
//    return true;
//  };
//
//  void Button::setVisible(bool visible) {
//    if (visible && !isVisible())
//      Iyathuum::Database<Widgets::Widget*>::add(this, { "MouseClick" });
//    else if (!visible && isVisible())
//      Iyathuum::Database<Widgets::Widget*>::remove(this);
//    Widget::setVisible(visible);
//  }
//
//  void Button::setText(std::string t)
//  {
//    _name = t;
//  }
//}