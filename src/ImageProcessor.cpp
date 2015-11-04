#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor() {}

std::unique_ptr< std::vector<uint8_t> > ImageProcessor::convertToBGRVector(void) {
  using namespace std;
  unique_ptr< vector<uint8_t> > vec_ptr(new vector<uint8_t>);
  vec_ptr->assign(image.datastart, image.dataend);

  return vec_ptr;
}

cv::Mat ImageProcessor::getImage(void) {
  return image;
}

void ImageProcessor::readImage(char* fileName) {
  image = cv::imread(fileName,1);
}

void ImageProcessor::readImage(cv::Mat imageMat) {
  image = imageMat;
}
