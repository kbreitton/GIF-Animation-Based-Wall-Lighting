#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdint>

class ImageProcessor {
  
private:  
  cv::Mat image;

public:
  ImageProcessor();
  cv::Mat getImage(void);
  void readImage(char* fileName);
  void readImage(cv::Mat imageMat);
  std::vector<uint8_t> convertToBGRVector(void);
  //plan to add methods like getSensorData() and modifyImage()
};
