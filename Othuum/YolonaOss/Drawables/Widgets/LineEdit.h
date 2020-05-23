#pragma once

#include "Widget.h"
#include <string>
#include <functional>
#include "YolonaOss/OpenGL/Keys.h"

namespace YolonaOss {
  namespace Widgets {
    class LineEdit : public Widget
    {
    public:
      LineEdit();
      LineEdit(std::string name, Iyathuum::AABB<2> position, Widget* parent = nullptr);
      ~LineEdit();

      void        setText(std::string text);
      std::string getText();
      void        setTextChangedCallback (std::function<void(std::string)> callback);
      void        setEditFinishedCallback(std::function<void(std::string)> callback);

      virtual void load(GL::DrawSpecification*)              override;
      virtual void draw()                                    override;
      virtual bool mouseClick(glm::vec2 position, GL::Key k) override;
      virtual void focusedKeyboardInput(YolonaOss::GL::Key key, YolonaOss::GL::KeyStatus status) override;
      virtual void setVisible(bool visible) override;
      virtual void focusStart() override;
      virtual void focusEnd() override;


    private:
      std::string _text           = "";
      int         _cursorPosition = 3 ;
      bool        _hasFocus = false;
      bool        _changed = false;
      std::function<void(std::string)> _textChangedCallback     = [](std::string s){};
      std::function<void(std::string)> _finishedEditingCallback = [](std::string s){};
    };
  }
}