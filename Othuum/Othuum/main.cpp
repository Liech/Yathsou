#include <iostream>
#include "Generated/Unit_generated.h"

int main() { 
  std::cout << "Purge" << std::endl;
  flatbuffers::FlatBufferBuilder builder;
  
  Yathsou::Vec3 p(0, 0, 0);
  auto unit = Yathsou::CreateUnit(builder, &p);  
  builder.Finish(unit);
  auto UNIT = Yathsou::GetUnit(builder.GetBufferPointer());
  UNIT->pos() = p;
} 