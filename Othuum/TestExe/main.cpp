#include <iostream>

#include <IyathuumCoreLib/Singleton/Database.h>
#include <SelenNavigationLib/Maps/NavigationAgent.h>
#include <SuthanusPhysicsLib/PhysicEngine.h>
#include <AhwassaGraphicsLib/Core/Window.h>
#include <filesystem>

void enforceWorkingDir(std::string exeDir) {
  const size_t last_slash_idx = exeDir.find_last_of("\\/");
  if (std::string::npos != last_slash_idx)
  {
    exeDir.erase(last_slash_idx + 1);
  }
  std::filesystem::current_path(exeDir);
}

int main(int argc, char** argv) {
  enforceWorkingDir(std::string(argv[0]));

  Iyathuum::Database<int>::terminate();
  Selen::NavigationAgent<2> agent(glm::vec2(0,0),glm::vec2(0,0));
  Suthanus::PhysicEngine engine;  
  Ahwassa::Window win(100, 100);
  win.run();
  return 0;
}
