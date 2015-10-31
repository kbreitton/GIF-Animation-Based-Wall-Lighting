#include "LPD8806.hpp"
#include <cstdint>
#include <vector>
#include <memory>
#include <cassert>

class GridLED {

  uint16_t _numLEDs;
  std::unique_ptr<LPD8806> strip;
  
public:

  GridLED(uint16_t numLEDs);
  ~GridLED();
  //GridLED(const GridLED& other);
  //GridLED& operator=(const GridLED& other);
  //uint8_t& operator() (uint8_t row, uint8_t col); // behave as though RGB vector is 2D
  void setPixels(std::vector<uint8_t> inputBGRVector); //1D array, RGB values in a row
  void show(void);
  void show(std::vector<uint8_t> inputBGRVector);
  void clearLEDs(void);
 
};
