#include "GridLED.hpp"

GridLED::GridLED(uint16_t numLEDs) {
  _numLEDs = numLEDs;
  strip = std::unique_ptr<LPD8806> (new LPD8806(_numLEDs));
}

GridLED::~GridLED() {
  //delete strip;
}

/*GridLED::GridLED(const GridLED& other) {*/
  //if (this.strip != other.strip) {
    //_numLEDs = other._numLEDs;
    //strip = other.strip;
  //}
//}

//GridLED::operator=(const GridLED& other) {
  //if (this.strip != other.strip) {
    //_numLEDs = other.numLEDs;
    //strip = other.strip;
  //}

  //return *this;
/*}*/

void GridLED::setPixels(std::vector<uint8_t> inputBGRVector) {
  assert(inputVector.size() == _numLEDs*3);

  uint8_t b;
  uint8_t g;
  uint8_t r;

  for(int i=0; i<_numLEDs; i++){
    b = inputVector[i*3];
    g = inputVector[i*3+1];
    r = inputVector[i*3+2];
    strip->setPixelColor(i,r,g,b);
  }
 
}

void GridLED::show(void) {
  strip->show();
}

void GridLED::show(std::vector<uint8_t> inputBGRVector) {
  setPixels(inputVector);
  show();
}

void GridLED::clearLEDs(void) {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  for(int i=0; i<_numLEDs; i++){
    strip->setPixelColor(i,r,g,b);
  }

  show();

}


