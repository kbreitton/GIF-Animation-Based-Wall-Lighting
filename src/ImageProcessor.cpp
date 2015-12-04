#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor() {
  determinePerspTransforms();
  wiringPiSetup();
  wiringPiISR(APDS9960_INT, INT_EDGE_FALLING,  interruptRoutine);
  apds.init();
  apds.enableGestureSensor(true);
}

cv::Mat ImageProcessor::getImage(void) {
  return _image;
}

void ImageProcessor::readImage(char* fileName) {
  _image = cv::imread(fileName,1);
}

void ImageProcessor::readImage(cv::Mat imageMat) {
  _image = imageMat;
}

std::vector<uint8_t> ImageProcessor::convertToBGRVector(const cv::Mat& input) {
  using namespace std;
  vector<uint8_t> vec;
  vec.assign(input.datastart, input.dataend);

  return vec;
}

std::vector<uint8_t>& ImageProcessor::thresholdVec(std::vector<uint8_t>& input) {
  auto applyThres = [=](uint8_t& pixel_val) { 
    if (pixel_val < _px_threshold) {
      pixel_val = 0;
    } 
  };
  std::for_each(input.begin(), input.end(), applyThres);

  return input;
}

void ImageProcessor::getGestureState() {
  if (isr_flag == 1) {
    handleGesture();
    isr_flag = 0;
  }
}

void ImageProcessor::handleGesture() {
  if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        cout << "UP" << endl;
        
        if (_gesture_state == DEFAULT) {
          _gesture_state == UP;
        } else if (_gesture_state == DOWN) {
          _gesture_state == DEFAULT;
        } 
        break;
      case DIR_DOWN:
        cout << "DOWN" << endl;

        if (_gesture_state == DEFAULT) {
          _gesture_state = DOWN;
        } else if (_gesture_state == UP) {
          _gesture_state = DEFAULT;
        }
        break;
      case DIR_LEFT:
        cout << "LEFT" << endl;

        if (_gesture_state == DEFAULT) {
          _gesture_state = LEFT;
        } else if (_gesture_state == RIGHT) {
          _guesture_state = DEFAULT;
        }
        break;
      case DIR_RIGHT:
        cout << "RIGHT" << endl;

        if (_gesture_state == DEFAULT) {
          _gesture_state = RIGHT;
        } else if (_gesture_state = LEFT) {
          _gesture_state = DEFAULT;
        }
        break;
      default:
        cout << "NONE" << endl;
    }
  }
}

void ImageProcessor::determinePerspTransforms() {
  using namespace cv;
  
  _lambda_left_gest = Mat(2, 4, CV_32FC1);
  _lambda_left_gest = Mat::zeros( _image.rows, _image.cols, _image.type() );
 
  _lambda_right_gest = Mat(2, 4, CV_32FC1);
  _lambda_right_gest = Mat::zeros( _image.rows, _image.cols, _image.type() );
  
  _lambda_up_gest = Mat(2, 4, CV_32FC1);
  _lambda_up_gest = Mat::zeros( _image.rows, _image.cols, _image.type() );
  
  _lambda_down_gest = Mat(2, 4, CV_32FC1);
  _lambda_down_gest = Mat::zeros( _image.rows, _image.cols, _image.type() );
  
  Point2f defaultQuad[4];
  defaultQuad[0] = Point2f( 0,0 );
  defaultQuad[1] = Point2f( _image.cols-1,0);
  defaultQuad[2] = Point2f( _image.cols-1,_image.rows-1);
  defaultQuad[3] = Point2f( 0,_image.rows-1  );

  Point2f leftGestQuad[4];
  leftGestQuad[0] = Point2f( (int) (_image.cols * -0.15f) , (int) (_image.rows * -0.30f) );
  leftGestQuad[1] = Point2f( (int) (_image.cols *  1.15f) , (int) (_image.rows * -0.15f) );
  leftGestQuad[2] = Point2f( (int) (_image.cols *  1.15f) , (int) (_image.rows *  1.15f) );
  leftGestQuad[3] = Point2f( (int) (_image.cols * -0.15f) , (int) (_image.rows *  1.30f) );

  Point2f rightGestQuad[4];
  rightGestQuad[0] = Point2f( (int) (_image.cols * -0.15f) , (int) (_image.rows * -0.15f) );
  rightGestQuad[1] = Point2f( (int) (_image.cols *  1.15f) , (int) (_image.rows * -0.30f) );
  rightGestQuad[2] = Point2f( (int) (_image.cols *  1.15f) , (int) (_image.rows *  1.30f) );
  rightGestQuad[3] = Point2f( (int) (_image.cols * -0.15f) , (int) (_image.rows *  1.15f) );

  Point2f upGestQuad[4];
  upGestQuad[0] = Point2f( (int) (_image.cols * -0.15f) , (int) (_image.rows * -0.30f) );
  upGestQuad[1] = Point2f( (int) (_image.cols *  1.15f) , (int) (_image.rows * -0.15f) );
  upGestQuad[2] = Point2f( (int) (_image.cols *  1.15f) , (int) (_image.rows *  1.15f) );
  upGestQuad[3] = Point2f( (int) (_image.cols * -0.15f) , (int) (_image.rows *  1.30f) );
 
  Point2f downGestQuad[4];
  downGestQuad[0] = Point2f( (int) (_image.cols * -0.15f) , (int) (_image.rows * -0.30f) );
  downGestQuad[1] = Point2f( (int) (_image.cols *  1.15f) , (int) (_image.rows * -0.15f) );
  downGestQuad[2] = Point2f( (int) (_image.cols *  1.15f) , (int) (_image.rows *  1.15f) );
  downGestQuad[3] = Point2f( (int) (_image.cols * -0.15f) , (int) (_image.rows *  1.30f) );
 
  _lambda_left_gest = getPerspectiveTransform(leftGestQuad, defaultQuad);
  _lambda_right_gest = getPerspectiveTransform(rightGestQuad, defaultQuad);
  _lambda_up_gest = getPerspectiveTransform(upGestQuad, defaultQuad);
  _lambda_down_gest = getPerspectiveTransform(downGestQuad, defaultQuad);
}

