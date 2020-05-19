#include "MainMenuPage.h"

#include <iostream>

#include "DialogPage.h"


MainMenuPage::MainMenuPage(int resolutionX, int resolutionY){
  _page = std::make_unique<DialogPage>(resolutionX,resolutionY);
  _page->addButton("HALLODRI", []() {std::cout << "Moin" << std::endl; });
  _page->addButton("OLA", []() {std::cout << "Una Serviza Por Favor" << std::endl; });
}

void MainMenuPage::draw() {
  _page->draw();
}

