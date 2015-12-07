#include "Controller.hpp"


Controller::Controller() {
  using namespace std;
  grid = unique_ptr<GridLED> (new GridLED(numLEDs_total, cols_total, rows_total));
  imgProc = unique_ptr<ImageProcessor> (new ImageProcessor());
  gestureSensor = unique_ptr<SensorHandler> (new SensorHandler());
  Magick::InitializeMagick(NULL);
//  signal(SIGINT, sigint_handler);
}

//Controller::Controller() {}
//
//void sigint_handler(int x) {
//  grid->clearLEDs();
//}

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
    if (it == magickImageList.begin()) {
      imgProc->determinePerspTransforms(imageMat);
    }
  }
}

cv::Mat Controller::magick2Mat(Magick::Image& magickImage) {
  using namespace cv;

  int width= magickImage.size().width();
  int height = magickImage.size().height();

  uint8_t* bytes = new uint8_t[width*height*3];
  magickImage.write(0,0, width, height, "BGR", MagickCore::CharPixel, bytes);

  /* even though you should have GIFs properly sized beforehand, many
   *  online GIF resizers do not, somehow, size all frames of a GIF 
   *  properly if the aspect ratio is chnaged -- therefore, resizing
   *  must happen here for safety                                    */  
  Mat image = Mat(height, width, CV_8UC3, bytes).clone();
  Mat img_resized;
  Size size(cols_total, rows_total);  
  resize(image, img_resized, size);
  delete [] bytes;
  return img_resized;
}

void Controller::show(unsigned int duration_ms) {
  using namespace std;
  using namespace cv;

  vector<uint8_t> vec;
  Mat output;
  
  unsigned int startTime = millis();
  while(millis() - startTime < duration_ms) {
    for (auto it = imgGIFasList.begin(); it != imgGIFasList.end(); it++) {
      if (millis() - startTime > duration_ms) {
        break;
      }
      imgProc->readImage(*it);
      output = imgProc->perspTransIm( gestureSensor->getGestureState() );
      output = imgProc->reconfigureImage(output, cols_panels, rows_panels, 
                                cols_leds_per_panel, rows_leds_per_panel);
      vec = imgProc->convertToBGRVector(output);
      vec = imgProc->thresholdVec(vec);
      grid->show(vec);
      delay(delay_ms); 
    }
  }

  //grid->clearLEDs();
}

void Controller::show_forever() {
  using namespace std;
  using namespace cv;

  vector<uint8_t> vec;
  Mat output;
  
  while(1){
    for (auto it = imgGIFasList.begin(); it != imgGIFasList.end(); it++) {
      
      imgProc->readImage(*it);
      output = imgProc->perspTransIm( gestureSensor->getGestureState() );
      output = imgProc->reconfigureImage(output, cols_panels, rows_panels, 
                                cols_leds_per_panel, rows_leds_per_panel);
      vec = imgProc->convertToBGRVector(output);
      vec = imgProc->thresholdVec(vec);
      grid->show(vec);
      delay(delay_ms); 
    }
  }

  //grid->clearLEDs();
}
