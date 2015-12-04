#include "ImageProcessor.hpp"
#include "GridLED.hpp"
#include <list>
#include <Magick++.h>
#include <memory>
#include <cassert>

class Controller {

private:
  const uint8_t leds_per_panel = 36;
  const uint8_t cols_leds_per_panel = 6;
  const uint8_t rows_leds_per_panel = 6;
  const uint8_t cols_panels = 3;
  const uint8_t rows_panels = 3;
  const uint8_t cols_total = cols_leds_per_panel * cols_panels;
  const uint8_t rows_total = rows_leds_per_panel * rows_panels;
  const uint16_t numLEDs_total = cols_total * rows_total;

  std::unique_ptr<ImageProcessor> imgProc;
  //std::unique_ptr<GridLED> grid(numLEDs_total, cols_total, rows_total);
  std::unique_ptr<GridLED> grid;
  std::list<cv::Mat> imgGIFasList;

  const uint16_t fps_in_ms = 25; //about 30 fps

  cv::Mat magick2Mat(Magick::Image&);
  
public:
  //Controller(uint16_t numLEDs, uint8_t grid_cols, uint8_t grid_rows);
  Controller();
  void readGIF(char* imageGIF);
  void show(unsigned int duration_ms);
};
