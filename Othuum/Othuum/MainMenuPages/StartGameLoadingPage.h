#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "ClientState.h"

namespace Iyathuum {
  class ContentLoader;
}
namespace Ahwassa {
  class Label;
}

enum class StartGameLoadingPageStatus {
  HostWait, Pending, Back, Proceed, Error
};

class StartGameLoadingPage : public Ahwassa::Drawable {
public:
  StartGameLoadingPage(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state, Ahwassa::Window*);

  virtual void draw() override;
  void setVisible(bool visible);
  void reset();
  void setLoader(std::shared_ptr<Iyathuum::ContentLoader> loader);
  void LoadGame();
  void HostWait();
  void update();


  StartGameLoadingPageStatus getStatus();
private:
  void goBack();
  void finish();
  void startLoading();

  std::unique_ptr<DialogPage> _page;
  
  StartGameLoadingPageStatus                 _status = StartGameLoadingPageStatus::Pending;
  std::shared_ptr<ClientConfiguration>       _config;
  std::shared_ptr<ClientState        >       _state ;
  std::shared_ptr<Iyathuum::ContentLoader>   _loader;
  std::shared_ptr<Ahwassa::Label> _text;
};