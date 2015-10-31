#include "LPD8806.hpp"

LPD8806::LPD8806(uint16_t n) {
// Allocate 3 bytes per pixel:
  pixels = new uint8_t[n*3];
  if (pixels != nullptr) {
    memset(pixels, 0x80, n * 3); // Init to RGB 'off' state
    numLEDs     = n;
  }

  begin();
}

LPD8806::~LPD8806() {
  r = 0;
  g = 0;
  b = 0;
 
  for(int i=0; i<numLEDs; i++){
    strip.setPixelColor(i,r,g,b);
  }

  strip.show();  
  
  delete [] pixels; 
}

void LPD8806::begin(void) {
  wiringPiSetupSys();
  wiringPiSPISetup(channelSPI, speedSPI);

  // Issue initial latch to 'wake up' strip (latch length varies w/numLEDs)
  writezeros(3 * ((numLEDs + 63) / 64));
}

uint16_t LPD8806::numPixels(void) {
  return numLEDs;
}

void LPD8806::writezeros(uint16_t n) {
  uint8_t zeros = 0x00;
  while (n--) wiringPiSPIDataRW(channelSPI, &zeros, 1);
}

// This is how data is pushed to the strip.  Unfortunately, the company
// that makes the chip didnt release the  protocol document or you need
// to sign an NDA or something stupid like that, but we reverse engineered
// this from a strip controller and it seems to work very nicely!
void LPD8806::show(void) {
  uint16_t nB = numLEDs * 3; // 3 bytes per LED

  for (uint16_t i=0; i<nB; i++ ) {
    wiringPiSPIDataRW(channelSPI, &pixels[i], 1);
  }

  // Write latch at end of data; latch length varies with number of LEDs
  writezeros(3 * ((numLEDs + 63) / 64));

  // We need to have a delay here, a few ms seems to do the job
  // shorter may be OK as well - need to experiment :(
// wait_ms(3);
}

// Convert R,G,B to combined 32-bit color
uint32_t LPD8806::Color(uint8_t r, uint8_t g, uint8_t b) {
  // Take the lowest 7 bits of each value and append them end to end
  // We have the top bit set high (its a 'parity-like' bit in the protocol
  // and must be set!)
  return 0x808080 | ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
}

// store the rgb component in our array
void LPD8806::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  if (n >= numLEDs) return; // '>=' because arrays are 0-indexed

  pixels[n*3  ] = g | 0x80;
  pixels[n*3+1] = r | 0x80;
  pixels[n*3+2] = b | 0x80;
}

void LPD8806::setPixelColor(uint16_t n, uint32_t c) {
  if (n >= numLEDs) return; // '>=' because arrays are 0-indexed

  pixels[n*3  ] = (c >> 16) | 0x80;
  pixels[n*3+1] = (c >>  8) | 0x80;
  pixels[n*3+2] =  c        | 0x80;
}

