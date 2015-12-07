#include "ImageProcessor.hpp"
#include <opencv2/highgui.hpp>

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
 /* cout << im << endl << endl;*/
  //cout << endl;
  //Point3_<uchar>* p = im.ptr<Point3_<uchar> >(1,1);
  //p = im.ptr<Point3_<uchar> >(1,4);
  //p = im.ptr<Point3_<uchar> >(1,7);
  imgProc.determinePerspTransforms(im);

  Mat im_trans_left = imgProc.perspTransIm(LEFT);
  Mat im_trans_right = imgProc.perspTransIm(RIGHT);
  Mat im_trans_up = imgProc.perspTransIm(UP);
  Mat im_trans_down = imgProc.perspTransIm(DOWN);
  //vector<uint8_t> vectorBGR = imgProc.convertToBGRVector(im);
  //vectorBGR = imProc.thresholdVec(vectorBGR);
  /*for (auto i: vectorBGR) {*/
    //cout << i << ' ';
  //}
  /*cout << endl;*/

  //imgProc.reconfigureImage(3, 3, 2, 3); 
  //imwrite("../bin/images/testReshapeImage2_Result.tif", imgProc.getImage());
  /*imshow("DEFAULT", im);*/
  //imshow("LEFT", im_trans_left);
  //imshow("RIGHT", im_trans_right);
  //imshow("UP", im_trans_up);
  /*imshow("DOWN", im_trans_down);*/
  imwrite("images/im_default.jpg", im);
  imwrite("images/im_down.jpg", im_trans_down);
  imwrite("images/im_left.jpg", im_trans_left);
  imwrite("images/im_right.jpg", im_trans_right);
  imwrite("images/im_up.jpg", im_trans_up);

  /*cout << "Press ENTER to finish" << endl;*/
  /*cin.ignore();*/

  return 0;
}
