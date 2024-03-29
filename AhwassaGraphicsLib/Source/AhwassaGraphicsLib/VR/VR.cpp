#include "VR.h"

#include <iostream>

#include <openvr.h>

namespace Ahwassa {
  VR::VR() {  
    vr::EVRInitError eError = vr::VRInitError_None;
    vr_pointer = VR_Init(&eError, vr::VRApplication_Background);
    if (eError != vr::VRInitError_None)
    {
      vr_pointer = NULL;
      printf("Unable to init VR runtime: %s \n",
        VR_GetVRInitErrorAsEnglishDescription(eError));
      exit(EXIT_FAILURE);
    }
  }

  void VR::update() {
    //vr_pointer->TriggerHapticPulse(3, 0, 3000);
    vr::VREvent_t event;
    if (vr_pointer->PollNextEvent(&event, sizeof(event)))
    {
      switch (event.eventType)
      {
      case vr::VREvent_TrackedDeviceActivated:
        std::cout << "EVENT (OpenVR) Device : " << event.trackedDeviceIndex << std::endl;
        break;

      default:
        std::cout << "EVENT--(OpenVR) Event: " << event.trackedDeviceIndex <<" " << event.eventType << std::endl;
        vrEvent(event);
      }
    }
  }

  void VR::vrEvent(const vr::VREvent_t& e) {
    
  }

  VR::~VR() {
    if (vr_pointer != NULL)
      vr::VR_Shutdown();
  }
}