#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"

enum class LobbyLoadingPageStatus {
  Pending, Back, Proceed, Error
};

class LobbyLoadingPage : public YolonaOss::GL::Drawable {
public:
  LobbyLoadingPage(std::shared_ptr<ClientConfiguration> config);

  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();

  LobbyLoadingPageStatus getStatus();
private:
  void goBack();

  std::unique_ptr<DialogPage> _page;
  
  LobbyLoadingPageStatus               _status = LobbyLoadingPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
};