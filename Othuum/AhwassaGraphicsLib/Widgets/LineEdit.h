#pragma once

#include <string>
#include <functional>

#include "AhwassaGraphicsLib/Input/UIElement.h"
#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa {
  class LineEdit : public UIElement, public Drawable
  {
  public:
    LineEdit(Window* w);
    LineEdit(std::string name, Iyathuum::glmAABB<2> position, Window* w, std::shared_ptr<UIElement> parent = nullptr);
    ~LineEdit();

    void        setText(std::string text);
    std::string getText();
    void        setTextChangedCallback (std::function<void(std::string)> callback);
    void        setEditFinishedCallback(std::function<void(std::string)> callback);
    void        setValidator(std::function<bool(Iyathuum::Key, std::string)> validator);

    virtual void draw()                                    override;
    virtual bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button);
    virtual bool focusKeyEvent(Iyathuum::Key button, Iyathuum::KeyStatus status);
    virtual void startFocusEvent();
    virtual void endFocusEvent();

    static std::function<bool(Iyathuum::Key, std::string)> integerValidator(int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());
    static std::function<bool(Iyathuum::Key, std::string)> defaultValidator();

  private:
    std::string _text = "";
    int         _cursorPosition = 3;
    bool        _hasFocus = false;
    bool        _changed = false;
    std::function<void(std::string)>        _textChangedCallback = [](std::string s) {};
    std::function<void(std::string)>        _finishedEditingCallback = [](std::string s) {};
    std::function<bool(Iyathuum::Key, std::string)> _validator = defaultValidator();
  };
}