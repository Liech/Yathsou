#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "VishalaNetworkLib/Serializable/CreateGameRequest.h"
#include "YolonaOss/Drawables/Widgets/LineEdit.h"

enum class HostPageStatus {
  Pending, Back, Host
};

class HostGamePage : public YolonaOss::GL::Drawable {
public:
  HostGamePage(std::shared_ptr<ClientConfiguration> config);

  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();

  Vishala::CreateGameRequest getResult();
  HostPageStatus getStatus();
private:
  void goBack();
  void hostGame();

  std::unique_ptr<DialogPage> _page;
  std::shared_ptr<YolonaOss::Widgets::LineEdit>   _gameName;
  HostPageStatus                                  _status = HostPageStatus::Pending;
  std::shared_ptr<ClientConfiguration>            _config;
};