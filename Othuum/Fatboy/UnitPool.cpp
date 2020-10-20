#include "UnitPool.h"
#include "Unit.h"

namespace Fatboy
{
  void UnitPool::addUnit(std::shared_ptr<Unit> obj)
  {
    _units.insert(obj);
    obj->load(_spec);
  }

  void UnitPool::removeUnit(std::shared_ptr<Unit> obj)
  {
    _units.erase(obj);
  }

  void UnitPool::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
  }

  void UnitPool::draw()
  {
    for (auto unit : _units) {
      unit->draw();
    }
  }
}