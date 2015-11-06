#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor() {}

std::vector<uint8_t> ImageProcessor::convertToBGRVector(void) {
  using namespace std;
  vector<uint8_t> vec;
  vec.assign(image.datastart, image.dataend);

  return vec;
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
