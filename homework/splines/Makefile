CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: all clean

all: out.txt spline_fig.svg

spline_fig.svg: out.txt spline_fig.gpi
	gnuplot spline_fig.gpi

out.txt: main
	./$< > $@

main: main.o LinearSpline.o vector.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc LinearSpline.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

vector.o: vector.cc vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

LinearSpline.o: LinearSpline.cc LinearSpline.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f out.txt main *.o *_fig.svg
