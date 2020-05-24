#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"

enum class LobbyPageStatus {
  Pending, Back, Host
};

class LobbyPage : public YolonaOss::GL::Drawable {
public:
  LobbyPage(std::shared_ptr<ClientConfiguration> config);

  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();

  LobbyPageStatus getStatus();
private:
  void goBack();
  void hostGame();

  std::unique_ptr<DialogPage> _page;
  
  LobbyPageStatus                      _status = LobbyPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
};