#include "Controller.hpp"

int main(int argc, char** argv) {
  if ( argc != 2 ) {
    printf("usage: testController <Image_Path>\n");
    return -1;
  }
  Controller controller(12, 12, 1);
  controller.setDuration(5000);
  controller.show();
  
  cout << "Press ENTER to finish" << endl;
  cin.ignore();

  return 0;
}
