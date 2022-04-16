#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "ClientState.h"

enum class HostLoadingPageStatus {
  Pending, Back, Proceed, Error
};

class HostLoadingPage : public Ahwassa::Drawable {
public:
  HostLoadingPage(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state, Ahwassa::Window*);

  virtual void draw()                                  override;
  void setVisible(bool visible);
  void reset();
  void start(Vishala::CreateGameRequest request);
  void update();


  HostLoadingPageStatus getStatus();
private:
  void goBack();
  void finish();

  std::unique_ptr<DialogPage> _page;
  
  HostLoadingPageStatus                _status = HostLoadingPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
  std::shared_ptr<ClientState        > _state ;
};