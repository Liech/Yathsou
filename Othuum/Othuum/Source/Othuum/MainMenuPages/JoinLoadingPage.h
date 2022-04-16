#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "ClientState.h"

enum class JoinLoadingPageStatus {
  Pending, Back, Proceed, Error
};

class JoinLoadingPage : public Ahwassa::Drawable {
public:
  JoinLoadingPage(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state, Ahwassa::Window*);

  virtual void draw() override;
  void setVisible(bool visible);
  void reset();
  void start(size_t gameID);
  void update();


  JoinLoadingPageStatus getStatus();
private:
  void goBack();
  void finish();

  std::unique_ptr<DialogPage> _page;
  
  JoinLoadingPageStatus                _status = JoinLoadingPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
  std::shared_ptr<ClientState        > _state ;
};