#pragma once

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <cstdint>
#include <cstring>

/*
 * Driver for controlling LPD8806 LED strip
 *
 * base code inspired by the LPD8806 mbed library:
 * https://developer.mbed.org/users/ehbmbed2/code/LPD8806/
 *
 */
class LPD8806 {

public:
  LPD8806(uint16_t n);
  ~LPD8806();
  void
    show(void),
    setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b),
    setPixelColor(uint16_t n, uint32_t c);
  uint16_t numPixels(void);
  uint32_t Color(uint8_t, uint8_t, uint8_t);

private:
  void begin(void);
  uint8_t  *pixels;     // Holds LED color values
  uint16_t numLEDs;     // Number of RGB LEDs in strand
  void writezeros(uint16_t n);
  const int channelSPI = 0;
  const int speedSPI = 2000000;
};
