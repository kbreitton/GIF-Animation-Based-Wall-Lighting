CXXFLAGS=-std=c++11 -lwiringPi -Wall

TARGETS = testLPD8806 
OBJS=testLPD8806.o

all: $(TARGETS)

testLPD8806: testLPD8806.o
	g++ -o testLPD8806 testLPD8806.o $(CXXFLAGS)

%.o: %.cpp LPD8806.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJS) $(TARGETS)

