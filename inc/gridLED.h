#include "LPD8806.h"

class gridLED {

  uint8_t *gridAsRGBArray; // (numLEDs x 3) x 1 RGB array

  // width = 5, length = 5 //
  const uint16_t numLEDs = 25;     // Number of RGB LEDs in strand

public:

  gridLED();
  ~gridLED();
  gridLED& operator= (const gridLED& other);
  uint8_t& operator() (uint8_t row, uint8_t col); // behave as though RGB array is 2D
  void show(void);
  void setRGBArray(uint8_t* inputArray);
  void clearLEDs(void);
 
};
