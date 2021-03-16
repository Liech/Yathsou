#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "ClientState.h"

enum class StartGameLoadingPageStatus {
  HostWait, Pending, Back, Proceed, Error
};

class StartGameLoadingPage : public YolonaOss::GL::Drawable {
public:
  StartGameLoadingPage(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state);

  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();
  void setLoader();
  void LoadGame();
  void HostWait();
  void update();


  StartGameLoadingPageStatus getStatus();
private:
  void goBack();
  void finish();
  void startLoading();

  std::unique_ptr<DialogPage> _page;
  
  StartGameLoadingPageStatus           _status = StartGameLoadingPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
  std::shared_ptr<ClientState        > _state ;
};