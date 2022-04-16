#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"

enum class ErrorPageStatus {
  Pending, Back
};

class ErrorPage : public Ahwassa::Drawable {
public:
  ErrorPage(std::shared_ptr<ClientConfiguration> config, Ahwassa::Window*);

  virtual void draw()                                  override;

  void setVisible(bool visible);
  void reset();
  void setMessage(std::string desc, std::string title = "ERROR");

  ErrorPageStatus getStatus();
private:
  void goBack();

  std::unique_ptr<DialogPage>     _page;
  std::shared_ptr<Ahwassa::Label> _desc;
  std::shared_ptr<Ahwassa::Label> _title;
  
  ErrorPageStatus                      _status = ErrorPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
};