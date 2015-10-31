#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor(char* fileName) {
  image = cv::imread(fileName, 1);

}

std::vector<uint8_t> ImageProcessor::convertToBGRVector(void) {
  std::vector<uint8_t> vec;
  vec.assign(image.datastart, image.dataend);

  return vec;
}