cv::Mat ImageProcessor::perspTransIm() {
  using namespace cv;
  Mat output;
  switch(_gesture_state) {
    case LEFT: 
      warpPerspective(_image, output, _lambda_left_gest, _image.size());
      break;
    case RIGHT:
      warpPerspective(_image, output, _lambda_right_gest, _image.size());
      break;
    case UP:
      warpPerspective(_image, output, _lambda_up_gest, _image.size());
      break;
    case DOWN:
      warpPerspective(_image, output, _lambda_down_gest, _image.size());
      break;
    default:
      break;
  }
   return output;
}

void ImageProcessor::reconfigureImage(uint8_t cols_panels,
                                      uint8_t rows_panels,
                                      uint8_t cols_leds_per_panel,
                                      uint8_t rows_leds_per_panel) {

  assert(_image.rows == rows_panels * rows_leds_per_panel);
  assert(_image.cols == cols_panels * cols_leds_per_panel);
  using namespace std;
  using namespace cv;
  
  vector<Mat> chunks;

  /* vectorize image for easier reshaping calculations */
  uint8_t original_rows = _image.rows;
  Mat image_vec = _image.reshape(0,1);

  for(int j = 0; j < rows_panels; j++) {
    for(int i = 0; i < cols_panels; i++) {
      Mat chunk = createImChunk(image_vec, i, j, cols_panels, 
                                cols_leds_per_panel, rows_leds_per_panel);
      chunks.push_back(chunk);
    }
  }
  
  /* concatenate chunks */
  Mat result;
  hconcat(chunks, result);
  result = result.reshape(0,original_rows);
  
  _image = result;

}

cv::Mat ImageProcessor::createImChunk(const cv::Mat& src_vec, 
                                      uint8_t col_panel_count, 
                                      uint8_t row_panel_count,
                                      uint8_t cols_panels, 
                                      uint8_t cols_leds_per_panel, 
                                      uint8_t rows_leds_per_panel) {
  using namespace cv;
  Mat im;

  /* fill in first row of im */
  uint8_t leds_per_panel = cols_leds_per_panel * rows_leds_per_panel;
  uint8_t startPix = col_panel_count * cols_leds_per_panel + 
                     row_panel_count * (leds_per_panel*cols_panels);
  uint8_t endPix = startPix + cols_leds_per_panel;
  
  im = src_vec(Range::all(), Range(startPix, endPix));

  /* fill in subsequent rows of im */
  for (int j = 1; j < rows_leds_per_panel; j++) {
    startPix += cols_leds_per_panel*cols_panels;
    endPix = startPix + cols_leds_per_panel;
    im.push_back(src_vec(Range::all(), Range(startPix, endPix)));
  }
  
  return im.reshape(0,1).clone();
  
}
