#include <iostream>

#include <IyathuumCoreLib/Singleton/Database.h>
#include <SelenNavigationLib/Maps/NavigationAgent.h>
#include <SuthanusPhysicsLib/PhysicEngine.h>
#include <AhwassaGraphicsLib/Core/Window.h>

int main() {
  Iyathuum::Database<int>::terminate();
  Selen::NavigationAgent<2> agent(glm::vec2(0,0),glm::vec2(0,0));
  Suthanus::PhysicEngine engine;  
  Ahwassa::Window win(100, 100);
  win.run();
  return 0;
}
