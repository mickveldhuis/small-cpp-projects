CXX = g++
TARGET = polyfitter
SOURCES = fitter.cpp leastsquares.cpp matrices.cpp graphdatareader.cpp
OBJS = $(SOURCES:.cpp=.o)
CXXFLAGS = #-g -Wall

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CXX) $(OBJS) -o $@

.cpp.o:
		$(CXX) -c $(CXXFLAGS)  $<

clean:
		rm *.o polyfitter
