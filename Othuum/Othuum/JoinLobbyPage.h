#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"

enum class JoinLobbyPageStatus {
  Pending, Back
};

class JoinLobbyPage : public YolonaOss::GL::Drawable {
public:
  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();

  JoinLobbyPageStatus getStatus();
  //std::string         getName  ();
private:
  void goBack();

  std::unique_ptr<DialogPage> _page  ;
  
  JoinLobbyPageStatus         _status = JoinLobbyPageStatus::Pending;
};