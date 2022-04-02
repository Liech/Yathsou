#include <iostream>

#include <IyathuumCoreLib/Singleton/Database.h>
#include <SelenNavigationLib/Maps/NavigationAgent.h>
#include <SuthanusPhysicsLib/PhysicEngine.h>

int main() {
  Iyathuum::Database<int>::terminate();
  Selen::NavigationAgent<2> agent(glm::vec2(0,0),glm::vec2(0,0));
  Suthanus::PhysicEngine engine;
  return 0;
}
