#include <iostream>
#include "Serial/Unit.h"
#include "Serial/Player.h"
#include "Lib/nop/serializer.h"
#include "Lib/nop/utility/stream_writer.h"
#include "Lib/nop/structure.h"

int main() { 
  std::cout << "Purge" << std::endl;
  Serial::Unit x;
  x.position.Y = 2;
  using Writer = nop::StreamWriter<std::stringstream>;
  nop::Serializer<Writer> serializer;
  serializer.Write(x);
  Serial::Player p;
} 