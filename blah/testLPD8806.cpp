#include <iostream>
#include <string>
#include "LPD8806.h"

const uint16_t numLEDs = 12;
LPD8806 strip(numLEDs);
uint8_t r;
uint8_t g;
uint8_t b;

void initLEDs() {
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
    strip.show();
    delay(500);
  }
}

void displayPurple() {
  r = 206;
  g = 84;
  b = 210;

  for(int i=0; i<numLEDs; i++){
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();
}

void cycleLEDs() {
  r = 0; g = 0; b= 0;

  while(1){    
    for (int i=0; i<numLEDs;i++){
      strip.setPixelColor(i,r,g,b);
      r+=5;
      g+=10;
      b+=3;
    }
    strip.show(); //Sets the color values
    delay(100); 
  }  
}

void turnOff() {
  r = 0;
  g = 0;
  b = 0;
 
  for(int i=0; i<numLEDs; i++){
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();

}

/* Usage: ./testLPD8806 (testFuncName) */
int main(int argc, char** argv) {
  if (argc != 2) {
    printUsage();
  } else {
    std::string input = argv[1];
    std::string str1 = "displayRed";
    std::string str2 = "displayGreen";
    std::string str3 = "displayBlue";
    std::string str4 = "displaySequentialRed";
    std::string str5 = "displayPurple";
    std::string str6 = "cycleLEDs";

    initLEDs();

    if (input.compare(str1) == 0) {
      displayRed();
    } else if (input.compare(str2) == 0) {    
      displayGreen();
    } else if (input.compare(str3) == 0) {    
      displayBlue();
    } else if (input.compare(str4) == 0) {    
      displaySequentialRed();
    } else if (input.compare(str5) == 0) {    
      displayPurple();
    } else if (input.compare(str6) == 0) {    
      cycleLEDs();
    } else {
      printUsage();
    }

  std::cout << "\n" << "Press ENTER to Finish" << "\n";
  std::cin.ignore();
  turnOff();
  return 0;
  }
}
