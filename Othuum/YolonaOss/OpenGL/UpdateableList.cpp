#include "OpenGL/UpdateableList.h"

namespace YolonaOss {
  namespace GL {

    void UpdateableList::addUpdateable(std::shared_ptr<Updateable> drawable) {
      _updateable.push_back(drawable);
    }

    void UpdateableList::load(DrawSpecification* d)
    {
      for (int i = 0; i < _updateable.size(); i++)
        _updateable[i]->load(d);
    }

    void UpdateableList::update()
    {
      for (int i = 0; i < _updateable.size(); i++)
        _updateable[i]->update();
    }
  }
}