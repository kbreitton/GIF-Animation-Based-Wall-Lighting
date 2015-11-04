#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <cassert>

#include "LPD8806.hpp"

class GridLED {
  uint16_t _numLEDs;
  uint8_t _cols, _rows;
  std::unique_ptr<LPD8806> strip;
  //uint8_t& operator() (uint8_t y, uint8_t x); // behave as though RGB vector is 2D
  
public:

  GridLED(uint16_t numLEDs, uint8_t cols, uint8_t rows);
  //GridLED(const GridLED& other);
  //GridLED& operator=(const GridLED& other);
  void setPixels(const std::vector<uint8_t>& inputBGRVector); 
  void show(void);
  void show(const std::vector<uint8_t>& inputBGRVector);
  void clearLEDs(void);
 
};
