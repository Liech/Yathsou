#pragma once

#include "Widget.h"
#include <string>

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


    private:
      std::string _text           = "";
      int         _cursorPosition = 3 ;
    };
  }
}