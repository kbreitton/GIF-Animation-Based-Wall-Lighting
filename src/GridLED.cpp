#include "GridLED.hpp"

GridLED::GridLED(uint16_t numLEDs_total, uint8_t cols_total, uint8_t rows_total) {
  _cols_total = cols_total;
  _rows_total = rows_total;
  _numLEDs_total = numLEDs_total;
  assert(_cols_total*_rows_total == _numLEDs_total);
  strip = std::unique_ptr<LPD8806> (new LPD8806(_numLEDs_total));
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

void GridLED::setPixels(const std::vector<uint8_t>& inputBGRVector) {
  assert(inputBGRVector.size() == _numLEDs_total*3);

  uint8_t b;
  uint8_t g;
  uint8_t r;

  for(int i=0; i<_numLEDs_total; i++){
    b = inputBGRVector[i*3];
    g = inputBGRVector[i*3+1];
    r = inputBGRVector[i*3+2];
    strip->setPixelColor(i,r,g,b);
  }
 
}

void GridLED::show(void) {
  strip->show();
}

void GridLED::show(const std::vector<uint8_t>& inputBGRVector) {
  setPixels(inputBGRVector);
  show();
}

void GridLED::clearLEDs(void) {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  for(int i=0; i<_numLEDs_total; i++){
    strip->setPixelColor(i,r,g,b);
  }

  show();

}


