#pragma once

#include "APDS9960_RPi.h"


#define APDS9960_INT 7

typedef enum gesture_state {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    DEFAULT
} GESTURE_STATE;


class SensorHandler {

private:
  
  GESTURE_STATE _gesture_state;
  
  int isr_flag = 0;
  void interruptRoutine();
  void handleGesture();

  APDS9960_RPi apds;

public:
  SensorHandler();
  GESTURE_STATE getGestureState(void);
};
