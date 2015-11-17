#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor() {}

cv::Mat ImageProcessor::getImage(void) {
  return _image;
}

void ImageProcessor::readImage(char* fileName) {
  _image = cv::imread(fileName,1);
}

void ImageProcessor::readImage(cv::Mat imageMat) {
  _image = imageMat;
}

std::vector<uint8_t> ImageProcessor::convertToBGRVector(void) {
  using namespace std;
  vector<uint8_t> vec;
  vec.assign(_image.datastart, _image.dataend);

  return vec;
}

std::vector<uint8_t>& ImageProcessor::thresholdVec(std::vector<uint8_t>& input) {
  auto applyThres = [=](uint8_t pixel_val) -> uint8_t { 
    if (pixel_val < _threshold) {
      return 0;
    } else {
      return pixel_val;
    }
  };
  std::for_each(input.begin(), input.end(), applyThres);

  return input;
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
      Mat chunk = createImChunk(image_vec, i, j, cols_panels, cols_leds_per_panel, rows_leds_per_panel);
      chunks.push_back(chunk);
    }
  }
  
  /* concatenate chunks */
  Mat result;
  hconcat(chunks, result);
  result = result.reshape(0,original_rows);
  
  _image = result;

}

cv::Mat ImageProcessor::createImChunk(const cv::Mat& src_vec, uint8_t col_panel_count, uint8_t row_panel_count,
                                  uint8_t cols_panels, uint8_t cols_leds_per_panel, 
                                  uint8_t rows_leds_per_panel) {
  using namespace cv;
  Mat im;

  /* fill in first row of im */
  uint8_t leds_per_panel = cols_leds_per_panel * rows_leds_per_panel;
  uint8_t startPix = col_panel_count * cols_leds_per_panel + row_panel_count*(leds_per_panel*cols_panels);
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
