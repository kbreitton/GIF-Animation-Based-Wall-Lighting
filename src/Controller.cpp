#include "Controller.hpp"


Controller::Controller() {
  using namespace std;
  grid = unique_ptr<GridLED> (new GridLED(numLEDs_total, cols_total, rows_total));
  imgProc = unique_ptr<ImageProcessor> (new ImageProcessor());
}

//Controller::Controller() {}

void Controller::readGIF(char* imageGIF) {
  using namespace Magick;
  using namespace std;
  using namespace cv;

  imgGIFasList.clear();
  list<Image> magickImageList;
  readImages( &magickImageList, imageGIF);

  for (auto it = magickImageList.begin(); it != magickImageList.end(); it++) {
    Mat imageMat = magick2Mat(*it);
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
  Mat image = Mat(height, width, CV_8UC3, bytes).clone();
  
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
