CXXFLAGS = -g -std=c++11
CXXFLAGS_CV = `pkg-config --cflags opencv` 
CXXFLAGS_MAGICK = -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-6 
LIBS_CV = `pkg-config --libs opencv`
LIBS_WPI = -lwiringPi
LIBS_MAGICK = -L/usr/local/lib -lMagick++-6.Q16 -lMagickWand-6.Q16 -lMagickCore-6.Q16
IDIR=../include
SDIR=../src


TARGETS = testLPD8806 testImageProcessor testController

all: $(TARGETS)

testImageProcessor: ImageProcessor.o GridLED.o testImageProcessor.o 
	g++ -o $@ $^ -I$(IDIR) $(CXXFLAGS)

testLPD8806: LPD8806.o testLPD8806.o
	g++ -o $@ $^ -I$(IDIR) $(CXXFLAGS)

testController: Controller.o testController.o
	g++ -o $@ $^ -I$(IDIR) $(CXXFLAGS) 


ImageProcessor.o: $(SDIR)/ImageProcessor.cpp $(IDIR)/ImageProcessor.hpp
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(CXXFLAGS_CV) $(LIBS_CV)

testImageProcessor.o: testImageProcessor.cpp $(IDIR)/ImageProcessor.hpp $(IDIR)/GridLED.hpp 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) 

GridLED.o: $(SDIR)/GridLED.cpp $(IDIR)/GridLED.hpp $(IDIR)/LPD8806.hpp
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) 

LPD8806.o: $(SDIR)/LPD8806.cpp $(IDIR)/LPD8806.hpp 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI)

testLPD8806.o: testLPD8806.cpp $(IDIR)/LPD8806.hpp 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS)

Controller.o: $(SDIR)/Controller.cpp $(IDIR)/ImageProcessor.hpp $(IDIR)/GridLED.hpp
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(CXXFLAGS_MAGICK) $(LIBS_MAGICK) 

testImageProcessor.o: testImageProcessor.cpp $(IDIR)/Controller.hpp
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS)


.PHONY: clean

clean:
	rm -f *.o
