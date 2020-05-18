#pragma once

#include "Widget.h"
#include <string>
#include "YolonaOss/OpenGL/Keys.h"

namespace YolonaOss {
  namespace Widgets {
    class LineEdit : public Widget
    {
    public:
      LineEdit();
      LineEdit(std::string name, Iyathuum::AABB<2> position);
      ~LineEdit();

      void        setText(std::string text);
      std::string getText();
      
      virtual void load(GL::DrawSpecification*)              override;
      virtual void draw()                                    override;
      virtual bool mouseClick(glm::vec2 position, GL::Key k) override;
      virtual void focusedKeyboardInput(YolonaOss::GL::Key key, YolonaOss::GL::KeyStatus status) override;

    private:
      std::string _text           = "";
      int         _cursorPosition = 3 ;
    };
  }
}