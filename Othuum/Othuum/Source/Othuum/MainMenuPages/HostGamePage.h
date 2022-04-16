#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "VishalaNetworkLib/Serializable/CreateGameRequest.h"
#include "AhwassaGraphicsLib/Widgets/LineEdit.h"

enum class HostPageStatus {
  Pending, Back, Host
};

class HostGamePage : public Ahwassa::Drawable {
public:
  HostGamePage(std::shared_ptr<ClientConfiguration> config, Ahwassa::Window*);

  virtual void draw()                                  override;
  void setVisible(bool visible);
  void reset();

  Vishala::CreateGameRequest getResult();
  HostPageStatus getStatus();
private:
  void goBack();
  void hostGame();

  std::unique_ptr<DialogPage> _page;
  std::shared_ptr<Ahwassa::LineEdit>   _gameName;
  HostPageStatus                                  _status = HostPageStatus::Pending;
  std::shared_ptr<ClientConfiguration>            _config;
};