CXXFLAGS = -g -std=c++11
CXXFLAGS_CV = `pkg-config --cflags opencv` 
CXXFLAGS_MAGICK = -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-6 
LIBS_CV = `pkg-config --libs opencv`
LIBS_WPI = -lwiringPi
LIBS_MAGICK = -L/usr/local/lib -lMagick++-6.Q16 -lMagickWand-6.Q16 -lMagickCore-6.Q16
IDIR=../include
SDIR=../src


TARGETS = testLPD8806 testImageProcessor Controller.o

all: $(TARGETS)

testImageProcessor: ImageProcessor.o GridLED.o LPD8806.o testImageProcessor.o 
	g++ -o $@ $^ -I$(IDIR) $(CXXFLAGS) $(CXXFLAGS_CV) $(LIBS_CV) $(LIBS_WPI)

testLPD8806: testLPD8806.o LPD8806.o
	g++ -o $@ $^ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI) 



ImageProcessor.o: $(SDIR)/ImageProcessor.cpp $(IDIR)/ImageProcessor.hpp
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(CXXFLAGS_CV) $(LIBS_CV)

testImageProcessor.o: testImageProcessor.cpp $(IDIR)/ImageProcessor.hpp $(IDIR)/GridLED.hpp 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(CXXFLAGS_CV) $(LIBS_CV) 

GridLED.o: $(SDIR)/GridLED.cpp $(IDIR)/GridLED.hpp $(IDIR)/LPD8806.hpp
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI)

LPD8806.o: $(SDIR)/LPD8806.cpp $(IDIR)/LPD8806.hpp 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI)

testLPD8806.o: testLPD8806.cpp $(IDIR)/LPD8806.hpp 
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(LIBS_WPI)

Controller.o: $(SDIR)/Controller.cpp $(IDIR)/ImageProcessor.hpp $(IDIR)/GridLED.hpp
	g++ -c $< -o $@ -I$(IDIR) $(CXXFLAGS) $(CXXFLAGS_MAGICK) $(LIBS_MAGICK) 


.PHONY: clean

clean:
	rm -f *.o
