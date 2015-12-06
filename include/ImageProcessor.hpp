#pragma once

#include <opencv2/opencv.hpp>
#include "APDS9960_RPi.h"
#include <vector>
#include <cstdint>
#include <cassert>
#include <algorithm>

#define APDS9960_INT 7

typedef enum gesture_state {
  LEFT,
  RIGHT,
  UP,
  DOWN,
  DEFAULT
} GESTURE_STATE;

class ImageProcessor {
  
private:  
  cv::Mat _image;
  cv::Mat createImChunk(const cv::Mat& src_vec, uint8_t col_panel_count, uint8_t row_panel_count,
                        uint8_t cols_panels, uint8_t cols_leds_per_panel, 
                        uint8_t rows_leds_per_panel); 
  
  const uint8_t _px_threshold = 50;

  GESTURE_STATE _gesture_state = DEFAULT; 
  
  cv::Mat _lambda_left_gest;
  cv::Mat _lambda_right_gest;
  cv::Mat _lambda_up_gest;
  cv::Mat _lambda_down_gest;

  APDS9960_RPi adps;
  int isr_flag = 0;

  void interruptRoutine() {
    isr_flag = 1;
  }

  void handleGesture(void);

public:
  ImageProcessor();
  cv::Mat getImage(void);
  void readImage(char* fileName);
  void readImage(cv::Mat imageMat);
  std::vector<uint8_t> convertToBGRVector(const cv::Mat& input);

  /* apply a threshold to an input vec such that below the threshold,
   * values will be set to 0 -- this is for particular LED aesthetics */
  std::vector<uint8_t>& thresholdVec(std::vector<uint8_t>& input);

  
  /* a strip displays pixels left to right, but for a panel format and across LEDs
   * the image must be reshaped so the image/GIF displays correctly 
   *
   * this assumes panels are assembed left to right then top to bottom,
   * and that the "last" pixel within one panel is at its bottom right */
  void reconfigureImage(uint8_t cols_panels,
                    uint8_t rows_panels,
                    uint8_t cols_leds_per_panel,
                    uint8_t rows_leds_per_panel);
  
  void getGestureState(void);
  void determinePerspTransforms(void);
  cv::Mat perspTransIm(void);
  
};
