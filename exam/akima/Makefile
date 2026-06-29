CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: all clean

all: akima_plot.svg README.txt

akima_plot.svg: plot.gpi data.txt spline.txt
	gnuplot $<

data.txt spline.txt README.txt: main
	./$<

main: main.o akima.o vector.o
	$(CXX) -o $@ $^

main.o: main.cc akima.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

akima.o: akima.cc akima.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

vector.o: vector.cc vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f *.txt main *.o akima_plot.svg