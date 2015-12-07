#pragma once

#include "APDS9960_RPi.h"
#include "Gesture_State.hpp"

#define APDS9960_INT 7

class SensorHandler {

private:
  
  GESTURE_STATE _gesture_state;
  
  static int isr_flag;
  static void interruptRoutine();
  void handleGesture();

  APDS9960_RPi apds;

public:
  SensorHandler();
  const GESTURE_STATE& getGestureState(void);
};
