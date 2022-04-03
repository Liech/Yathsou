#pragma once

#include <string>
#include <functional>
#include <limits>

#include "IyathuumCoreLib/BaseTypes/Keys.h"
#include "AhwassaGraphicsLib/Input/UIElement.h"
#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa {
  class LineEdit : public UIElement, public Drawable
  {
  public:
    LineEdit(Window* w);
    LineEdit(std::string name, Iyathuum::glmAABB<2> position, Window* w, UIElement* parent = nullptr);
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

    static std::function<bool(Iyathuum::Key, std::string)> integerValidator(int min = INT_MIN, int max = INT_MAX);
    static std::function<bool(Iyathuum::Key, std::string)> defaultValidator();

  private:
    std::string _text           ;
    int         _cursorPosition ;
    bool        _hasFocus       ;
    bool        _changed        ;
    std::function<void(std::string)>                _textChangedCallback     ;
    std::function<void(std::string)>                _finishedEditingCallback ;
    std::function<bool(Iyathuum::Key, std::string)> _validator               ;
  };
}