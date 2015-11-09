#include "ImageProcessor.hpp"
#include "GridLED.hpp"
#include <list>
#include <Magick++.h>
#include <memory>

class Controller {

private:
  std::unique_ptr<ImageProcessor> imgProc;
  std::unique_ptr<GridLED> grid;
  std::list<cv::Mat> imgGIFasList;
  const uint16_t fps_in_ms = 33; //about 30 fps

  cv::Mat magick2Mat(Magick::Image&);
  
public:
  Controller(uint16_t numLEDs, uint8_t grid_cols, uint8_t grid_rows);
  void readGIF(char* imageGIF);
  void show(unsigned int duration_ms);
};
