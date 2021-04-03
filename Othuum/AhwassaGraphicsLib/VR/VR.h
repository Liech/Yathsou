#pragma once

namespace vr
{
  class IVRSystem;
  struct VREvent_t;
}

//https://github.com/osudrl/CassieVrControls/wiki/OpenVR-Quick-Start
namespace Ahwassa {
  class VR {
  public:
    VR();
    ~VR();

    void update();

  private:
    void vrEvent(const vr::VREvent_t&);

    vr::IVRSystem* vr_pointer = nullptr;
  };
}