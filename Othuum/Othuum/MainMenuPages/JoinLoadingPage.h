#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "ClientState.h"

enum class JoinLoadingPageStatus {
  Pending, Back, Proceed, Error
};

class JoinLoadingPage : public YolonaOss::GL::Drawable {
public:
  JoinLoadingPage(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state);

  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
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