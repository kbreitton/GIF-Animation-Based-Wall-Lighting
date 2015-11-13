#include "Controller.hpp"


//Controller::Controller(uint16_t numLEDs, uint8_t grid_cols, uint8_t grid_rows) {
  //using namespace std;
  //grid = unique_ptr<GridLED> (new GridLED(numLEDs, grid_cols, grid_rows));
  //imgProc = unique_ptr<ImageProcessor> (new ImageProcessor());
/*}*/

Controller::Controller() {}

void Controller::readGIF(char* imageGIF) {
  using namespace Magick;
  using namespace std;
  using namespace cv;

  imgGIFasList.clear();
  list<Image> magickImageList;
  readImages( &magickImageList, imageGIF);

  for (auto it = magickImageList.begin(); it != magickImageList.end(); it++) {
    Mat imageMat = magick2Mat(*it).clone();
    imgGIFasList.push_back(imageMat);
  }
}

cv::Mat Controller::magick2Mat(Magick::Image& magickImage) {
  using namespace cv;

  int width= magickImage.size().width();
  int height = magickImage.size().height();

  uint8_t* bytes = new uint8_t[width*height*3];
  magickImage.write(0,0, width, height, "BGR", MagickCore::CharPixel, bytes);
  //Mat image = Mat(sizeof(bytes), 1, CV_8U, bytes).clone();
  //image = image.reshape(0, height);
  Mat image = Mat(1, height*width*3, CV_8U, bytes);
  
  delete [] bytes;
  return image;
}

void Controller::show(unsigned int duration_ms) {
  using namespace std;
  vector<uint8_t> vec;
  
  unsigned int startTime = millis();
  while(millis() - startTime < duration_ms) {
    for (auto it = imgGIFasList.begin(); it != imgGIFasList.end(); it++) {
      if (millis() - startTime > duration_ms) {
        break;
      }
      imgProc->readImage(*it);
      imgProc->reconfigureImage(cols_panels, rows_panels, 
                                cols_leds_per_panel, rows_leds_per_panel);
      vec = imgProc->convertToBGRVector();
      grid->show(vec);
      delay(fps_in_ms); 
    }
  }

  //grid->clearLEDs();
}
