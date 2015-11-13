#include "ImageProcessor.hpp"

int main(int argc, char** argv) {
  if ( argc != 2 ) {
    printf("usage: testImageProcessor <Image_Path>\n");
    return -1;
  }

  ImageProcessor imgProc;
  imgProc.readImage(argv[1]);

  using namespace std;
  using namespace cv;
  Mat im = imgProc.getImage();
  cout << im << endl << endl;
  cout << endl;
  Point3_<uchar>* p = im.ptr<Point3_<uchar> >(1,1);
  p = im.ptr<Point3_<uchar> >(1,4);
  p = im.ptr<Point3_<uchar> >(1,7);

  vector<uint8_t> vectorBGR = imgProc.convertToBGRVector();

  for (auto i: vectorBGR) {
    cout << i << ' ';
  }
  cout << endl;

  Mat im2 = imgProc.reshapeImage(3, 3, 2, 3); 
  imwrite("../testReshapeImage2_Result.tif", im2);
   
  cout << "Press ENTER to finish" << endl;
  cin.ignore();

  return 0;
}
