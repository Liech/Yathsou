#pragma once

#include "../../OpenGL/Drawable.h"
#include "../../OpenGL/Keys.h"
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
      virtual bool mouseClick          (glm::vec2 position, GL::Key k) { return false; };
      virtual void mouseMove           (glm::vec2 position) {};
      virtual bool mouseStatusChanged  (glm::vec2 position, GL::Key key, GL::KeyStatus status) { return false; };
      virtual bool keyboardInput       (GL::Key key, GL::KeyStatus status){ return false;};
      virtual void focusedKeyboardInput(YolonaOss::GL::Key key, YolonaOss::GL::KeyStatus status) {};
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
    protected:
      bool isVisible() { return _visible; }
    private:
      Iyathuum::AABB<2> _position;
      bool              _visible  = false;
      Widget*           _parent = nullptr;
    };
  }
}