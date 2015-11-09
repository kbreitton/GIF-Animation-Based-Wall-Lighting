#include "Controller.hpp"

int main(int argc, char** argv) {
  if ( argc != 2 ) {
    printf("usage: testController <Image_Path>\n");
    return -1;
  }
  Controller controller(12, 12, 1);
  controller.readGIF(argv[1]);
  controller.show(5000);
  
  using namespace std;
  /* cout << "Press ENTER to finish" << endl;
  cin.ignore(); */

  return 0;
}
