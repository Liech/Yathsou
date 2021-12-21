#include <iostream>
#include <filesystem>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Input/IMGUIRenderer.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

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
  int width = 800;
  int height = 600;
  //int height = 1500;
  //int width = 2500;
  Ahwassa::Window w(width, height);

  std::string scPath = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Supreme Commander Forged Alliance";
  std::string mapPath = scPath + "\\maps";

  std::string soundPath = scPath + "\\sounds\\Interface";

  {
    Ahwassa::Background b(&w);
    std::unique_ptr<Ahwassa::FPS> fps;

    std::shared_ptr<Ahwassa::DeferredComposer> composer;
    std::shared_ptr<Ahwassa::BasicTexture2DRenderer> textureRenderer;
    std::shared_ptr<Ahwassa::BasicBoxRenderer> boxRenderer;
    std::unique_ptr<Ahwassa::IMGUIRenderer> ui;

    w.Startup = [&]() {
      ui = std::make_unique<Ahwassa::IMGUIRenderer>(&w);
      fps = std::make_unique<Ahwassa::FPS>(&w);
    };
    int counter = 0;
    bool show_demo_window = true;
    glm::vec4 clear_color(1,1,1,1);
    float f = 0;

    w.Update = [&]() {

      b.draw();

      ui->start();

      ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

      ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
      ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
      //ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();

      ui->end();

      fps->draw();
    };
    w.run();
  }
  Iyathuum::DatabaseTerminator::terminateAll();
}