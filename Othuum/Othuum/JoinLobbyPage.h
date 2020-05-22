#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"

enum class JoinLobbyPageStatus {
  Pending, Back
};

class JoinLobbyPage : public YolonaOss::GL::Drawable {
public:
  JoinLobbyPage(std::shared_ptr<ClientConfiguration> config);

  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();

  JoinLobbyPageStatus getStatus();
private:
  void goBack();

  std::unique_ptr<DialogPage> _page;
  
  JoinLobbyPageStatus                  _status = JoinLobbyPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
};