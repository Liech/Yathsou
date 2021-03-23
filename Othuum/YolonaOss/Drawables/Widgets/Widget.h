#pragma once

#include "../../OpenGL/Drawable.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"
#include "IyathuumCoreLib/BaseTypes/AABB.h"
#include "../../OpenGL/InputHandling.h"

namespace YolonaOss {
  namespace Widgets {
    class Widget : public GL::Drawable {
    public:
      Widget(Iyathuum::AABB<2> position, Widget* parent = nullptr) {
        _position = position;
        _parent = parent;
      }
      Widget() {
        _position = Iyathuum::AABB<2>({ 0,0 }, { 100, 100 });
      }

      virtual ~Widget() {
        GL::InputHandling::getInstance().setFocus(nullptr);
      };

      virtual void mouseEnter() {};
      virtual void mouseLeave() {};
      virtual bool mouseClick          (glm::vec2 position, Iyathuum::Key k) { return false; };
      virtual void mouseMove           (glm::vec2 position) {};
      virtual bool mouseStatusChanged  (glm::vec2 position, Iyathuum::Key key, Iyathuum::KeyStatus status) { return false; };
      virtual bool mouseWheel          (glm::vec2 movement){ return false;};
      virtual bool keyboardInput       (Iyathuum::Key key, Iyathuum::KeyStatus status){ return false;};
      virtual void focusedKeyboardInput(Iyathuum::Key key, Iyathuum::KeyStatus status) {};
      virtual void focusStart() {};
      virtual void focusEnd  () {};
      virtual void adjustSize() {};
      virtual glm::vec2 getSizeHint() { return glm::vec2(100, 50); };

      virtual void load(GL::DrawSpecification*) override{}

      Widget* getParent() { return _parent; }
      Iyathuum::AABB<2>& getPosition();
      Iyathuum::AABB<2>  getGlobalPosition() const;      
      void               setPosition(Iyathuum::AABB<2> pos);
      virtual void setVisible(bool visible);
      bool isVisible() { return _visible; }
    private:
      Iyathuum::AABB<2> _position;
      bool              _visible  = false;
      Widget*           _parent = nullptr;
    };
  }
}