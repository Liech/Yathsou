#pragma once

#include "Updateable.h"
#include <vector>
#include <memory>
namespace YolonaOss {
  namespace GL {
    class UpdateableList : public Updateable
    {
    public:
      UpdateableList() {}
      virtual ~UpdateableList()override {}

      void addUpdateable(std::shared_ptr<Updateable> draw);
      virtual void load(DrawSpecification*) override;
      virtual void update() override;

    private:
      std::vector<std::shared_ptr<Updateable>> _updateable;
    };
  }
}