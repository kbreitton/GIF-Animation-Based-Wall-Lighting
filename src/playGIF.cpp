#include "Controller.hpp"
#include <sstream>
#include <ctime>

Controller controller;

int main(int argc, char** argv) {
  if ( argc != 3 ) {
    printf("usage: testController <Image_Path> <duration_ms> \n");
    return -1;
  }
  
  using namespace std;
  
  controller.readGIF(argv[1]);

  stringstream s(argv[2]);
  unsigned int duration_ms;
  s >> duration_ms;
  cout << "playing" << endl;
  
  clock_t start_time = clock();
 
  if (duration_ms <= 0) {
    controller.show_forever();
  } else {
    controller.show(duration_ms);
  }

  using namespace std;
  /* cout << "Press ENTER to finish" << endl;
  cin.ignore(); */
  
  clock_t end_time = clock(); 
  double timeInSec = (end_time - start_time ) / (double) CLOCKS_PER_SEC;

  cout<<"duration: "<< timeInSec << endl;
  return 0;
}
