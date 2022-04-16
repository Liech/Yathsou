#pragma once

#include <memory>
#include <functional>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

namespace Ahwassa {
  class ListLayout;
}

enum class DialogPageStatus {
  InProgress,Finished
};

class DialogPage : public Ahwassa::Drawable {
public:
  DialogPage(Ahwassa::Window*);

  virtual void draw() override;
  
  void setVisible(bool visible);

  Ahwassa::ListLayout& layout();

private:
  Iyathuum::glmAABB<2> getAABB();
  const int buttonWidth = 500;
  const int buttonHeight = 100;  

  std::unique_ptr<Ahwassa::ListLayout> _layout        ;
  bool                                 _visible = true;

};