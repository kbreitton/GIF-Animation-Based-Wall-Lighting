#include "Controller.hpp"


Controller::Controller(uint16_t numLEDs, uint8_t grid_cols, uint8_t grid_rows) {
  using namespace std;
  grid = unique_ptr<GridLED> (new GridLED(numLEDs, grid_cols, grid_rows));
  imgProc = unique_ptr<ImageProcessor> (new ImageProcessor());
}

void Controller::readGIF(char* imageGIF) {
  using namespace Magick;
  using namespace std;
  using namespace cv;

  imageGIFasList.clear();
  list<Image> magickImageList;
  readImages( &magickImageList, imageGIF);

  for (auto it = magickImageList.begin(); it != magickImageList.end(); it++) {
    Mat imageMat = magick2Mat(*it);
    imageGIFasList.push_back(imageMat);
  }
}

void Controller::setDuration(unsigned int duration_ms) {
  _duration_ms = duration_ms;
}

cv::Mat Controller::magick2Mat(Magick::Image magickImage) {
  using namespace cv;

  int width= magickImage.size().width();
  int height = magickImage.size().height();

  uint8_t* bytes = new uint8_t[width*height*3];
  magickImage.write(0,0, width, height, "BGR", MagickCore::CharPixel, bytes);
  Mat image = cv::Mat(sizeof(bytes), 1, CV_8U, bytes).clone();
  image = image.reshape(0, height);

  delete [] bytes;
  return image;
}

void Controller::show(void) {
  using namespace std;
  vector<uint8_t>& vectorBuff;

  for (auto it = imgGIFasList.begin(); it != imgGIFasList.end(); it++) {
    imgProc.readImage(*it);
    vectorBuff = imgProc.convertToBGRVector();
    grid->show(vectorBuff);
    delay(fps_in_ms); 
  }

  grid->clearLEDs();
}
