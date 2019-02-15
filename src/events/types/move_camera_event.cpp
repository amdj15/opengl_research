#include "move_camera_event.h"

using namespace Eng;
using namespace Events;

MoveCameraEvent::MoveCameraEvent(float xOffset, float yOffset, float sensitivity): xOffset(xOffset),
                                                                                   yOffset(yOffset),
                                                                                   sensetivity(sensitivity) {}
