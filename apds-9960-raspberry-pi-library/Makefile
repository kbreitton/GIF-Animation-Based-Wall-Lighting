CXXFLAGS = -g -std=c++11 -fno-exceptions
LIBS_WPI = -lwiringPi
IDIR = .
SDIR = .

TARGETS = GestureTest

all: $(TARGETS)

GestureTest: APDS9960_RPi.o GestureTest.o 
	g++ -o $@ $^ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI) 

APDS9960_RPi.o: $(SDIR)/APDS9960_RPi.cpp $(IDIR)/APDS9960_RPi.h
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI)

GestureTest.o: GestureTest.cpp $(IDIR)/APDS9960_RPi.h 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI) 

.PHONY: clean

clean:
	rm -f *.o $(TARGETS) 
