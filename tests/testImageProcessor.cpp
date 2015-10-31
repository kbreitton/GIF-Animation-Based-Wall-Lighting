#include "ImageProcessor.hpp"
#include "GridLED.hpp"

int main(int argc, char** argv) {
  if ( argc != 2 ) {
    printf("usage: testImageProcessor <Image_Path>\n");
    return -1;
  }

  ImageProcessor imgProc(argv[1]);

  using namespace std;
  using namespace cv;
  Mat im = imgProc.image;
  cout << im << endl << endl;
  cout << endl;
  Point3_<uchar>* p = im.ptr<Point3_<uchar> >(1,1);
  cout << "Blue: " << p << endl << endl;
  p = im.ptr<Point3_<uchar> >(1,4);
  cout << "Green: " << p << endl << endl;
  p = im.ptr<Point3_<uchar> >(1,7);
  cout << "Red: " << p << endl << endl;

  std::vector<uint8_t> vectorBGR = imgProc.convertToBGRVector();

/*  for (auto i: vectorBGR) {*/
    //cout << i << ' ';
  //}
  /*cout << endl;*/
  
  uint16_t numLEDs = 12; 
  GridLED grid(numLEDs);
  vectorBGR.resize(36); //for 12 LEDs
  std::vector<uint8_t> &vectorRef = vectorBGR;
  grid.show(vectorRef);
  
  cout << "Press ENTER to finish" << endl;
  cin.ignore();
  return 0;
}
