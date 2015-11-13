#include "Controller.hpp"
#include <sstream>

int main(int argc, char** argv) {
  if ( argc != 3 ) {
    printf("usage: testController <Image_Path> <duration_ms> \n");
    return -1;
  }
  
  using namespace std;
  
  Controller controller;
  controller.readGIF(argv[1]);

  stringstream s(argv[2]);
  unsigned int duration_ms;
  s >> duration_ms;
  controller.show(duration_ms);
  
  using namespace std;
  /* cout << "Press ENTER to finish" << endl;
  cin.ignore(); */

  return 0;
}
