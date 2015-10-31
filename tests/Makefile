CXXFLAGS = -g -std=c++11
CXXFLAGS_CV = `pkg-config --cflags opencv` 
LIBS_CV = `pkg-config --libs opencv`
LIBS_WPI = -lwiringPi
IDIR=../include
SDIR=../src


TARGETS = testLPD8806 testImageProcessor

all: $(TARGETS)

testImageProcessor: testImageProcessor.o ImageProcessor.o
	g++ -o $@ $^ -I$(IDIR) $(CXXFLAGS) $(CXXFLAGS_CV) $(LIBS_CV)

testLPD8806: testLPD8806.o LPD8806.o
	g++ -o $@ $^ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI) 



ImageProcessor.o: $(SDIR)/ImageProcessor.cpp $(IDIR)/ImageProcessor.hpp 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(CXXFLAGS_CV) $(LIBS_CV)

testImageProcessor.o: testImageProcessor.cpp $(IDIR)/ImageProcessor.hpp 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(CXXFLAGS_CV) $(LIBS_CV)

LPD8806.o: $(SDIR)/LPD8806.cpp $(IDIR)/LPD8806.hpp 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI)

testLPD8806.o: testLPD8806.cpp $(IDIR)/LPD8806.hpp 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI)


.PHONY: clean

clean:
	rm -f *.o
