#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdint>

class ImageProcessor {
  
public:
  cv::Mat image;
  ImageProcessor(char* fileName);

  std::vector<uint8_t> convertToBGRVector(void);
};
