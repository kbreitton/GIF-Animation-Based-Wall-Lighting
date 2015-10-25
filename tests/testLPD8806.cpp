#include <iostream>
#include "LPD8806.h"

const uint16_t numLEDs = 12;
LPD8806 strip(numLEDs);
uint8_t r;
uint8_t g;
uint8_t b;

void initLEDs() {
  strip.begin();
  
  r = 0;
  g = 0; 
  b = 0;

  //Initialize empty strip
  for(int i=0; i<numLEDs; i++){
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();

}

void printUsage() {
  std::cout << "Usage: ./testLPD8806 (testFuncName)" << "\n" 
              << "Test Functions:" << "\n"
              << "  displayRed" << "\n"
              << "  displayGreen" << "\n"
              << "  displayBlue" << "\n"
              << "  displaySequentialRed" << "\n"
              << "  displayTurqoise" << "\n";
}

void displayRed() {
  r = 255;
  g = 0;
  b = 0;
  for(int i=0; i<numLEDs; i++){
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();
}

void displayGreen() {
  r = 0;
  g = 255;
  b = 0;
  for(int i=0; i<numLEDs; i++){
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();

}

void displayBlue() {
  r = 0;
  g = 0;
  b = 255;
  for(int i=0; i<numLEDs; i++){
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();
}

void displaySequentialRed() {
  r = 255;
  g = 0;
  b = 0;

  for(int i=0; i<numLEDs; i++){
    strip.setPixelColor(i,r,g,b);
    strip.show()
    // wait //
  }
}

void displayPurple() {
  r = 206;
  g = 84;
  b = 210;

  for(int i=0; i<numLEDs; i++){
    strip.setPixelColor(i,r,g,b);
    strip.show()
    // wait //
  }

}


/* Usage: ./testLPD8806 (testFuncName) */
int main(int argc, char** argv) {
  if (argc != 1) {
    printUsage();
  } else {
    initLEDs();

    switch(argv[1]) {
      case "displayRed":
        displayRed();
        break;
      case "displayGreen":
        displayGreen();
        break;
      case "displayBlue":
        displayBlue();
        break;
      case "displaySequentialRed":
        displaySequentialRed();
        break;
      case "displayTurqoise":
        displayTurqoise();
        break;
      default:
        std::cout << "typo in function name" << "\n";
        printUsage(); 
    }
  }

  std::cout << "\n" << "Press Any Button to Finish" << "\n";
  std::cin.ignore();
  return 0;
}
