//#include "UnitPool.h"
//#include "Unit.h"
//
//namespace Fatboy
//{
//  void UnitPool::addUnit(std::shared_ptr<Unit> obj)
//  {
//    _units.insert(obj);
//    obj->load(_spec);
//    for (auto part : obj->getPhysics())
//      _physicMap[part] = obj;
//  }
//
//  void UnitPool::removeUnit(std::shared_ptr<Unit> obj)
//  {
//    _units.erase(obj);
//    for (auto part : obj->getPhysics())
//      _physicMap.erase(part);
//  }
//
//  void UnitPool::load(YolonaOss::GL::DrawSpecification* spec)
//  {
//    _spec = spec;
//  }
//
//  void UnitPool::draw()
//  {
//    for (auto unit : _units) {
//      unit->draw();
//    }
//  }
//
//  std::shared_ptr<Unit> UnitPool::physicBodyToUnit(std::shared_ptr<Suthanus::PhysicObject> phys)
//  {
//    if (!_physicMap.count(phys))
//      return nullptr;
//    std::weak_ptr<Unit> p = _physicMap[phys];
//    return p.lock();
//  }
//
//}