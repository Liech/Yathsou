#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"

enum class OptionsPageStatus {
  Pending, Back
};

class OptionsPage : public Ahwassa::Drawable {
public:
  OptionsPage(std::shared_ptr<ClientConfiguration> config, Ahwassa::Window*);

  virtual void draw()                                  override;
  void setVisible(bool visible);
  void reset();
  bool requiresRestart();

  OptionsPageStatus getStatus();
private:
  void goBack();

  std::unique_ptr<DialogPage> _page;
  
  OptionsPageStatus                    _status = OptionsPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
  bool                                 _requiresRestart = false;
};